// import { useCallback, useRef, useState } from 'react';
// import { Device } from 'react-native-ble-plx';

// const SERVICE_UUID = '6e400001-b5a3-f393-e0a9-e50e24dcca9e';
// const NOTIFY_UUID = '6e400003-b5a3-f393-e0a9-e50e24dcca9e';
// const WRITE_UUID = '6e400002-b5a3-f393-e0a9-e50e24dcca9e';

// // const manager = new BleManager();

// const log = (msg: string) => {
//   console.log(msg);
// };

// export function useBle() {
//   const [connected, setConnected] = useState(false);
//   const [scanning, setScanning] = useState(false);
//   const DeviceRef = useRef<Device | null>(null);
//   const pendingResolveRef = useRef<(text: string) => void | null>(null);

//   const connect = useCallback(async () => {
//     if (connected || scanning) return;
//     log('Waiting for BLE initialization...');

//     await new Promise<void>((resolve, reject) => {
//       const sub = manager.onStateChange((state) => {
//         log(`State: ${state}`);
//         if (state === 'PoweredOn') {
//           sub.remove();
//           resolve();
//         }
//         if (state === 'PoweredOff') {
//           sub.remove();
//           reject(new Error('Bluetooth is off'));
//         }
//         if (state === 'Unauthorized') {
//           sub.remove();
//           reject(new Error('No permission'));
//         }
//         if (state === 'Unsupported') {
//           sub.remove();
//           reject(new Error('Bluetooth not supported'));
//         }
//         if (state === 'Resetting') {
//           log('Bluetooth resetting, waiting...');
//         }
//       }, true);
//     });

//     log('Scanning...');
//     setScanning(true);

//     const scanTimeout = setTimeout(() => {
//       manager.stopDeviceScan();
//       log('Device not found (timeout)');
//     }, 10000);

//     manager.startDeviceScan(null, null, async (error, scanned) => {
//       if (error) {
//         clearTimeout(scanTimeout);
//         log(`Scan error: ${error.message}`);
//         return;
//       }
//       log(`Found: ${scanned?.name ?? 'unknown'} (${scanned?.rssi} dBm)`);

//       if (!scanned?.name?.includes('ESP32')) return;

//       clearTimeout(scanTimeout);
//       log('BLE found, connecting...');
//       manager.stopDeviceScan();
//       setScanning(false);

//       try {
//         const device = await scanned.connect();
//         log('Connected');

//         await device.discoverAllServicesAndCharacteristics();
//         log('Services discovered');

//         log('Subscribing to notifications...');
//         device.monitorCharacteristicForService(SERVICE_UUID, NOTIFY_UUID, (err, char) => {
//           if (err) {
//             log(`❌ Receive error: ${err.message}`);
//             return;
//           }

//           const bytes = Uint8Array.from(atob(char!.value!), (c) => c.charCodeAt(0));
//           const text = new TextDecoder().decode(bytes);
//           log(` Received: "${text}"`);

//           pendingResolveRef.current?.(text);
//           pendingResolveRef.current = null;
//         });

//         device.onDisconnected(() => {
//           setConnected(false);
//           DeviceRef.current = null;
//           log('Device disconnected');
//         });

//         setConnected(true);
//         DeviceRef.current = device;
//         log('Ready');
//       } catch (error: any) {
//         log(`Connection error ${error.massage}`);
//       }
//     });
//   }, []);

//   const sendAndReceive = useCallback(async (msg: string) => {
//     if (!DeviceRef.current) return;
//     log(`Sending (waiting for response): "${msg}"`);

//     try {
//       const response = await Promise.race([
//         new Promise((resolve, reject) => {
//           pendingResolveRef.current = resolve;

//           const bytes = new TextEncoder().encode(msg);
//           const base64 = btoa(String.fromCharCode(...bytes));

//           DeviceRef.current!.writeCharacteristicWithoutResponseForService(
//             SERVICE_UUID,
//             WRITE_UUID,
//             base64
//           );

//           log('Sent');
//         }),
//         new Promise((_, reject) =>
//           setTimeout(() => {
//             pendingResolveRef.current = null;
//             reject(new Error('Timeout 2s'));
//           }, 2000)
//         ),
//       ]);

//       log(`Response: "${response}"`);
//     } catch (error: any) {
//       log(`Sending error: ${error.massage}`);
//     }
//   }, []);

//   return { connected, scanning, connect, sendAndReceive };
// }

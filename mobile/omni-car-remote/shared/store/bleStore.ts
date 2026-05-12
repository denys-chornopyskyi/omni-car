import { Device } from 'react-native-ble-plx';
import { create } from 'zustand';
import log from '../utils/log';

const SERVICE_UUID = '6E400001-B5A3-F393-E0A9-E50E24DCCA9E';
const NOTIFY_UUID = '6E400003-B5A3-F393-E0A9-E50E24DCCA9E';
const WRITE_UUID = '6E400002-B5A3-F393-E0A9-E50E24DCCA9E';

// const manager = new BleManager();

interface BleState {
  device: Device | null;
  pendingResolve: ((text: string) => void) | null;
  connected: boolean;
  scanning: boolean;
  connect: () => Promise<void>;
  sendAndReceive: (msg: string) => Promise<void>;
  send: (msg: string) => Promise<void>;
}

export const useBleStore = create<BleState>((set, get) => ({
  device: null,
  pendingResolve: null,
  connected: false,
  scanning: false,

  connect: async () => {
    const { connected, scanning } = get();
    if (connected || scanning) return;

    log('Waiting for BLE initialization...');

    await new Promise<void>((resolve, reject) => {
      const sub = manager.onStateChange((state) => {
        log(`State: ${state}`);
        if (state === 'PoweredOn') {
          sub.remove();
          resolve();
        }
        if (state === 'PoweredOff') {
          sub.remove();
          reject(new Error('Bluetooth is off'));
        }
        if (state === 'Unauthorized') {
          sub.remove();
          reject(new Error('No permission'));
        }
        if (state === 'Unsupported') {
          sub.remove();
          reject(new Error('Not supported'));
        }
      }, true);
    });

    log('Scanning...');
    set({ scanning: true });

    const scanTimeout = setTimeout(() => {
      set({ scanning: false });
      manager.stopDeviceScan();
      log('Device not found (timeout)', 'error');
    }, 10000);

    manager.startDeviceScan(null, null, async (error, scanned) => {
      if (error) {
        clearTimeout(scanTimeout);
        set({ scanning: false });
        log(`Scan error: ${error.message}`, 'error');
        return;
      }

      log(`Found: ${scanned?.name ?? 'unknown'} (${scanned?.rssi} dBm)`);
      if (!scanned?.name?.includes('ESP32')) return;

      clearTimeout(scanTimeout);
      manager.stopDeviceScan();
      set({ scanning: false });

      try {
        const device = await scanned.connect();
        log('Connected', 'success');

        await device.discoverAllServicesAndCharacteristics();
        log('Services discovered');

        device.monitorCharacteristicForService(SERVICE_UUID, NOTIFY_UUID, (err, char) => {
          if (err) {
            log(`Receive error: ${err.message}`, 'error');
            return;
          }

          const bytes = Uint8Array.from(atob(char!.value!), (c) => c.charCodeAt(0));
          const text = new TextDecoder().decode(bytes);
          log(`Received: "${text}"`, 'success');

          // ← берём актуальный pendingResolve через get()
          const { pendingResolve } = get();
          pendingResolve?.(text);
          set({ pendingResolve: null });
        });

        device.onDisconnected(() => {
          set({ connected: false, device: null });
          log('Device disconnected');
        });

        set({ connected: true, device }); // ← один set
        log('Ready', 'success');
      } catch (e: any) {
        log(`Connection error: ${e.message}`, 'error');
      }
    });
  },

  sendAndReceive: async (msg: string) => {
    const { device } = get();
    if (!device) return;

    log(`Sending: "${msg}"`);

    try {
      const response = await Promise.race([
        new Promise<string>((resolve) => {
          set({ pendingResolve: resolve });

          const bytes = new TextEncoder().encode(msg);
          const base64 = btoa(String.fromCharCode(...bytes));

          device
            .writeCharacteristicWithoutResponseForService(
              SERVICE_UUID,
              WRITE_UUID,
              base64
            )
            .then(() => log('Sent'))
            .catch((e) => log(`Write error: ${e.message}`, 'error'));
        }),
        new Promise<never>((_, reject) =>
          setTimeout(() => {
            set({ pendingResolve: null });
            reject(new Error('Timeout 10s'));
          }, 10000)
        ),
      ]);

      log(`Response: "${response}"`);
    } catch (e: any) {
      log(`Sending error: ${e.message}`, 'error'); // ← message не massage
    }
  },
  send: async (msg: string) => {
    const { device } = get();
    if (!device) return;

    const bytes = new TextEncoder().encode(msg);
    const base64 = btoa(String.fromCharCode(...bytes));

    device
      .writeCharacteristicWithoutResponseForService(SERVICE_UUID, WRITE_UUID, base64)
      .then(() => log('Sent'))
      .catch((e) => log(`Write error: ${e.message}`, 'error'));
  },
}));

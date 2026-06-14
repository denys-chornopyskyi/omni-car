import parser, { ParsedPacket } from '@/shared/ble/BleParser';
import { onConnect } from '@/shared/ble/hook/useBLECommandQueue';
import { BleManager, Device } from 'react-native-ble-plx';
import { create } from 'zustand';
import log from '../utils/log';

const SERVICE_UUID = '6E400001-B5A3-F393-E0A9-E50E24DCCA9E';
const NOTIFY_UUID = '6E400003-B5A3-F393-E0A9-E50E24DCCA9E';
const WRITE_UUID = '6E400002-B5A3-F393-E0A9-E50E24DCCA9E';

const manager = new BleManager();

type PendingRequest = {
  resolve: (response: ParsedPacket) => void;
  reject: (response: string) => void;
  timeout: ReturnType<typeof setTimeout>;
};

interface BleState {
  device: Device | null;
  pendingRequest: PendingRequest | null;
  connected: boolean;
  scanning: boolean;
  connect: () => Promise<void>;
  disconnect: () => Promise<void>;
  sendAndReceive: (msg: string | Uint8Array, timeoutMs: number) => Promise<ParsedPacket>;
  send: (msg: string | Uint8Array) => Promise<void>;
}

export const useBleStore = create<BleState>((set, get) => ({
  device: null,
  pendingRequest: null,
  connected: false,
  scanning: false,

  disconnect: async () => {
    await get().device?.cancelConnection();
  },

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
          parser.feed(bytes);
          // const text = new TextDecoder().decode(bytes);
          // log(`Received: "${text}"`, 'success');

          // const { pendingResolve } = get();
          // pendingResolve?.(text);
          // set({ pendingResolve: null });
        });

        device.onDisconnected(() => {
          set({ connected: false, device: null });
          log('Device disconnected');
        });

        set({ connected: true, device });
        log('Ready', 'success');
        onConnect();
      } catch (e: any) {
        log(`Connection error: ${e.message}`, 'error');
      }
    });
  },

  sendAndReceive: async (
    msg: string | Uint8Array,
    timeoutMs: number
  ): Promise<ParsedPacket> => {
    return new Promise((resolve, reject) => {
      log(`send and receive: "${msg}"`);

      if (get().pendingRequest) {
        log('previous request is pending');
        clearTimeout(get().pendingRequest?.timeout);
        set({ pendingRequest: null });
        reject('Reject: cancelled');
      }

      const timeout = setTimeout(() => {
        set({ pendingRequest: null });
        reject('Reject: timeout');
      }, timeoutMs);

      set({
        pendingRequest: {
          reject,
          resolve,
          timeout,
        },
      });

      get().send(msg);
    });
  },
  send: async (msg: string | Uint8Array) => {
    const { device } = get();
    // log('Attemt to send');
    // log(device ? 'true' : 'false');
    if (!device) return;

    const bytes = typeof msg === 'string' ? new TextEncoder().encode(msg) : msg;
    const base64 = btoa(String.fromCharCode(...bytes));

    device
      .writeCharacteristicWithResponseForService(SERVICE_UUID, WRITE_UUID, base64)
      .then(() => log('Sent' + msg))
      .catch((e) => log(`Write error: ${e.message}`, 'error'));
  },
}));

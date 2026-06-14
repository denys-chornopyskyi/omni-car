import { useBleStore } from '@/shared/store/bleStore';
import { useDeviceStore } from '@/shared/store/deviceStore';
import log from '@/shared/utils/log';
import { useRef } from 'react';
import { PacketBuilder } from '../BlePacketBuilder';

const commandQueue = useRef<(() => Promise<void>)[]>([]);
const isProcessing = useRef(false);

const sendNext = async () => {
  if (isProcessing.current || commandQueue.current.length === 0) return;

  isProcessing.current = true;
  const cmd = commandQueue.current.shift()!;

  try {
    await cmd();
    // log(response, 'success');
  } catch (e: any) {
    log(e, 'error');
  } finally {
    isProcessing.current = false;
    sendNext();
  }
};

const requestSafetyMode = async () => {
  const send = useBleStore.getState().sendAndReceive;
  const response = await send(PacketBuilder.getSafetyMode(), 1000);
  if (!!response.value !== useDeviceStore.getState().safetyMode)
    useDeviceStore.getState().setSafetyMode(!useDeviceStore.getState().safetyMode);
};

const requestSpeed = async () => {
  const send = useBleStore.getState().sendAndReceive;
  const response = await send(PacketBuilder.getBase(), 1000);
  useDeviceStore.getState().setSpeed(response.value!);
};

const requestThreshold = async () => {
  const send = useBleStore.getState().sendAndReceive;
  const response = await send(PacketBuilder.getThreshold(), 1000);
  useDeviceStore.getState().setThreshold(response.value!);
};

const requestMode = async () => {
  const send = useBleStore.getState().sendAndReceive;
  const response = await send(PacketBuilder.getModule(), 1000);
  switch (response.value) {
    case 1:
      useDeviceStore.getState().setActiveMode('manual');
      break;
    case 2:
      useDeviceStore.getState().setActiveMode('line');
      break;
  }
};

export const onConnect = () => {
  isProcessing.current = false;
  commandQueue.current = [
    () => requestSafetyMode(),
    () => requestSpeed(),
    () => requestThreshold(),
    () => requestMode(),
  ];
  sendNext();
};

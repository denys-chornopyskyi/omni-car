import { PacketBuilder } from '@/shared/ble/BlePacketBuilder';
import PageContainer from '@/shared/components/ui/PageContainer';
import { useBleStore } from '@/shared/store/bleStore';
import { useDeviceStore } from '@/shared/store/deviceStore';
import log from '@/shared/utils/log';
import { useFocusEffect } from 'expo-router';
import React from 'react';
import Distance from './layout/Distance';
import IRAarray from './layout/IRArray';
import LinePosition from './layout/LinePosition';
import SafetyGuard from './layout/SafetyGuard';

export default function SensorTab() {
  const mode = useDeviceStore((s) => s.activeMode);
  const send = useBleStore((s) => s.sendAndReceive);
  const safetyMode = useDeviceStore((s) => s.safetyMode);

  useFocusEffect(
    React.useCallback(() => {
      console.log('mount');
      const startStreaming = async () => {
        send(PacketBuilder.startUSstream(), 500).catch((e) => log(e, 'error'));
        if (mode === 'line') {
          send(PacketBuilder.startIRstream(), 500).catch((e) => log(e, 'error'));
        }
      };

      const stopStreaming = async () => {
        send(PacketBuilder.endUSstream(), 500).catch((e) => log(e, 'error'));
        if (mode === 'line') {
          send(PacketBuilder.endIRstream(), 500).catch((e) => log(e, 'error'));
        }
      };

      startStreaming();
      return () => {
        console.log('unmount');
        stopStreaming();
      };
    }, [mode])
  );

  return (
    <PageContainer>
      {mode === 'line' && (
        <>
          <LinePosition />
          <IRAarray />
        </>
      )}
      <Distance />
      {safetyMode && <SafetyGuard />}
    </PageContainer>
  );
}

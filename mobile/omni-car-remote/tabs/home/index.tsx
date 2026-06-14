import { PacketBuilder } from '@/shared/ble/BlePacketBuilder';
import { useOptimisticUpdate } from '@/shared/ble/hook/useOptimisticUpdate';
import Button from '@/shared/components/ui/Button';
import PageContainer from '@/shared/components/ui/PageContainer';
import SectionLabel from '@/shared/components/ui/SectionLabel';
import { useBleStore } from '@/shared/store/bleStore';
import { DeviceStore, useDeviceStore } from '@/shared/store/deviceStore';
import { useCallback } from 'react';
import { View } from 'react-native';
import SpeedSlider from './components/SpeedSlider';
import LineFollowControl from './layout/LineFollowControl';
import ManualControl from './layout/ManualControl';
import ObjectFollowControl from './layout/ObjectFollowControl';

export default function HomeTab() {
  const mode = useDeviceStore((s) => s.activeMode);
  const send = useBleStore((s) => s.sendAndReceive);
  const sendStop = useBleStore((s) => s.send);
  const { update } = useOptimisticUpdate();
  const handleMode = useCallback(
    (v: DeviceStore['activeMode']) => {
      update(
        () => useDeviceStore.getState().activeMode,
        (v) => useDeviceStore.getState().setActiveMode(v),
        v,
        () => {
          if (v === 'line') {
            update(
              () => useDeviceStore.getState().speed,
              (v) => useDeviceStore.getState().setSpeed(v),
              60,
              () => send(PacketBuilder.setBase(60), 500)
            );
            sendStop(PacketBuilder.setLineModule());
          }
          if (v === 'object') return send(PacketBuilder.setObjectModule(), 500);
          if (v === 'manual') return send(PacketBuilder.setManualModule(), 500);
        }
      );
    },
    [update]
  );

  return (
    <PageContainer>
      <SectionLabel label="mode" />
      <View className="flex-row gap-buttonGap mb-sectionSpacing">
        <Button
          label="manual"
          variant="primary"
          onPress={() => handleMode('manual')}
          state={mode === 'manual' ? 'selected' : 'default'}
          className="flex-1"
        />
        <Button
          label="line-follow"
          variant="primary"
          onPress={() => handleMode('line')}
          state={mode === 'line' ? 'selected' : 'default'}
          className="flex-1"
        />
      </View>
      <View className="flex-row gap-buttonGap mb-sectionSpacing">
        <Button
          label="object-following"
          variant="primary"
          onPress={() => handleMode('object')}
          state={mode === 'object' ? 'selected' : 'default'}
          className="flex-1"
        />
      </View>
      {mode === 'manual' && <ManualControl />}
      {mode === 'line' && <LineFollowControl />}
      {mode === 'object' && <ObjectFollowControl />}
      <SpeedSlider />
      <Button
        label="emergency stop"
        variant="danger"
        onPress={() => sendStop(PacketBuilder.stop())}
      />
    </PageContainer>
  );
}

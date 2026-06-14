import Toggle from '@/shared/components/ui/Toggle';
import { useCallback } from 'react';
import { Text, View } from 'react-native';
import { PacketBuilder } from '../ble/BlePacketBuilder';
import { useOptimisticUpdate } from '../ble/hook/useOptimisticUpdate';
import { useBleStore } from '../store/bleStore';
import { useDeviceStore } from '../store/deviceStore';

export default function AvoidToggle() {
  const value = useDeviceStore((s) => s.safetyMode);
  const { update } = useOptimisticUpdate();
  const send = useBleStore((s) => s.sendAndReceive);

  const handleAvoidToggle = useCallback(() => {
    update(
      () => useDeviceStore.getState().safetyMode,
      (v) => useDeviceStore.getState().setSafetyMode(v),
      !value,
      () => send(PacketBuilder.setSafetyMode(!value ? 1 : 0), 1000)
    );
  }, [value, update]);

  return (
    <View className="flex-row items-center gap-1">
      <Text className="text-muted text-[9px] font-medium">AVOID</Text>
      <Toggle value={value} onChange={handleAvoidToggle} />
    </View>
  );
}

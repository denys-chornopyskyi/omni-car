import { PacketBuilder } from '@/shared/ble/BlePacketBuilder';
import { useOptimisticUpdate } from '@/shared/ble/hook/useOptimisticUpdate';
import Button from '@/shared/components/ui/Button';
import { useBleStore } from '@/shared/store/bleStore';
import { useCallback, useState } from 'react';
import { View } from 'react-native';

type mode = 'start' | 'stop';

export default function ObjectFollowControl() {
  const [active, setActive] = useState<mode>('start');
  const send = useBleStore((s) => s.sendAndReceive);
  const { update } = useOptimisticUpdate();
  const handleStateMode = useCallback(
    (v: mode) => {
      update(
        () => active,
        (newValue) => setActive(newValue),
        v,
        () => {
          if (v === 'start') return send(PacketBuilder.startFollowing(), 500);
          if (v === 'stop') return send(PacketBuilder.stopFollowing(), 500);
        }
      );
    },
    [update]
  );

  return (
    <View className="flex-col gap-4 py-10">
      <Button
        label="start"
        onPress={() => handleStateMode('start')}
        variant={active === 'start' ? 'neonGreen' : 'disabled'}
      />
      <Button
        label="stop"
        onPress={() => handleStateMode('stop')}
        variant={active === 'stop' ? 'neonRed' : 'disabled'}
      />
    </View>
  );
}

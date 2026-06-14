import SectionLabel from '@/shared/components/ui/SectionLabel';
import { useDeviceStore } from '@/shared/store/deviceStore';
import { useMemo } from 'react';
import { Text, View } from 'react-native';
import PositionBar from '../components/PositionBar';

export default function LinePosition() {
  const ir = useDeviceStore((s) => s.ir);

  const position = useMemo(() => {
    const sum = ir[0] + ir[1] + ir[2] + ir[3] + ir[4];
    if (sum === 0) return 0;
    console.log('hello');
    return (-2 * ir[0] + -1 * ir[1] + 0 * ir[2] + 1 * ir[3] + 2 * ir[4]) / sum;
  }, [ir]);

  return (
    <View className="mb-[19px]">
      <SectionLabel label="line position" />
      <View className="bg-surface py-5 rounded-[10px] px-[10px]">
        <PositionBar value={position} min={-2} max={2} />
        <View className="flex-row justify-between pt-2">
          <Text className="text-muted font-mono">-2</Text>
          <Text className="text-muted font-mono">-1</Text>
          <Text className="text-muted font-mono">0</Text>
          <Text className="text-muted font-mono">+1</Text>
          <Text className="text-muted font-mono">+2</Text>
        </View>
      </View>
    </View>
  );
}

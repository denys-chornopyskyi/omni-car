import SectionLabel from '@/shared/components/ui/SectionLabel';
import { useState } from 'react';
import { Text, View } from 'react-native';
import PositionBar from '../components/PositionBar';

export default function LinePosition() {
  const [position, setPosition] = useState(0);

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

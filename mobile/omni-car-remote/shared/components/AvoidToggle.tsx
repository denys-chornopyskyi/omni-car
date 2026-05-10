import Toggle from '@/shared/components/ui/Toggle';
import { useState } from 'react';
import { Text, View } from 'react-native';

export default function AvoidToggle() {
  const [avoid, setAvoid] = useState(false);

  return (
    <View className="flex-row items-center gap-1">
      <Text className="text-muted text-[9px] font-medium">AVOID</Text>
      <Toggle value={avoid} onChange={setAvoid} />
    </View>
  );
}

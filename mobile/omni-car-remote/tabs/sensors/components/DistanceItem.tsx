import FontAwesome from '@expo/vector-icons/FontAwesome';
import { Text, View } from 'react-native';

export default function DistanceItem({
  value,
  side,
  arrowDirection,
}: {
  value: number;
  side: 'Front' | 'Left' | 'Right' | 'Back';
  arrowDirection:
    | 'long-arrow-up'
    | 'long-arrow-down'
    | 'long-arrow-right'
    | 'long-arrow-left';
}) {
  return (
    <View className="flex-row flex-1 bg-surface px-inlinePadding py-[10px] gap-1 rounded-[10px]">
      <View className="justify-around">
        <FontAwesome name={arrowDirection} color="white" size={20} />
      </View>
      <View>
        <Text className="text-muted text-[8px] font-medium">{side}</Text>
        <Text className="text-secondary text-[14px] font-mono">
          {value}
          <Text className="text-muted text-[8px] font-medium">cm</Text>
        </Text>
      </View>
    </View>
  );
}

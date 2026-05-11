import cn from '@/shared/utils/cn';
import FontAwesome from '@expo/vector-icons/FontAwesome';
import { Text, View } from 'react-native';

export default function SafetyGuardItem({
  side,
  arrowDirection,
  isClear,
}: {
  side: 'Front' | 'Left' | 'Right' | 'Back';
  isClear: boolean;
  arrowDirection:
    | 'long-arrow-up'
    | 'long-arrow-down'
    | 'long-arrow-right'
    | 'long-arrow-left';
}) {
  return (
    <View className="bg-surface flex-1 items-center py-[10px] rounded-[10px] flex-col">
      <FontAwesome size={20} color="white" name={arrowDirection} />
      <Text className="text-muted text-[8px] font-medium">{side}</Text>
      <Text
        className={cn(
          'text-neonGreen font-medium text-[9px]',
          isClear ? 'text-neonGreen' : 'text-neonRed'
        )}>
        {isClear ? 'Clear' : 'Blocked'}
      </Text>
    </View>
  );
}

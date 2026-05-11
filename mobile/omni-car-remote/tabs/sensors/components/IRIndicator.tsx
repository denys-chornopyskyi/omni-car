import cn from '@/shared/utils/cn';
import { View } from 'react-native';
import Animated, { SharedValue, useAnimatedStyle } from 'react-native-reanimated';

export default function IRIndicator({
  sharedValue,
  isActive,
}: {
  sharedValue: SharedValue<number>;
  isActive: boolean;
}) {
  const animatedStyle = useAnimatedStyle(() => ({
    height: sharedValue.value,
  }));

  return (
    <View className="flex-1 h-full justify-end">
      <Animated.View
        className={cn('rounded-[3px]', isActive ? 'bg-neonRed' : 'bg-neonGreen')}
        style={[animatedStyle]}></Animated.View>
    </View>
  );
}

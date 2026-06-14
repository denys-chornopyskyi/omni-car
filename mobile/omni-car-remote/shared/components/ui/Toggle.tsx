import { useEffect, useRef } from 'react';
import { Animated, Pressable } from 'react-native';

export default function Toggle({
  value,
  onChange,
}: {
  value: boolean;
  onChange: (v: boolean) => void;
}) {
  const anim = useRef(new Animated.Value(value ? 1 : 0)).current;

  const toggle = () => {
    onChange(!value);
  };

  useEffect(() => {
    Animated.spring(anim, {
      toValue: value ? 1 : 0,
      useNativeDriver: true,
    }).start();
  }, [value, anim]);

  const translateX = anim.interpolate({
    inputRange: [0, 1],
    outputRange: [2, 20],
  });

  return (
    <Pressable
      onPress={() => onChange(!value)}
      className={`w-12 h-7 rounded-full justify-center ${value ? 'bg-primary border-secondary' : 'bg-panel border-border'} border-[1px]`}>
      <Animated.View
        className={`w-5 h-5 rounded-full ${value ? 'bg-white' : 'bg-muted'}`}
        style={{ transform: [{ translateX }] }}
      />
    </Pressable>
  );
}

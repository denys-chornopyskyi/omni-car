import cn from '@/shared/utils/cn';
import { useState } from 'react';
import { Text, View } from 'react-native';
import { Gesture, GestureDetector } from 'react-native-gesture-handler';

type BaseProps = {
  label: string | React.ReactNode;
  onPress?: () => void;
  onPressIn?: () => void;
  onPressOut?: () => void;
  className?: string;
  textClass?: string;
};

type ButtonType = BaseProps &
  (
    | { variant: 'primary'; state?: ButtonState }
    | {
        variant: 'danger' | 'neonGreen' | 'neonRed' | 'disabled' | 'custom';
        state?: never;
      }
  );

type ButtonState = 'selected' | 'default';

function getContainerStyle(variant: string, state?: ButtonState) {
  return cn(
    'rounded-lg border-[1px] py-buttonPadding border-white',
    variant === 'primary' && state === 'selected' && 'border-primary bg-[#8A2BE20A]',
    variant === 'primary' && state !== 'selected' && 'border-border',
    variant === 'danger' &&
      'border-danger py-stopButtonPadding px-stopButtonPadding bg-[#FF3B5C23]',
    variant === 'neonGreen' &&
      'border-neonGreen py-stopButtonPadding px-stopButtonPadding',
    variant === 'neonRed' && 'border-danger py-stopButtonPadding px-stopButtonPadding',
    variant === 'disabled' && 'border-border py-stopButtonPadding px-stopButtonPadding'
  );
}

function getTextStyle(variant: string, state?: ButtonState) {
  return cn(
    'text-center text-[10px] font-semibold text-white',
    variant === 'primary' && state === 'selected' && 'text-primary',
    variant === 'primary' && state !== 'selected' && 'color-muted',
    variant === 'danger' && 'text-danger text-left text-[16px] font-bold',
    variant === 'neonGreen' && 'text-neonGreen text-left text-[16px] font-bold',
    variant === 'neonRed' && 'text-left text-[16px] font-bold text-danger',
    variant === 'disabled' && 'text-left text-[16px] font-bold text-muted'
  );
}

export default function Button({
  label,
  onPress,
  onPressIn,
  onPressOut,
  variant,
  state,
  className,
  textClass,
}: ButtonType) {
  const [press, setPress] = useState(false);

  const gesture = Gesture.Pan()
    .runOnJS(true)
    .activateAfterLongPress(0)
    .onStart(() => {
      onPressIn?.();
      setPress(true);
    })
    .onFinalize(() => {
      onPressOut?.();
      onPress?.();
      setPress(false);
    });

  return (
    <GestureDetector gesture={gesture}>
      <View
        className={cn(
          getContainerStyle(variant, state),
          className,
          press && 'opacity-70'
        )}>
        <Text className={cn(getTextStyle(variant, state), textClass)}>
          {typeof label === 'string' ? label.toUpperCase() : label}
        </Text>
      </View>
    </GestureDetector>
  );
}

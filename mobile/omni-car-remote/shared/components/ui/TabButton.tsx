import { BottomTabBarProps } from '@react-navigation/bottom-tabs';
import { Pressable, Text } from 'react-native';

type Props = {
  route: BottomTabBarProps['state']['routes'][number];
  navigation: BottomTabBarProps['navigation'];
  isFocused: boolean;
  label: string;
};

const TabButton = ({ route, navigation, isFocused, label }: Props) => {
  const onPress = () => {
    const event = navigation.emit({
      type: 'tabPress',
      target: route.key,
      canPreventDefault: true,
    });

    if (!isFocused && !event.defaultPrevented) {
      navigation.navigate(route.name);
    }
  };

  return (
    <Pressable
      onPress={onPress}
      className={`py-blockPadding flex-1 border-b-[1px] ${isFocused ? 'border-primary' : 'border-muted'}`}>
      <Text
        className={`font-semibold text-[10px] text-center ${isFocused ? 'text-primary' : 'text-muted'}`}>
        {label}
      </Text>
    </Pressable>
  );
};

export default TabButton;

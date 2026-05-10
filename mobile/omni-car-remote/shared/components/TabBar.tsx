import { BottomTabBarProps } from '@react-navigation/bottom-tabs';
import { View } from 'react-native';
import { useTabBar } from '../context/TabBarContext';
import TabButton from './ui/TabButton';

export function TabBar({ state, navigation }: BottomTabBarProps) {
  const { setTabBarTop } = useTabBar();
  return (
    <View
      className="flex-row absolute top-0"
      onLayout={(e) => setTabBarTop(e.nativeEvent.layout.height)}>
      {state.routes.map((route, index) => {
        return (
          <TabButton
            key={route.key}
            route={route}
            navigation={navigation}
            isFocused={state.index === index}
            label={route.name === 'index' ? 'CONTROL' : route.name.toUpperCase()}
          />
        );
      })}
    </View>
  );
}

export default TabBar;

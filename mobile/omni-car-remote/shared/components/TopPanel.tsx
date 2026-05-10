import { View } from 'react-native';
import AvoidToggle from './AvoidToggle';
import ConnectionButton from './ui/ConnectionButton';
import Logo from './ui/Logo';

export default function TopPanel() {
  return (
    <View className="flex-row w-full py-blockPadding justify-between px-inlinePadding">
      <Logo />
      <View className="flex-row gap-[6px]">
        <AvoidToggle />
        <ConnectionButton />
      </View>
    </View>
  );
}

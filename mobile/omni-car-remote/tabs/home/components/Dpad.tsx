import { View } from 'react-native';
import DpadButton from './DpadButton';

export default function Dpad() {
  return (
    <View className="flex-col gap-5 items-center py-20">
      <View className="flex-row gap-5">
        <DpadButton rotation={7} />
        <DpadButton rotation={0} />
        <DpadButton rotation={1} />
      </View>
      <View className="flex-row gap-5">
        <DpadButton rotation={6} />
        <DpadButton dot />
        <DpadButton rotation={2} />
      </View>
      <View className="flex-row gap-5">
        <DpadButton rotation={5} />
        <DpadButton rotation={4} />
        <DpadButton rotation={3} />
      </View>
    </View>
  );
}

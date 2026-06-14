import { View } from 'react-native';
import Dpad from '../components/Dpad';

export default function ManualControl() {
  return (
    <View className="flex-col gap-5">
      <Dpad />
    </View>
  );
}

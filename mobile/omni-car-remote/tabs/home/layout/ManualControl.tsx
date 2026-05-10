import Button from '@/shared/components/ui/Button';
import { View } from 'react-native';
import Dpad from '../components/Dpad';
import SpeedSlider from '../components/SpeedSlider';

export default function ManualControl() {
  return (
    <View className="flex-col gap-5">
      <Dpad />
      <SpeedSlider />
      <Button label="emergency stop" variant="danger" />
    </View>
  );
}

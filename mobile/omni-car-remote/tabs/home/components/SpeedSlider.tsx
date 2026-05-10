import Slider from '@react-native-community/slider';
import { useState } from 'react';
import { Text, View } from 'react-native';

export default function SpeedSlider() {
  const [speed, setSpeed] = useState(100);

  return (
    <View className="flex-row items-center gap-2 mb-sectionSpacing ">
      <Text className="text-[14px] font-mono color-secondary">Speed</Text>
      <View className="flex-1">
        <Slider
          minimumValue={0}
          maximumValue={255}
          value={speed}
          step={1}
          onValueChange={(v) => setSpeed(v)}
          thumbTintColor="#38BDF8"
          minimumTrackTintColor="#334155"
          maximumTrackTintColor="#334155"
        />
      </View>
      <Text className=" text-primary font-mono">{speed}</Text>
    </View>
  );
}

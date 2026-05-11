import { View } from 'react-native';

export default function PositionBar({
  value,
  min = 0,
  max = 255,
}: {
  value: number;
  min?: number;
  max?: number;
}) {
  function getPercent(value: number, min: number, max: number) {
    const percent = ((value - min) / (max - min)) * 100;
    return Math.max(0, Math.min(100, percent));
  }

  return (
    <View className="w-full px-1 bg-surface border-panel border-2 rounded-full">
      <View className="w-full relative">
        <View
          className="bg-neonGreen rounded-full absolute -translate-y-1/2 -translate-x-1/2 w-4 h-4"
          style={{ left: `${getPercent(value, min, max)}%` }}></View>
      </View>
    </View>
  );
}

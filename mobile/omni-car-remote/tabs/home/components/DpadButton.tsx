import Button from '@/shared/components/ui/Button';
import FontAwesome from '@expo/vector-icons/FontAwesome';
import { View } from 'react-native';

export default function DpadButton({
  rotation = 0,
  dot,
}: {
  rotation?: number;
  dot?: boolean;
}) {
  return (
    <Button
      label={
        dot ? (
          <View className="w-[10px] h-[10px] bg-white rounded-full"></View>
        ) : (
          <View style={{ transform: [{ rotate: `${rotation * 45}deg` }] }}>
            <FontAwesome size={20} name="long-arrow-up" color="white" />
          </View>
        )
      }
      variant="custom"
      className="w-dpadSize h-dpadSize border-border border-[1px] rounded-[12px] justify-center items-center bg-panel"
    />
  );
}

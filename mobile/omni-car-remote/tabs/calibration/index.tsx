import PageContainer from '@/shared/components/ui/PageContainer';
import { useDeviceStore } from '@/shared/store/deviceStore';
import { View } from 'react-native';
import LineFollowForm from './components/LineFollowForm';
import MotionForm from './components/MotionForm';
import ObjectFollowerForm from './components/ObjectFollowerForm';

export default function CalibrationTab() {
  const activeMode = useDeviceStore((s) => s.activeMode);
  return (
    <PageContainer>
      <View className="flex-row gap-4 flex-wrap">
        <MotionForm />
        {/* {activeMode === 'object' && <ObjectFollowerForm />} */}
        <ObjectFollowerForm />
        <LineFollowForm />
      </View>
    </PageContainer>
  );
}

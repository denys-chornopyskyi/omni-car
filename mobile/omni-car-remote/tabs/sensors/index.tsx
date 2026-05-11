import PageContainer from '@/shared/components/ui/PageContainer';
import Distance from './layout/Distance';
import IRAarray from './layout/IRArray';
import LinePosition from './layout/LinePosition';
import SafetyGuard from './layout/SafetyGuard';

export default function SensorTab() {
  return (
    <PageContainer>
      <LinePosition />
      <IRAarray />
      <Distance />
      <SafetyGuard />
    </PageContainer>
  );
}

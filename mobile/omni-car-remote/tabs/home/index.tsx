import Button from '@/shared/components/ui/Button';
import PageContainer from '@/shared/components/ui/PageContainer';
import SectionLabel from '@/shared/components/ui/SectionLabel';
import { useState } from 'react';
import { View } from 'react-native';
import LineFollowControl from './layout/LineFollowControl';
import ManualControl from './layout/ManualControl';

const modes = ['manual', 'line-follow'] as const;

export default function HomeTab() {
  const [mode, setMode] = useState<(typeof modes)[number]>('manual');

  return (
    <PageContainer>
      <SectionLabel label="mode" />
      <View className="flex-row gap-buttonGap mb-sectionSpacing">
        <Button
          label="manual"
          variant="primary"
          onPress={() => setMode('manual')}
          state={mode === 'manual' ? 'selected' : 'default'}
          className="flex-1"
        />
        <Button
          label="line-follow"
          variant="primary"
          onPress={() => setMode('line-follow')}
          state={mode === 'line-follow' ? 'selected' : 'default'}
          className="flex-1"
        />
      </View>
      {mode === 'manual' && <ManualControl />}
      {mode === 'line-follow' && <LineFollowControl />}
    </PageContainer>
  );
}

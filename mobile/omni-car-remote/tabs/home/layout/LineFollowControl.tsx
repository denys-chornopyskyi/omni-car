import Button from '@/shared/components/ui/Button';
import { useState } from 'react';
import { View } from 'react-native';

type mode = 'start' | 'stop';

export default function LineFollowControl() {
  const [active, setActive] = useState<mode>('start');

  return (
    <View className="flex-col gap-buttonGap">
      <Button
        label="start"
        onPress={() => setActive('stop')}
        variant={active === 'start' ? 'neonGreen' : 'disabled'}
      />
      <Button
        label="stop"
        onPress={() => setActive('start')}
        variant={active === 'stop' ? 'neonRed' : 'disabled'}
      />
    </View>
  );
}

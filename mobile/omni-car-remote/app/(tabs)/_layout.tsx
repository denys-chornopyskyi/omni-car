import React from 'react';
import Header from '../../shared/layout/Header';

import MainTabs from '@/shared/layout/MainTabs';
import { View } from 'react-native';
import { useSafeAreaInsets } from 'react-native-safe-area-context';

export default function HomeScreen() {
  const insest = useSafeAreaInsets();

  return (
    <>
      <View className="flex-1 bg-background">
        <Header style={{ paddingTop: insest.top }} />
        <MainTabs />
      </View>
    </>
  );
}

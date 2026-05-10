import { PropsWithChildren } from 'react';
import { View } from 'react-native';

export default function PageContainer({ children }: PropsWithChildren) {
  return <View className="py-4 px-inlinePadding">{children}</View>;
}

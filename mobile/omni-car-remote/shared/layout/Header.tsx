import { View, ViewProps } from 'react-native';
import TelemetryPanel from '../components/TelemetryPanel';
import TopPanel from '../components/TopPanel';

export default function Header({ style, className, onLayout }: ViewProps) {
  return (
    <View style={style} className={className} onLayout={onLayout}>
      <TopPanel />
      <TelemetryPanel />
    </View>
  );
}

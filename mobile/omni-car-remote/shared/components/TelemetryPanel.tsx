import React, { useMemo } from 'react';
import { View } from 'react-native';
import { useBleStore } from '../store/bleStore';
import { useDeviceStore } from '../store/deviceStore';
import TelemetryItem, { TelemetryItemProps } from './ui/TelemetryItem';

const TelemetryPanel = () => {
  const speed = useDeviceStore((s) => s.speed);
  const connected = useBleStore((s) => s.connected);
  const activeMode = useDeviceStore((s) => s.activeMode);

  const telemetry: TelemetryItemProps[] = useMemo(
    () => [
      { label: 'Mode', value: activeMode },
      { label: 'Speed', value: String(speed) },
      { label: 'Status', value: connected ? 'Ready' : 'Not Ready' },
    ],
    [speed, connected, activeMode]
  );

  return (
    <View className="flex-row">
      {telemetry.map(({ label, value }, index) => (
        <TelemetryItem key={index} label={label} value={value} />
      ))}
    </View>
  );
};
export default TelemetryPanel;

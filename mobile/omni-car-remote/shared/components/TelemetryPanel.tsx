import React, { useMemo } from 'react';
import { View } from 'react-native';
import { useBleStore } from '../store/bleStore';
import { useDeviceStore } from '../store/deviceStore';
import TelemetryItem, { TelemetryItemProps } from './ui/TelemetryItem';

const telemetry: TelemetryItemProps[] = [
  { label: 'Speed', value: '120 km/h' },
  { label: 'Battery', value: '80%' },
  { label: 'Temp', value: '32°C' },
];

const TelemetryPanel = () => {
  const speed = useDeviceStore((s) => s.speed);
  const connected = useBleStore((s) => s.connected);

  const telemetry: TelemetryItemProps[] = useMemo(
    () => [
      { label: 'Speed', value: String(speed) },
      { label: 'Status', value: connected ? 'Ready' : 'Not Ready' },
    ],
    [speed, connected]
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

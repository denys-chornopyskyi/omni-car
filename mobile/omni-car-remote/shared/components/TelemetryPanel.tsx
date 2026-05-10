import React from 'react';
import { View } from 'react-native';
import TelemetryItem, { TelemetryItemProps } from './ui/TelemetryItem';

const telemetry: TelemetryItemProps[] = [
  { label: 'Speed', value: '120 km/h' },
  { label: 'Battery', value: '80%' },
  { label: 'Temp', value: '32°C' },
];

const TelemetryPanel = () => {
  return (
    <View className="flex-row">
      {telemetry.map(({ label, value }, index) => (
        <TelemetryItem key={index} label={label} value={value} />
      ))}
    </View>
  );
};
export default TelemetryPanel;

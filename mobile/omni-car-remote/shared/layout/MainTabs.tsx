import { Tabs } from 'expo-router';
import TabBar from '../components/TabBar';
import { useTabBar } from '../context/TabBarContext';

export default function MainTabs() {
  const { tabBarTop } = useTabBar();
  return (
    <Tabs
      tabBar={(props) => <TabBar {...props} />}
      screenOptions={{
        headerShown: false,
        sceneStyle: { backgroundColor: '#0F172A', paddingTop: tabBarTop + 20 },
      }}>
      <Tabs.Screen name="index" />
      <Tabs.Screen name="calibration" />
      <Tabs.Screen name="sensors" />
      <Tabs.Screen name="terminal" />
    </Tabs>
  );
}

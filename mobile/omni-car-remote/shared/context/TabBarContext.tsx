import React, { createContext, useContext, useState } from 'react';

type TabBarContextType = {
  tabBarTop: number;
  setTabBarTop: (h: number) => void;
};

const TabBarContext = createContext<TabBarContextType>({
  tabBarTop: 0,
  setTabBarTop: () => {},
});

export function TabBarProvider({ children }: { children: React.ReactNode }) {
  const [tabBarTop, setTabBarTop] = useState(0);
  return (
    <TabBarContext.Provider value={{ tabBarTop, setTabBarTop }}>
      {children}
    </TabBarContext.Provider>
  );
}

export const useTabBar = () => useContext(TabBarContext);

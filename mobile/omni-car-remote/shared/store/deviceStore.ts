import { create } from 'zustand';

type DeviceStore = {
  speed: number;
  // updateValues: (data: Partial<DeviceStore>) => void; //??
  setSpeed: (value: number) => void;
};

export const useDeviceStore = create<DeviceStore>((set) => ({
  speed: 100,
  setSpeed: (value) => set({ speed: value }),
}));

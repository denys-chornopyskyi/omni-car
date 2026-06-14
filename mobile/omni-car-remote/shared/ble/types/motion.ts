export const MotionButton = {
  Center: 10,
  UpLeft: 20,
  Up: 30,
  UpRight: 40,
  Left: 50,
  Right: 60,
  DownLeft: 70,
  Down: 80,
  DownRight: 90,
} as const;

export type MotionButtonValue = (typeof MotionButton)[keyof typeof MotionButton];

export const ButtonState = {
  Pressed: 1,
  Released: 0,
} as const;

export type ButtonStateValue = (typeof ButtonState)[keyof typeof ButtonState];

export type ButtonValues =
  | 10
  | 11
  | 20
  | 21
  | 30
  | 31
  | 40
  | 41
  | 50
  | 51
  | 60
  | 61
  | 70
  | 71
  | 80
  | 81
  | 90
  | 91;

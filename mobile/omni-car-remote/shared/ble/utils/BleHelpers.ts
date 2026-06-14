import { ButtonState, MotionButton } from '../types/motion';

export function BuildMotionPayload(
  btn: keyof typeof MotionButton,
  state: keyof typeof ButtonState
): number[] {
  return [MotionButton[btn] + ButtonState[state]];
}

type ReverseMap<T extends Record<string, string | number>> = {
  [K in keyof T as T[K]]: K;
};

export function reverseMap<T extends Record<string, string | number>>(
  obj: T
): ReverseMap<T> {
  return Object.fromEntries(Object.entries(obj).map(([a, b]) => [b, a])) as ReverseMap<T>;
}

import { ButtonState, MotionButton } from '../types/motion';

export function BuildMotionPayload(
  btn: keyof typeof MotionButton,
  state: keyof typeof ButtonState
): number[] {
  return [MotionButton[btn] + ButtonState[state]];
}

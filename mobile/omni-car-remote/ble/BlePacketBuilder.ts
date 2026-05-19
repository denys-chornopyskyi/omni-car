import { PacketType, PacketTypeValue, PROTOCOL } from './types/bleProtocol';
import { ButtonState, MotionButton } from './types/motion';
import { BuildMotionPayload } from './utils/BleHelpers';

export class PacketBuilder {
  static build(type: PacketTypeValue, payload: number[] | Uint8Array): Uint8Array {
    const typeValue = type;
    const len = payload.length;
    const total = 1 + 1 + 1 + len + 1;
    const buf = new Uint8Array(total);
    let i = 0;

    buf[i++] = PROTOCOL.START;
    buf[i++] = typeValue;
    buf[i++] = len;

    for (const byte of payload) {
      buf[i++] = byte;
    }

    buf[i++] = PROTOCOL.END;

    return buf;
  }

  static buildMotionPacket(
    btn: keyof typeof MotionButton,
    state: keyof typeof ButtonState
  ) {
    return this.build(PacketType.motion, BuildMotionPayload(btn, state));
  }
}

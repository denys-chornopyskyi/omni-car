import { PacketType, PacketTypeValue, PROTOCOL, ValueType } from './types/bleProtocol';
import { ButtonState, MotionButton } from './types/motion';
import { ParamCmd } from './types/paramCmd';
import { SimpleCmd } from './types/simpleCmd';
import { BuildMotionPayload } from './utils/BleHelpers';

export class PacketBuilder {
  static build(
    type: PacketTypeValue,
    payload: number[] | Uint8Array,
    needsResponse: boolean
  ): Uint8Array {
    const typeValue = needsResponse ? type | 0x80 : type;
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

  private static floatToBytes(value: number): number[] {
    const buf = new ArrayBuffer(4);
    new DataView(buf).setFloat32(0, value, true);
    return Array.from(new Uint8Array(buf));
  }

  private static uint8ToBytes(value: number): number[] {
    value = Math.round(value);
    value = Math.max(0, Math.min(255, value));

    return [value];
  }

  private static boolToBytes(value: number): number[] {
    return [value ? 1 : 0];
  }

  static buildMotionPacket(
    btn: keyof typeof MotionButton,
    state: keyof typeof ButtonState
  ) {
    return this.build(PacketType.motion, BuildMotionPayload(btn, state), false);
  }

  static stop() {
    return this.build(PacketType.simpleCmd, [SimpleCmd.stop], true);
  }
  static setManualModule() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['module:manual']], true);
  }
  static setLineModule() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['module:line']], true);
  }
  static getBase() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['base?']], true);
  }
  static getCK() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['cK?']], true);
  }
  static getModule() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['module?']], true);
  }
  static getCrs() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['crs?']], true);
  }
  static getCre() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['cre?']], true);
  }
  // static toggleSafetyMode() {
  //   return this.build(PacketType.simpleCmd, [SimpleCmd.safetymode], true);
  // }
  static getSafetyMode() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['safetymode?']], true);
  }
  static getThreshold() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['threshold?']], true);
  }
  static startIRstream() {
    return this.build(PacketType.simpleCmd, [SimpleCmd.sIRs], true);
  }
  static endIRstream() {
    return this.build(PacketType.simpleCmd, [SimpleCmd.eIRs], true);
  }
  static startUSstream() {
    return this.build(PacketType.simpleCmd, [SimpleCmd.sUSs], true);
  }
  static endUSstream() {
    return this.build(PacketType.simpleCmd, [SimpleCmd.eUSs], true);
  }
  static startLine() {
    return this.build(PacketType.simpleCmd, [SimpleCmd.startLine], true);
  }
  static endLine() {
    return this.build(PacketType.simpleCmd, [SimpleCmd.endLine], true);
  }
  static setObjectModule() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['module:object']], true);
  }
  static startFollowing() {
    return this.build(PacketType.simpleCmd, [SimpleCmd.startFollowing], true);
  }
  static stopFollowing() {
    return this.build(PacketType.simpleCmd, [SimpleCmd.stopFollowing], true);
  }
  static getMinDist() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['minDist?']], true);
  }
  static getMaxDist() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['maxDist?']], true);
  }
  static getRadius() {
    return this.build(PacketType.simpleCmd, [SimpleCmd['radius?']], true);
  }

  private static param(
    code: keyof typeof ParamCmd,
    value: number,
    valueType: ValueType,
    withResponse = true
  ): Uint8Array {
    let bytes: number[] = [];
    switch (valueType) {
      case ValueType.uint8:
        bytes = [...PacketBuilder.uint8ToBytes(value)];
        break;
      case ValueType.float:
        bytes = [...PacketBuilder.floatToBytes(value)];
        break;
      case ValueType.bool:
        bytes = [...PacketBuilder.boolToBytes(value)];
        break;
    }

    return PacketBuilder.build(
      PacketType.paramCmd,
      [ParamCmd[code], ...bytes],
      withResponse
    );
  }

  static setBase(v: number) {
    return this.param('base', v, ValueType.uint8, true);
  }
  // static setModule(v: keyof typeof ModuleType) {
  //   return this.param('', ModuleType[v], ValueType.uint8, true);
  // }
  static setThreshold(v: number) {
    return this.param('threshold', v, ValueType.uint8, true);
  }
  static setCK(v: number) {
    return this.param('cK', v, ValueType.float, true);
  }
  // ## TODO
  static setMinDist(v: number) {
    return this.param('minDist', v, ValueType.uint8, true);
  }
  static setMaxDist(v: number) {
    return this.param('maxDist', v, ValueType.uint8, true);
  }
  static setSafetyMode(v: number) {
    return this.param('safetymode', v, ValueType.uint8, true);
  }
  static setCrs(v: number) {
    return this.param('crs', v, ValueType.float, true);
  }
  static setCre(v: number) {
    return this.param('cre', v, ValueType.float, true);
  }
  static setRadius(v: number) {
    return this.param('radius', v, ValueType.float, true);
  }
}

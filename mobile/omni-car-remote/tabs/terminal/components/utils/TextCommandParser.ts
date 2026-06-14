import { PacketBuilder } from '@/shared/ble/BlePacketBuilder';
import { ParamCmd } from '@/shared/ble/types/paramCmd';
import { SimpleCmd } from '@/shared/ble/types/simpleCmd';

// interface ParseResult {
//   packet: Uint8Array;
//   withResponse: boolean;
// }

// type ModuleCmd = 'module:manual' | 'module:line';

type TerminalSimpleCmd = keyof typeof SimpleCmd;

export class TextCommandParser {
  static parse(input: string): Uint8Array | null {
    const cmd = input.trim();

    const simple: Record<TerminalSimpleCmd, () => Uint8Array> = {
      'base?': () => PacketBuilder.getBase(),
      stop: () => PacketBuilder.stop(),
      'module:manual': () => PacketBuilder.setManualModule(),
      'module:line': () => PacketBuilder.setLineModule(),
      'module?': () => PacketBuilder.getModule(),
      'cK?': () => PacketBuilder.getCK(),
      'safetymode?': () => PacketBuilder.getSafetyMode(),
      'cre?': () => PacketBuilder.getCre(),
      'crs?': () => PacketBuilder.getCrs(),
      'threshold?': () => PacketBuilder.getThreshold(),
      sIRs: () => PacketBuilder.startIRstream(),
      eIRs: () => PacketBuilder.endIRstream(),
      sUSs: () => PacketBuilder.startUSstream(),
      eUSs: () => PacketBuilder.endUSstream(),
      'module:object': () => PacketBuilder.setObjectModule(),
      startLine: () => PacketBuilder.startUSstream(),
      endLine: () => PacketBuilder.endLine(),
      startFollowing: () => PacketBuilder.startFollowing(),
      stopFollowing: () => PacketBuilder.stopFollowing(),
      'minDist?': () => PacketBuilder.getMinDist(),
      'maxDist?': () => PacketBuilder.getMaxDist(),
      'radius?': () => PacketBuilder.getRadius(),
    };

    if (simple[cmd as TerminalSimpleCmd]) {
      return simple[cmd as TerminalSimpleCmd]();
    }

    const sep = cmd.indexOf(':');
    if (sep === -1) return null;

    const key = cmd.slice(0, sep).trim();
    const value = cmd.slice(sep + 1).trim();

    const params: Record<keyof typeof ParamCmd, (v: string) => Uint8Array> = {
      base: (v) => PacketBuilder.setBase(parseInt(v, 10)),
      cK: (v) => PacketBuilder.setCK(parseInt(v, 10)),
      threshold: (v) => PacketBuilder.setThreshold(parseInt(v, 10)),
      safetymode: (v) => PacketBuilder.setSafetyMode(parseInt(v, 10)),
      minDist: (v) => PacketBuilder.setMinDist(parseInt(v, 10)),
      maxDist: (v) => PacketBuilder.setMaxDist(parseInt(v, 10)),
      crs: (v) => PacketBuilder.setCrs(parseFloat(v)),
      cre: (v) => PacketBuilder.setCre(parseFloat(v)),
      radius: (v) => PacketBuilder.setRadius(parseFloat(v)),
    };

    if (!params[key as keyof typeof ParamCmd]) return null;

    return params[key as keyof typeof ParamCmd](value);
  }
}

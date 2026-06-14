import { useBleStore } from '@/shared/store/bleStore';
import { useDeviceStore } from '@/shared/store/deviceStore';
import log from '@/shared/utils/log';
import {
  InPacketType,
  InPacketTypePayloadMap,
  InPacketTypeValue,
  PacketTypeReverse,
  PacketTypeValue,
  PROTOCOL,
} from './types/bleProtocol';
import { ParamCmdValue, ParamTypeReverse } from './types/paramCmd';
import { SimpleCmdReverse, SimpleCmdValue } from './types/simpleCmd';

type Handler<T extends InPacketTypeValue> = (payload: InPacketTypePayloadMap[T]) => void;

type Handlers = {
  [T in InPacketTypeValue]?: Handler<T>;
};

export interface ParsedPacket {
  type: PacketTypeValue;
  cmd: SimpleCmdValue | ParamCmdValue;
  value: number | null;
}

class BleParser {
  private _buf = new Uint8Array(0);
  private _handlers: Handlers = {};

  on<T extends keyof typeof InPacketType>(
    type: T,
    handler: Handler<(typeof InPacketType)[T]>
  ): this {
    const packetType = InPacketType[type] as (typeof InPacketType)[typeof type];
    this._handlers[packetType] = handler as Handlers[typeof packetType];
    return this;
  }

  feed(bytes: Uint8Array): void {
    const merged = new Uint8Array(this._buf.length + bytes.length);
    merged.set(this._buf);
    merged.set(bytes, this._buf.length);
    this._buf = merged;
    this._parse();
  }

  private _parse() {
    while (this._buf.length >= 3) {
      const start = this._buf.indexOf(PROTOCOL.START);
      if (start === -1) {
        this._buf = new Uint8Array(0);
        return;
      }
      if (start !== 0) {
        this._buf = this._buf.slice(start);
      }

      const plen = this._buf[2];
      const total = 1 + 1 + 1 + plen + 1;

      if (this._buf.length < total) return;
      if (this._buf.indexOf(PROTOCOL.END) !== total - 1) {
        this._buf = this._buf.slice(1);
        continue;
      }

      const type = this._buf[1] as InPacketTypeValue;
      const payload = this._buf.slice(3, 3 + plen);

      this._dispatch(type, payload);
      this._buf = this._buf.slice(total);
    }
  }

  private _dispatch(type: InPacketTypeValue, payload: Uint8Array) {
    switch (type) {
      case InPacketType.Success: {
        const handler = this._handlers[InPacketType.Success];
        if (!handler) return;
        handler({ response: payload });
        console.log('clear pendingRequest');
        useBleStore.getState().pendingRequest = null;
        break;
      }
      case InPacketType.Error: {
        const handler = this._handlers[InPacketType.Error];
        if (!handler) return;
        handler({ response: payload });
        console.log('clear pendingRequest');
        useBleStore.getState().pendingRequest = null;
        break;
      }
      case InPacketType.IRSensor: {
        const handler = this._handlers[InPacketType.IRSensor];
        if (!handler) return;
        handler({ response: payload });
        break;
      }
      case InPacketType.USSensor: {
        const handler = this._handlers[InPacketType.USSensor];
        if (!handler) return;
        handler({ response: payload });
        break;
      }
      default:
        log('unknown inPacketType', 'error');
        useBleStore.getState().pendingRequest = null;
        break;
    }
  }
}

const parser = new BleParser();

parser
  .on('IRSensor', ({ response }) => {
    // let msg = '';
    // response.forEach((v) => {
    //   msg += v;
    // });
    // log(msg, 'info');
    console.log(`IR: ${Array.from(response)}`);
    useDeviceStore.getState().setIr(Array.from(response));
  })
  .on('USSensor', ({ response }) => {
    const sensors = Array.from(response);
    console.log(`US: ${sensors}`);
    useDeviceStore.getState().setSensors(sensors[0], sensors[1], sensors[2], sensors[3]);
  })
  .on('Success', ({ response }) => {
    const pendingRequest = useBleStore.getState().pendingRequest;
    if (!pendingRequest) return;
    clearTimeout(pendingRequest.timeout);

    const packetType = response[0] as PacketTypeValue;
    const packetTypeName = PacketTypeReverse[packetType];

    const cmd =
      packetTypeName === 'simpleCmd'
        ? (response[1] as SimpleCmdValue)
        : (response[1] as ParamCmdValue);

    const cmdName =
      packetTypeName === 'simpleCmd'
        ? SimpleCmdReverse[cmd as keyof typeof SimpleCmdReverse]
        : ParamTypeReverse[cmd as keyof typeof ParamTypeReverse];

    const valueType = response[2];

    let valueTypeName;
    let value = null;
    switch (valueType) {
      case 0:
        valueTypeName = 'None';
        break;
      case 1:
        valueTypeName = 'Uint8';
        const UintView = new DataView(response.buffer, 3, 1);
        value = UintView.getUint8(0);
        break;
      case 2:
        valueTypeName = 'float';
        const FloatView = new DataView(response.buffer, 3, 4);
        value = FloatView.getFloat32(0, true);
        break;
    }

    const parsedMsg = `Packet Type: ${packetTypeName}; \nCommand: ${cmdName} \nValueType: ${
      valueTypeName === 'None' ? valueTypeName : `${valueTypeName}; \nValue: ${value}`
    }`;
    log(parsedMsg, 'success');
    const packet: ParsedPacket = {
      value: value,
      type: packetType,
      cmd: cmd,
    };

    pendingRequest.resolve(packet);
  })
  .on('Error', ({ response }) => {
    const pendingRequest = useBleStore.getState().pendingRequest;
    if (!pendingRequest) return;
    clearTimeout(pendingRequest.timeout);

    // const packetType = response[0] as PacketTypeValue;
    // const packetTypeName = PacketTypeReverse[packetType];

    // const valueArr = response.slice(1);

    // const parsedMsg = `${packetTypeName}=[${valueArr}]`;
    const parsedMsg = `Error Received Payload ${response}`;

    pendingRequest.reject(parsedMsg);
  });

export default parser;

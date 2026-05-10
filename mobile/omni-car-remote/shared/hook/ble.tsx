// import { useCallback, useRef, useState } from 'react';
// import { Pressable, ScrollView, Text, TextInput, View } from 'react-native';
// import { Device } from 'react-native-ble-plx';

// // const manager = new BleManager();

// const SERVICE_UUID = '6e400001-b5a3-f393-e0a9-e50e24dcca9e';
// const NOTIFY_UUID = '6e400003-b5a3-f393-e0a9-e50e24dcca9e';
// const WRITE_UUID = '6e400002-b5a3-f393-e0a9-e50e24dcca9e';

// export default function BleDebugScreen() {
//   const [logs, setLogs] = useState<string[]>([]);
//   const [connected, setConnected] = useState(false);
//   const [message, setMessage] = useState('');
//   const deviceRef = useRef<Device | null>(null);
//   const scrollRef = useRef<ScrollView>(null);

//   const log = (msg: string) => {
//     console.log(msg);
//     setLogs((prev) => [...prev, msg]);
//     setTimeout(() => scrollRef.current?.scrollToEnd({ animated: true }), 100);
//   };

//   const connect = useCallback(async () => {
//     log('1. Ожидаем инициализации BLE...');

//     await new Promise<void>((resolve, reject) => {
//       const sub = manager.onStateChange((state) => {
//         log(`Состояние: ${state}`);
//         if (state === 'PoweredOn') {
//           sub.remove();
//           resolve();
//         }
//         if (state === 'PoweredOff') {
//           sub.remove();
//           reject(new Error('Bluetooth выключен'));
//         }
//         if (state === 'Unauthorized') {
//           sub.remove();
//           reject(new Error('Нет разрешения'));
//         }
//       }, true);
//     });

//     log('2. Начало сканирования...');
//     manager.startDeviceScan(null, null, async (error, scanned) => {
//       if (error) {
//         log(`❌ Ошибка сканирования: ${error.message}`);
//         return;
//       }

//       log(`Найдено: ${scanned?.name ?? 'без имени'} (${scanned?.rssi} dBm)`);

//       if (!scanned?.name?.includes('ESP32')) return;

//       manager.stopDeviceScan();
//       log('3. ESP найден, подключаемся...');

//       try {
//         const device = await scanned.connect();
//         log('4. Подключились ✅');

//         await device.discoverAllServicesAndCharacteristics();
//         log('5. Сервисы обнаружены ✅');

//         const services = await device.services();
//         log(`6. Сервисов: ${services.length}`);

//         for (const service of services) {
//           log(`   Сервис: ${service.uuid}`);
//           const chars = await service.characteristics();
//           for (const char of chars) {
//             log(`   Характеристика: ${char.uuid}`);
//             log(
//               `     readable: ${char.isReadable} writable: ${char.isWritableWithResponse} notifiable: ${char.isNotifiable}`
//             );
//           }
//         }

//         log('7. Подписываемся на уведомления...');
//         device.monitorCharacteristicForService(SERVICE_UUID, NOTIFY_UUID, (err, char) => {
//           if (err) {
//             log(`❌ Ошибка получения: ${err.message}`);
//             return;
//           }
//           const bytes = Uint8Array.from(atob(char!.value!), (c) => c.charCodeAt(0));
//           const text = new TextDecoder().decode(bytes);
//           log(`📨 Получено: "${text}" [${bytes.join(', ')}]`);
//         });

//         device.onDisconnected(() => {
//           log('❌ Устройство отключилось');
//           setConnected(false);
//           deviceRef.current = null;
//         });

//         deviceRef.current = device;
//         setConnected(true);
//         log('8. Готов к работе ✅');
//       } catch (e: any) {
//         log(`❌ Ошибка подключения: ${e.message}`);
//       }
//     });
//   }, []);

//   const send = useCallback(async () => {
//     if (!deviceRef.current || !message.trim()) return;

//     log(`📤 Отправляем: "${message}"`);

//     try {
//       const bytes = new TextEncoder().encode(message);
//       const base64 = btoa(String.fromCharCode(...bytes));

//       await deviceRef.current.writeCharacteristicWithResponseForService(
//         SERVICE_UUID,
//         WRITE_UUID,
//         base64
//       );

//       log('✅ Отправлено');
//       setMessage('');
//     } catch (e: any) {
//       log(`❌ Ошибка отправки: ${e.message}`);
//     }
//   }, [message]);

//   const sendAndReceive = useCallback(async () => {
//     if (!deviceRef.current || !message.trim()) return;

//     log(`📤 Отправляем (ждём ответ): "${message}"`);

//     try {
//       const response = await Promise.race([
//         new Promise<string>((resolve, reject) => {
//           const sub = deviceRef.current!.monitorCharacteristicForService(
//             SERVICE_UUID,
//             NOTIFY_UUID,
//             (err, char) => {
//               if (err) {
//                 sub.remove();
//                 reject(err);
//                 return;
//               }
//               const bytes = Uint8Array.from(atob(char!.value!), (c) => c.charCodeAt(0));
//               const text = new TextDecoder().decode(bytes);
//               sub.remove();
//               resolve(text);
//             }
//           );

//           const bytes = new TextEncoder().encode(message);
//           const base64 = btoa(String.fromCharCode(...bytes));
//           deviceRef.current!.writeCharacteristicWithResponseForService(
//             SERVICE_UUID,
//             WRITE_UUID,
//             base64
//           );
//         }),

//         new Promise<never>((_, reject) =>
//           setTimeout(() => reject(new Error('Таймаут 3с')), 3000)
//         ),
//       ]);

//       log(`📨 Ответ: "${response}"`);
//       setMessage('');
//     } catch (e: any) {
//       log(`❌ ${e.message}`);
//     }
//   }, [message]);

//   return (
//     <View className="flex-1 bg-slate-900 p-4 pt-16">
//       <Text className="text-white text-xl font-bold mb-4">BLE Debug</Text>

//       <Pressable
//         onPress={connect}
//         disabled={connected}
//         className={`rounded-xl p-4 mb-4 ${connected ? 'bg-green-700' : 'bg-primary'}`}>
//         <Text className="text-white text-center font-medium">
//           {connected ? '✅ Подключено' : 'Подключить'}
//         </Text>
//       </Pressable>

//       <ScrollView ref={scrollRef} className="flex-1 bg-slate-800 rounded-xl p-3 mb-4">
//         {logs.map((l, i) => (
//           <Text
//             key={i}
//             className={`text-sm font-mono mb-1 ${
//               l.includes('❌')
//                 ? 'text-red-400'
//                 : l.includes('✅')
//                   ? 'text-green-400'
//                   : l.includes('📨')
//                     ? 'text-blue-400'
//                     : l.includes('📤')
//                       ? 'text-yellow-400'
//                       : 'text-slate-300'
//             }`}>
//             {l}
//           </Text>
//         ))}
//       </ScrollView>

//       <View className="flex-row gap-2">
//         <TextInput
//           value={message}
//           onChangeText={setMessage}
//           placeholder="Введи сообщение..."
//           placeholderTextColor="#64748b"
//           className="flex-1 bg-slate-800 text-white rounded-xl px-4 py-3"
//         />
//         <Pressable
//           onPress={send}
//           disabled={!connected}
//           className="bg-primary rounded-xl px-4 justify-center">
//           <Text className="text-white font-medium">Send</Text>
//         </Pressable>
//         <Pressable
//           onPress={sendAndReceive}
//           disabled={!connected}
//           className="bg-slate-700 rounded-xl px-4 justify-center">
//           <Text className="text-white font-medium">Ask</Text>
//         </Pressable>
//       </View>
//     </View>
//   );
// }

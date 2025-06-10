import 'dart:async';
import 'dart:convert';
// import 'dart:nativewrappers/_internal/vm/lib/typed_data_patch.dart';
import 'dart:typed_data';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';

class BluetoothManager {
  static final BluetoothManager _instance = BluetoothManager._internal();
  factory BluetoothManager() => _instance;
  BluetoothManager._internal();

 final String targetDeviceName = "Fire Wheels";
  BluetoothDevice? _device;
  BluetoothCharacteristic? _writeChar;

  Future<void> start() async {
    print("🔍 Rozpoczynanie skanowania...");
    FlutterBluePlus.startScan(timeout: const Duration(seconds: 15));

    FlutterBluePlus.scanResults.listen((results) async {
      for (ScanResult result in results) {
        print("rezultat skanowania:  ${result.device.platformName}");
        if (result.device.platformName == targetDeviceName) {
          print("✅ Znaleziono urządzenie: ${result.device.platformName}");
          FlutterBluePlus.stopScan();

          _device = result.device;
          await _device!.connect(timeout: const Duration(seconds: 10));
          print("✅ Połączono");

          await _discoverServicesAndSetCharacteristic();
          print("✅ ustawiono charakterystyki");

          print("⏳ Odczekaj 3 sekundy...");
          await Future.delayed(const Duration(seconds: 3));

          //await sendCommand("+++DATA\n"); //tu dać komendę na tryb danych
        }
      }
    });
  }

  Future<void> _discoverServicesAndSetCharacteristic() async {
    if (_device == null) {
      print("⚠️ Urządzenie nie jest dostępne.");
      return;
    }

    List<BluetoothService> services = await _device!.discoverServices();

    final writeUUID = Guid("0000ffe1-0000-1000-8000-00805f9b34fb");

    for (var service in services) {
      for (var characteristic in service.characteristics) {
        print("🔍 Sprawdzam charakterystykę: ${characteristic.uuid}");
        if (characteristic.uuid == writeUUID && characteristic.properties.write) {
          _writeChar = characteristic;
          print("✅ Znaleziono i ustawiono poprawną charakterystykę zapisu: ${characteristic.uuid}");
          return;
        }
      }
    }

    print("⚠️ Nie znaleziono odpowiedniej charakterystyki zapisu.");
  }


  bool _ready = true;

  Future<void> sendCommand(Int8List command) async {
    print("🔍 Entering sendCommand with command: $command");
    if (_writeChar == null) return;
    await _writeChar!.write(command);
    print("📤 Wysłano komendę: $command");
    _ready = true;
  }

  bool get isReady => _ready;

}

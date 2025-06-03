import 'dart:async';
import 'dart:convert';
import 'package:flutter_blue_plus/flutter_blue_plus.dart';

class BluetoothManager {
  static final BluetoothManager _instance = BluetoothManager._internal();
  factory BluetoothManager() => _instance;
  BluetoothManager._internal();

 final String targetDeviceName = "FireWheels";
  BluetoothDevice? _device;
  BluetoothCharacteristic? _writeChar;

  Future<void> start() async {
    print("🔍 Rozpoczynanie skanowania...");
    FlutterBluePlus.startScan(timeout: const Duration(seconds: 5));

    FlutterBluePlus.scanResults.listen((results) async {
      for (ScanResult result in results) {
        if (result.device.name == targetDeviceName) {
          print("✅ Znaleziono urządzenie: ${result.device.name}");
          FlutterBluePlus.stopScan();

          _device = result.device;
          await _device!.connect(timeout: const Duration(seconds: 5));

          await _discoverServicesAndSetCharacteristic();

          print("⏳ Odczekaj 3 sekundy...");
          await Future.delayed(const Duration(seconds: 3));

          await sendCommand("+++DATA\n"); //tu dać komendę na tryb danych
        }
      }
    });
  }

  Future<void> _discoverServicesAndSetCharacteristic() async {
    if (_device == null) return;

    List<BluetoothService> services = await _device!.discoverServices();

    for (var service in services) {
      for (var characteristic in service.characteristics) {
        if (characteristic.properties.write) {
          _writeChar = characteristic;
          print("✍️ Charakterystyka zapisu ustawiona.");
          return;
        }
      }
    }

    print("⚠️ Nie znaleziono odpowiedniej charakterystyki zapisu.");
  }

  bool _ready = false;

  Future<void> sendCommand(String command) async {
    if (_writeChar == null) return;

    List<int> bytes = utf8.encode(command);
    await _writeChar!.write(bytes, withoutResponse: true);
    print("📤 Wysłano komendę: $command");

    if (command.trim() == "+++DATA") {
      _ready = true;
    }
  }

  bool get isReady => _ready;

}

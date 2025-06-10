import 'dart:async';
import 'dart:typed_data';
import 'package:flutter/cupertino.dart';
import 'bluetooth_manager.dart';
import 'data_frame.dart';
import '../models/app_state.dart';
import 'package:synchronized/synchronized.dart';

class DataSender {
  static final DataSender _instance = DataSender._internal();

  factory DataSender() => _instance;

  DataSender._internal();

  Timer? _timer;
  BuildContext? _context;

  void attachContext(BuildContext context) {
    _context = context;
  }

  void startSending() {
    stopSending();
    print("✅ DataSender: startSending wywołanse");

    final appState = AppState.of(_context!);


    final lock = Lock();

    _timer = Timer.periodic(const Duration(milliseconds: 100), (timer) async {
      await lock.synchronized(() async {
        final frameCopy = appState.frameNotifier.value.clone();
        final frameBytes = frameCopy.toBytes();
        print("❗FRAME SNAPSHOT before send: $frameBytes");
        final frameBytesCopy = Int8List.fromList(frameBytes);
        BluetoothManager().sendCommand(frameBytesCopy);
        print("❗FRAME SNAPSHOT after send: $frameBytes");
      });
    });
  }

  void stopSending() {
    _timer?.cancel();
    _timer = null;
    print("⛔️ DataSender: stopSending wywołane");
  }
}
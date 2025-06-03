import 'dart:async';
import 'bluetooth_manager.dart';
import 'data_frame.dart';

class DataSender {
  static final DataSender _instance = DataSender._internal();
  factory DataSender() => _instance;
  DataSender._internal();

  Timer? _timer;
  DataFrame Function()? _frameProvider;

  void setFrameProvider(DataFrame Function() provider) {
    _frameProvider = provider;
  }

  void startSending() {
    stopSending();
    _timer = Timer.periodic(const Duration(milliseconds: 20), (timer) {
      if (BluetoothManager().isReady) {
        final cmd = _frameProvider!();
        BluetoothManager().sendCommand(cmd.debugString());
      }
    });
  }

  void stopSending() {
    _timer?.cancel();
    _timer = null;
  }
}

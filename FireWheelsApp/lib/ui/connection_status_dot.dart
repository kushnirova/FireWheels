import 'package:flutter/material.dart';
import '../bluetooth/bluetooth_manager.dart';

class ConnectionStatusDot extends StatefulWidget {
  const ConnectionStatusDot({super.key});

  @override
  State<ConnectionStatusDot> createState() => _ConnectionStatusDotState();
}

class _ConnectionStatusDotState extends State<ConnectionStatusDot> {
  final BluetoothManager _bt = BluetoothManager();
  late final Stream _refresh;

  @override
  void initState() {
    super.initState();
    _refresh = Stream.periodic(const Duration(milliseconds: 500));
  }

  @override
  Widget build(BuildContext context) {
    return StreamBuilder(
      stream: _refresh,
      builder: (context, snapshot) {
        Color color;
        if (_bt.isReady) {
          color = Color(0xFF00D21B);
        }
        else {
          color = Colors.red;
        }

        return Positioned(
          child:
          Container(
            margin: const EdgeInsets.all(8),
            width: 12,
            height: 12,
            decoration: BoxDecoration(
              shape: BoxShape.circle,
              color: color,
            ),
          )
        );
      },
    );
  }
}

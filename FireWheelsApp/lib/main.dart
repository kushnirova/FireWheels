import 'package:firewheelsapp/ui/info_overlay.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:provider/provider.dart';

import 'bluetooth/bluetooth_manager.dart';
import 'bluetooth/data_sender.dart';
import 'models/app_state.dart';
import 'ui/control_header.dart';
import 'ui/control_buttons_mode.dart';
import 'ui/control_tilt_mode.dart';

void main() async {
  WidgetsFlutterBinding.ensureInitialized();

  await SystemChrome.setPreferredOrientations([
    DeviceOrientation.landscapeLeft,
    DeviceOrientation.landscapeRight,
  ]);

  runApp(
    ChangeNotifierProvider(
      create: (_) => AppState(),
      child: const MyApp(),
    ),
  );
  BluetoothManager().start();
  DataSender().startSending();
}

class MyApp extends StatelessWidget {
  const MyApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'FireWheels',
      debugShowCheckedModeBanner: false,
      home: Scaffold(
        backgroundColor: const Color(0xFF140030),
        body: SafeArea(
          child: Column(
            children: [
              const ControlHeader(),

              Expanded(
                child: Consumer<AppState>(
                  builder: (context, state, _) {
                    DataSender().setFrameProvider(() => state.frame);

                    return Stack(
                      children: [
                        state.mode == ControlMode.buttons
                            ? const ControlButtonsMode()
                            : const ControlTiltMode(),
                        const InfoOverlay(),
                      ],
                    );
                  },
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}

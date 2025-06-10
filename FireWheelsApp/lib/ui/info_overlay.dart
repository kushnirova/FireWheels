import 'dart:async';
import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import 'package:sensors_plus/sensors_plus.dart';
import '../models/app_state.dart';

class InfoOverlay extends StatefulWidget {
  const InfoOverlay({super.key});

  @override
  State<InfoOverlay> createState() => _InfoOverlayState();
}

class _InfoOverlayState extends State<InfoOverlay> {
  late StreamSubscription _accelerometerSub;
  double x = 0.0;
  double y = 0.0;
  double a = 0.0;
  double b = 0.0;

  @override
  void initState() {
    super.initState();
    _accelerometerSub = accelerometerEvents.listen((event) {
      setState(() {
        final appState = Provider.of<AppState>(context, listen: false);
        final newFrame = appState.frameNotifier.value.clone();
        if (newFrame.buttons & 32 == 32) {
          x = -event.x;
          y = event.y;
        } else {
          x = 0;
          y = 0;
        }
        a = x * 10;
        b = y * 10;
        appState.setSpeedFromTilt(a.clamp(-100, 100).toInt(), b.clamp(-100, 100).toInt());
      });
    });
  }

  @override
  void dispose() {
    _accelerometerSub.cancel();
    super.dispose();
  }

  int getX() {
    return (x * 10).toInt();
  }

  int getY() {
    return (y * 10).toInt();
  }

  @override
  Widget build(BuildContext context) {
    final state = context.watch<AppState>();

    if (state.mode == ControlMode.buttons) {
      return Positioned(
        top: 45,
        right: 380,
        child: Text(
          '${state.speed}',
          style: const TextStyle(
            color: Colors.white,
            fontSize: 52,
            fontWeight: FontWeight.bold,
            fontStyle: FontStyle.italic,
          ),
        ),
      );
    } else {
      return const SizedBox.shrink();
    }
  }
}
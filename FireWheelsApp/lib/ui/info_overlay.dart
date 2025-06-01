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

  @override
  void initState() {
    super.initState();
    _accelerometerSub = accelerometerEvents.listen((event) {
      setState(() {
        x = event.x;
        y = event.y;
      });
    });
  }

  @override
  void dispose() {
    _accelerometerSub.cancel();
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    final state = context.watch<AppState>();

    if (state.mode == ControlMode.buttons) {
      return Positioned(
        top: 40,
        right: 380,
        child: Text(
          '${state.speed}',
          style: const TextStyle(
            color: Colors.white,
            fontSize: 50,
            fontWeight: FontWeight.bold,
            fontStyle: FontStyle.italic,
          ),
        ),
      );
    } else if (state.mode == ControlMode.tilt) {
      return Center(
        child: Text(
          'x=${x.toStringAsFixed(2)},\ny=${y.toStringAsFixed(2)}',
          style: const TextStyle(color: Colors.white, fontSize: 20),
        ),
      );
    } else {
      return const SizedBox.shrink();
    }
  }
}

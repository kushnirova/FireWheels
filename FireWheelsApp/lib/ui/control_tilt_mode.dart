import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../models/app_state.dart';

class ControlTiltMode extends StatelessWidget {
  const ControlTiltMode({super.key});

  @override
  Widget build(BuildContext context) {
    final appState = Provider.of<AppState>(context, listen: false);
    return Stack(
      children: [
        Align(
          alignment: Alignment.bottomCenter,
          child: Padding(
            padding: const EdgeInsets.only(bottom: 30.0),
            child: SizedBox(
              width: 137,
              height: 137,
              child: ElevatedButton(
                onPressed: () {
                  final newFrame = appState.frameNotifier.value.clone();
                  newFrame.setX_tilt(0);
                  newFrame.setBit(0, true);
                  newFrame.setY(0);
                  appState.frameNotifier.value = newFrame;
                  appState.notifyListeners();
                  print("=========SPEED ${appState.speed}=====X ${newFrame.x}====Y ${newFrame.y}====K ${newFrame.buttons & 32}=====B ${newFrame.buttons & 1}==== BTN");
                  print("STOP=================================B ${newFrame.buttons & 1}======================= BTN");
                },
                style: ElevatedButton.styleFrom(
                  backgroundColor: Color(0xFF2E00C6),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(20),
                  ),
                  padding: EdgeInsets.zero,
                ),
                child: Image.asset(
                  './images/stop.jpg',
                  width: 80,
                  height: 60,
                  fit: BoxFit.contain,
                ),
              ),
            ),
          ),
        ),

        Positioned(
          top: 0,
          left: 30.0,
          child: SizedBox(
            width: 57.0,
            height: 57.0,
            child: FloatingActionButton(
              backgroundColor: appState.lightsOn ? const Color(0xffa75402) : const Color(0xFF1C007A),
              onPressed: () => appState.toggleLights(),
              shape: const CircleBorder(),
              child: Image.asset(
                appState.lightsOn ? './images/swiatla_on.jpg' : './images/swiatla.jpg',
                width: 40,
                height: 40,
                fit: BoxFit.contain,
              ),
            ),
          ),
        ),

        Positioned(
          top: 72.0,
          left: 30.0,
          child: SizedBox(
            width: 57.0,
            height: 57.0,
            child: FloatingActionButton(
              backgroundColor: appState.hazardsOn ? const Color(0xffa75402) : const Color(0xFF1C007A),
              onPressed: () => appState.toggleHazards(),
              shape: const CircleBorder(),
              child: Image.asset(
                appState.hazardsOn ? './images/awaryjne_on.jpg' : './images/awaryjne.jpg',
                width: 40,
                height: 40,
                fit: BoxFit.contain,
              ),
            ),
          ),
        ),

        Positioned(
          top: 0.0,
          right: 30.0,
          child: SizedBox(
            width: 57.0,
            height: 57.0,
            child: GestureDetector(
              onTapDown: (_) {
                final newFrame = appState.frameNotifier.value.clone();
                newFrame.setBit(3, true);
                appState.frameNotifier.value = newFrame;
                appState.notifyListeners();
                print("KRZYCZY======================================================================");
                print("x ${newFrame.x}, y ${newFrame.y}");
              },
              onTapUp: (_) {
                final newFrame = appState.frameNotifier.value.clone();
                newFrame.setBit(3, false);
                appState.frameNotifier.value = newFrame;
                appState.notifyListeners();
                print("nie krzyczy======================================================================");
              },
              onTapCancel: () {
                final newFrame = appState.frameNotifier.value.clone();
                newFrame.setBit(3, false);
                appState.frameNotifier.value = newFrame;
                appState.notifyListeners();
                print("nie krzyczy======================================================================");
              },
              child: FloatingActionButton(
                onPressed: () {},
                backgroundColor: const Color(0xFF1C007A),
                shape: const CircleBorder(),
                child: Image.asset(
                  './images/klakson.jpg',
                  width: 40,
                  height: 40,
                  fit: BoxFit.contain,
                ),
              ),
            ),
          ),
        ),

        Positioned(
          top: 72.0,
          right: 30.0,
          child: SizedBox(
            width: 57.0,
            height: 57.0,
            child: FloatingActionButton(
              backgroundColor: appState.driftOn ? const Color(0xffa75402) : const Color(0xFF1C007A),
              onPressed: () => appState.toggleDrift(),
              shape: const CircleBorder(),
              child: Image.asset(
                appState.driftOn ? './images/drift_on.jpg' : './images/drift.jpg',
                width: 40,
                height: 40,
                fit: BoxFit.contain,
              ),
            ),
          ),
        ),

        Positioned(
          bottom: 30,
          right: 30,
          child: SizedBox(
            width: 72.0,
            height: 72.0,
            child: ElevatedButton(
              onPressed: () {
                final newFrame = appState.frameNotifier.value.clone();
                newFrame.setBit(0, false);
                newFrame.setBit(5, true);
                newFrame.setX(appState.speed * 10);
                appState.frameNotifier.value = newFrame;
                appState.notifyListeners();
                print("PRZÓD=========SPEED ${appState.speed}=====X ${newFrame.x}====Y ${newFrame.y}====K ${newFrame.buttons & 32}=====B ${newFrame.buttons & 1}==== BTN");
              },
              style: ElevatedButton.styleFrom(
                backgroundColor: const Color(0xFF00D21B),
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(20.0),
                ),
                padding: EdgeInsets.zero,
              ),
              child: Image.asset(
                './images/przod.jpg',
                width: 60,
                height: 60,
                fit: BoxFit.contain,
              ),
            ),
          ),
        ),
      ],
    );
  }
}
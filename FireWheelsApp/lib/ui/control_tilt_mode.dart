import 'package:flutter/material.dart';
import 'package:provider/provider.dart';

import '../models/app_state.dart';

class ControlTiltMode extends StatelessWidget {
  const ControlTiltMode({super.key});

  @override
  Widget build(BuildContext context) {
    final state = Provider.of<AppState>(context);
    return Stack(
      children: [
        Align(
          alignment: Alignment.bottomCenter,
          child: Padding(
            padding: const EdgeInsets.only(bottom: 30.0),
            child: SizedBox( // przycisk STOP
              width: 137,
              height: 137,
              child: ElevatedButton(
                onPressed: () {
                  // Tutaj można dodać funkcjonalność przycisku
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

        Positioned( // przycisk światła
          top: 0,
          left: 30.0,
          child: SizedBox(
            width: 57.0,
            height: 57.0,
            child: FloatingActionButton(
              backgroundColor: state.lightsOn ? const Color(0xffa75402) : const Color(0xFF1C007A),
              onPressed: () => state.toggleLights(),
              shape: const CircleBorder(),
              child: Image.asset(
                state.lightsOn ? './images/swiatla_on.jpg' : './images/swiatla.jpg',
                width: 40,
                height: 40,
                fit: BoxFit.contain,
              ),
            ),
          ),
        ),

        Positioned( // przycisk awaryjne
          top: 72.0,
          left: 30.0,
          child: SizedBox(
            width: 57.0,
            height: 57.0,
            child: FloatingActionButton(
              backgroundColor: state.hazardsOn ? const Color(0xffa75402) : const Color(0xFF1C007A),
              onPressed: () => state.toggleHazards(),
              shape: const CircleBorder(),
              child: Image.asset(
                state.hazardsOn ? './images/awaryjne_on.jpg' : './images/awaryjne.jpg',
                width: 40,
                height: 40,
                fit: BoxFit.contain,
              ),
            ),
          ),
        ),

        Positioned( // przycisk klakson
          top: 0.0,
          right: 30.0,
          child: SizedBox(
            width: 57.0,
            height: 57.0,
            child: FloatingActionButton(
              onPressed: () {
                // Tutaj możesz dodać akcję po naciśnięciu przycisku
              },
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

        Positioned( // przycisk drift
          top: 72.0,
          right: 30.0,
          child: SizedBox(
            width: 57.0,
            height: 57.0,
            child: FloatingActionButton(
              backgroundColor: state.driftOn ? const Color(0xffa75402) : const Color(0xFF1C007A),
              onPressed: () => state.toggleDrift(),

              shape: const CircleBorder(),
              child: Image.asset(
                state.driftOn ? './images/drift_on.jpg' : './images/drift.jpg',
                width: 40,
                height: 40,
                fit: BoxFit.contain,
              ),
            ),
          ),
        ),

        // Tył
        Positioned( // przycisk tył
          bottom: 30,
          left: 30,
          child: SizedBox(
            width: 72.0,
            height: 72.0,
            child: ElevatedButton(
              onPressed: () {
                // Tutaj możesz dodać akcję po naciśnięciu przycisku
              },
              style: ElevatedButton.styleFrom(
                backgroundColor: const Color(0xFF00D21B),
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(20.0),
                ),
                padding: EdgeInsets.zero,
              ),
              child: Image.asset(
                './images/tyl.jpg',
                width: 60,
                height: 60,
                fit: BoxFit.contain,
              ),
            ),
          ),
        ),

        // Przód
        Positioned( // przycisk przód
          bottom: 30,
          right: 30,
          child: SizedBox(
            width: 72.0,
            height: 72.0,
            child: ElevatedButton(
              onPressed: () {
                // Tutaj możesz dodać akcję po naciśnięciu przycisku
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

  Widget _circleButton(VoidCallback onPressed) {
    return SizedBox(
      width: 57.0,
      height: 57.0,
      child: FloatingActionButton(
        onPressed: onPressed,
        backgroundColor: const Color(0xFF1C007A),
        shape: const CircleBorder(),
        child: null,
      ),
    );
  }
}

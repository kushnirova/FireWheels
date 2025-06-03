import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../models/app_state.dart';

class ControlButtonsMode extends StatelessWidget {
  const ControlButtonsMode({super.key});

  @override
  Widget build(BuildContext context) {
    final state = Provider.of<AppState>(context);
    final frame = Provider.of<AppState>(context).frame;
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
                  frame.setX(0);
                  frame.setBit(0, true);
                  frame.setY(0);
                  print("=========SPEED ${state.speed}=====X ${frame.x}====Y ${frame.y}====K ${frame.buttons&32}=====B ${frame.buttons&1}==== BTN");
                  print("STOP=================================B ${frame.buttons&1}======================= BTN");
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
            child: GestureDetector(
              onTapDown: (_) {
                frame.setBit(3, true);
                print("KRZYCZY======================================================================${frame.buttons&8}");
              },
              onTapUp: (_) {
                frame.setBit(3, false);
                print("nie krzyczy======================================================================${frame.buttons&8}");
              },
              onTapCancel: () {
                frame.setBit(3, false);
                print("nie krzyczy======================================================================${frame.buttons&8}");
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

        Positioned( // przycisk tył
          bottom: 30,
          left: 30,
          child: SizedBox(
            width: 72.0,
            height: 72.0,
            child: ElevatedButton(
              onPressed: () {
                frame.setBit(0, false);
                frame.setBit(5, false);
                frame.setX(state.speed*10);

                print("TYŁ======SPEED ${state.speed}====X ${frame.x}=====Y ${frame.y}=====K ${frame.buttons&32}=====B ${frame.buttons&1}== BTN");
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

        Positioned( // przycisk przód
          bottom: 30,
          right: 30,
          child: SizedBox(
            width: 72.0,
            height: 72.0,
            child: ElevatedButton(
              onPressed: () {
                //state.unblock();
                frame.setBit(0, false);
                frame.setBit(5, true);
                frame.setX(state.speed*10);
                print("PRZÓD=========SPEED ${state.speed}=====X ${frame.x}====Y ${frame.y}====K ${frame.buttons&32}=====B ${frame.buttons&1}==== BTN");
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

        Positioned( // przycisk prawo
          bottom: 95,
          right: 200,
          child: SizedBox(
            width: 72.0,
            height: 72.0,
            child: GestureDetector(
              onTapDown: (_) {
                frame.setY(100);
                print('PRAWO=========SPEED ${state.speed}========X ${frame.x}==========Y ${frame.y}================ BTN');
              },
              onTapUp: (_) {
                frame.setY(0);
                print('PRAWO=========SPEED ${state.speed}========X ${frame.x}==========Y ${frame.y}================ BTN');
              },
              onTapCancel: () {
                frame.setY(0);
                print('PRAWO=========SPEED ${state.speed}========X ${frame.x}==========Y ${frame.y}================ BTN');
              },
              child: ElevatedButton(
                onPressed: () {
                  frame.setY(-100);
                },
                style: ElevatedButton.styleFrom(
                  backgroundColor: const Color(0xFF00D21B),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(20.0),
                  ),
                  padding: EdgeInsets.zero,
                ),
                child: Image.asset(
                  './images/prawo.jpg',
                  width: 60,
                  height: 60,
                  fit: BoxFit.contain,
                ),
              ),
            ),
          ),
        ),

        Positioned( // przycisk lewo
          bottom: 95,
          left: 200,
          child: SizedBox(
            width: 72.0,
            height: 72.0,
            child: GestureDetector(
              onTapDown: (_) {
                frame.setY(-100);
                print('LEWO=========SPEED ${state.speed}========X ${frame.x}==========Y ${frame.y}================ BTN');
              },
              onTapUp: (_) {
                frame.setY(0);
                print('LEWO=========SPEED ${state.speed}========X ${frame.x}==========Y ${frame.y}================ BTN');
              },
              onTapCancel: () {
                frame.setY(0);
                print('LEWO=========SPEED ${state.speed}========X ${frame.x}==========Y ${frame.y}================ BTN');
              },
              child: ElevatedButton(
                onPressed: () {
                  frame.setY(-100);
                },
                style: ElevatedButton.styleFrom(
                  backgroundColor: const Color(0xFF00D21B),
                  shape: RoundedRectangleBorder(
                    borderRadius: BorderRadius.circular(20.0),
                  ),
                  padding: EdgeInsets.zero,
                ),
                child: Image.asset(
                  './images/lewo.jpg',
                  width: 60,
                  height: 60,
                  fit: BoxFit.contain,
                ),
              ),
            ),
          ),
        ),

        Positioned( // przycisk plus
          top: 65,
          right: 280,
          child: SizedBox(
            width: 48.0,
            height: 48.0,
            child: ElevatedButton(
              onPressed: () => state.increaseSpeed(),
              style: ElevatedButton.styleFrom(
                backgroundColor: const Color(0xFF00D21B),
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(10.0),
                ),
                padding: EdgeInsets.zero,
              ),
              child: Image.asset(
                './images/plus.jpg',
                width: 40,
                height: 40,
                fit: BoxFit.contain,
              ),
            ),
          ),
        ),

        Positioned( // przycisk minus
          top: 65,
          left: 280,
          child: SizedBox(
            width: 48.0,
            height: 48.0,
            child: ElevatedButton(
              onPressed: () => state.decreaseSpeed(),
              style: ElevatedButton.styleFrom(
                backgroundColor: const Color(0xFF00D21B),
                shape: RoundedRectangleBorder(
                  borderRadius: BorderRadius.circular(10.0),
                ),
                padding: EdgeInsets.zero,
              ),
              child: Image.asset(
                './images/minus.jpg',
                width: 40,
                height: 40,
                fit: BoxFit.contain,
              ),
            ),
          ),
        ),
      ],
    );
  }
}
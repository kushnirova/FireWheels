import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../models/app_state.dart';
import 'connection_status_dot.dart';

class ControlHeader extends StatelessWidget {
  const ControlHeader({super.key});

  @override
  Widget build(BuildContext context) {

    return Stack (
        children: [
          Positioned( // przycisk tryb
          child: SizedBox(
          width: 170,
          height: 30,
          child: ElevatedButton(
            onPressed: () => context.read<AppState>().toggleMode(),
            style: ElevatedButton.styleFrom(
              backgroundColor: const Color(0xFF1C007A),
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(15),
              ),
              padding: EdgeInsets.zero,
            ),
            child: Image.asset(
              './images/tryb.jpg',
              width: 130,
              height: 30,
              fit: BoxFit.contain,
            ),
          ),
        ),
       ),
      const Positioned(
        right: 200,
        top: 15,
        child: ConnectionStatusDot(),
      )
      ]
    );
  }
}

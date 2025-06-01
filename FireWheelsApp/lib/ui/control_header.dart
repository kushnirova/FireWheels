import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
import '../models/app_state.dart';

class ControlHeader extends StatelessWidget {
  const ControlHeader({super.key});

  @override
  Widget build(BuildContext context) {
    final state = context.watch<AppState>();

    return Positioned(// przycisk tryb
        top: 15, // Odstęp 15px od góry
        left: 0,
        //left: (MediaQuery.of(context).size.width / 2) - (170 / 2), // Wyśrodkowanie poziome
        child: SizedBox(
          width: 170.0, // Szerokość 170px
          height: 30.0, // Wysokość 30px
          child: ElevatedButton(
            onPressed: () => context.read<AppState>().toggleMode(),
            style: ElevatedButton.styleFrom(
              backgroundColor: const Color(0xFF1C007A), // Kolor #1C007A
              shape: RoundedRectangleBorder(
                borderRadius: BorderRadius.circular(15.0), // Lekko zaokrąglone rogi
              ),
              padding: EdgeInsets.zero,
            ),
            child: Image.asset(
              './images/tryb.jpg',
              width: 130,
              height: 30,
              fit: BoxFit.contain,
            ), // Brak zawartości w przycisku
          ),
        )
    );

  }
}

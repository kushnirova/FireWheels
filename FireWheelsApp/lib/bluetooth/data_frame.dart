import 'dart:typed_data';

class DataFrame {

  int x = 0;
  int y = 0;

  final int reserved3 = 0; // bajt dla drugiego analogu x
  final int reserved4 = 0; // bajt dla drugiego analogu y
  final int reserved6 = 0; // bajt dla dodatkowych przycisków na padzie

  // 0 – przyblokowanie
  // 1 – swiatla
  // 2 – awaryjne
  // 3 – klakson
  // 4 – drift
  // 5 - kierunek
  int buttons = 0x21; // przyblokowany i do przodu

  Uint8List toBytes() {
    return Uint8List.fromList([
      x.toSigned(8),        // bajt 1: X
      y.toSigned(8),        // bajt 2: Y
      reserved3,            // bajt 3: 0
      reserved4,            // bajt 4: 0
      buttons,              // bajt 5: bity przycisków
      reserved6,            // bajt 6: 0
    ]);
  }

  // Ustawia bit o danym indeksie na 1 lub 0
  void setBit(int bitIndex, bool value) {
    if (value) {
      buttons |= (1 << bitIndex); // ustaw 1
    } else {
      buttons &= ~(1 << bitIndex); // ustaw 0
    }
  }

  // Przełącza stan bitu (XOR z 1)
  void toggleBit(int bitIndex) {
    buttons ^= (1 << bitIndex);
  }

  // Zmiana X w trybie przyciskowym
  void setX(int a) {
    if (buttons & 1 == 0) { // sprawdzenie czy nie przyblokowane
      print("nie przyblokowane");
      if(buttons & 32 == 32){
        x = a.toSigned(8);
        print("kierunek przod, x ${x}, bt ${buttons}");
      }
      else {
        x = -a;
        print("kierunek tyl, x ${x}, bt ${buttons}");
      }
      if (a.abs()<=10) {
        x = a.toSigned(8);
        print("zero, x ${x}, bt ${buttons}, abs(a) ${a.abs()}");
      }
    }
  }

  // Zmiana X w trybie nachylenia
  void setX_tilt(int a) {
    if (buttons & 1 == 0) {
      x = a.toSigned(8);
      if (a.abs() >= 10) x = a.toSigned(8);
    }
  }

  // Zmiana Y
  void setY(int a) {
    if (buttons & 1 == 0) {
      y = a.toSigned(8);
      if (a.abs()>=10) y = a.toSigned(8);
    }
  }

  String debugString() {
    final bytes = toBytes();
    return bytes.map((b) => b.toRadixString(16).padLeft(2, '0')).join(' ').toUpperCase();
  }
}

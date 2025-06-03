import 'package:flutter/material.dart';
import '../bluetooth/data_frame.dart';

enum ControlMode { buttons, tilt }

class AppState extends ChangeNotifier {
  ControlMode _mode = ControlMode.buttons;
  int _speed = 5;

  ControlMode get mode => _mode;
  int get speed => _speed;

  void toggleMode() {
    _mode = _mode == ControlMode.buttons ? ControlMode.tilt : ControlMode.buttons;
    notifyListeners();
  }

  final DataFrame frame = DataFrame();

  bool _lightsOn = false;
  bool _hazardsOn = false;
  bool _driftOn = false;

  bool get lightsOn => _lightsOn;
  bool get hazardsOn => _hazardsOn;
  bool get driftOn => _driftOn;

  void toggleLights() {
    _lightsOn = !_lightsOn;
    notifyListeners();
    frame.toggleBit(1);
  }

  void toggleHazards() {
    _hazardsOn = !_hazardsOn;
    notifyListeners();
    frame.toggleBit(2);
  }

  void toggleDrift() {
    _driftOn = !_driftOn;
    notifyListeners();
    frame.toggleBit(4);
  }

  void increaseSpeed() {
    if (_speed < 10) {
      _speed++;
      notifyListeners();
      frame.setX(_speed*10);
      print("speed ${_speed*10}===========================================================");
    }
  }

  void decreaseSpeed() {
    if (_speed > 1) {
      _speed--;
      notifyListeners();
      frame.setX(_speed*10);
    }
  }

  void unblock() {
    frame.setBit(0, false);
  }

  void setSpeedFromTilt(int xAngle, int yAngle) {
    if (_mode != ControlMode.tilt) return;

    final newX = xAngle.clamp(-100, 100).toInt();
    final newY = yAngle.clamp(-100, 100).toInt();

    frame.x = newX;
    frame.y = newY;
    notifyListeners();
    print("jedzie x ${frame.x}, y ${frame.y}=======   new x ${newX}, y ${newY}===============================");
  }
}


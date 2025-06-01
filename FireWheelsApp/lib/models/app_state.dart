import 'package:flutter/material.dart';

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

  bool _lightsOn = false;
  bool _hazardsOn = false;
  bool _driftOn = false;

  bool get lightsOn => _lightsOn;
  bool get hazardsOn => _hazardsOn;
  bool get driftOn => _driftOn;

  void toggleLights() {
    _lightsOn = !_lightsOn;
    notifyListeners();
  }

  void toggleHazards() {
    _hazardsOn = !_hazardsOn;
    notifyListeners();
  }

  void toggleDrift() {
    _driftOn = !_driftOn;
    notifyListeners();
  }

  void increaseSpeed() {
    if (_speed < 10) {
      _speed++;
      notifyListeners();
    }
  }

  void decreaseSpeed() {
    if (_speed > 1) {
      _speed--;
      notifyListeners();
    }
  }

  void setSpeedFromTilt(double angle) {
    final mapped = (angle.abs() * 10).clamp(1, 10).toInt();
    if (_speed != mapped) {
      _speed = mapped;
      notifyListeners();
    }
  }
}


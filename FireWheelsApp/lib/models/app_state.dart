import 'package:flutter/material.dart';
import 'package:provider/provider.dart';
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

  final ValueNotifier<DataFrame> frameNotifier = ValueNotifier(DataFrame());

  bool _lightsOn = false;
  bool _hazardsOn = false;
  bool _driftOn = false;

  bool get lightsOn => _lightsOn;
  bool get hazardsOn => _hazardsOn;
  bool get driftOn => _driftOn;

  void toggleLights() {
    _lightsOn = !_lightsOn;
    final newFrame = frameNotifier.value.clone();
    newFrame.toggleBit(1);
    frameNotifier.value = newFrame;
    notifyListeners();
  }

  void toggleHazards() {
    _hazardsOn = !_hazardsOn;
    final newFrame = frameNotifier.value.clone();
    newFrame.toggleBit(2);
    frameNotifier.value = newFrame;
    notifyListeners();
  }

  void toggleDrift() {
    _driftOn = !_driftOn;
    final newFrame = frameNotifier.value.clone();
    newFrame.toggleBit(4);
    frameNotifier.value = newFrame;
    notifyListeners();
  }

  void increaseSpeed() {
    if (_speed < 10) {
      _speed++;
      final newFrame = frameNotifier.value.clone();
      newFrame.setX(_speed * 10);
      frameNotifier.value = newFrame;
      notifyListeners();
      print("speed ${_speed * 10}===========================================================");
    }
  }

  void decreaseSpeed() {
    if (_speed > 1) {
      _speed--;
      final newFrame = frameNotifier.value.clone();
      newFrame.setX(_speed * 10);
      frameNotifier.value = newFrame;
      notifyListeners();
    }
  }

  void unblock() {
    final newFrame = frameNotifier.value.clone();
    newFrame.setBit(0, false);
    frameNotifier.value = newFrame;
    notifyListeners();
  }

  void setSpeedFromTilt(int xAngle, int yAngle) {
    if (_mode != ControlMode.tilt) return;
    final newX = xAngle.clamp(-100, 100).toInt();
    final newY = yAngle.clamp(-100, 100).toInt();
    final newFrame = frameNotifier.value.clone();
    newFrame.x = newX;
    newFrame.y = newY;
    frameNotifier.value = newFrame;
    notifyListeners();
    print("jedzie x ${newFrame.x}, y ${newFrame.y}======= new x ${newX}, y ${newY}===============================");
  }

  void updateFrame(DataFrame newFrame) {
    frameNotifier.value = newFrame.clone();
    notifyListeners();
  }

  static AppState of(BuildContext context) {
    return Provider.of<AppState>(context, listen: false);
  }
}
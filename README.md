# 🏁 FireWheels 🏎️💨

**Projekt semestralny z przedmiotu Systemy Wbudowane i Mikroprocesory -** zdalnie sterowany robot mobilny do wyścigów i driftu

**Autorzy:** Daria Kushnirova i Mateusz Kowalczyk

**Data rozpoczęcia:** 01.05.2025

---

## ⚙️ Opis projektu

FireWheels to dynamiczny, czterokołowy robot mobilny, stworzony do szybkiej jazdy i kontrolowanych poślizgów. Napęd jest realizowany na każde z kół. Wykorzystuje układ kierowniczy Ackermanna napędzany serwomechanizmem. Komunikacja odbywa się bezprzewodowo przez Bluetooth, możliwe jest również sterowanie radiowe 2.4 GHz. Robot wyposażony jest w sygnalizacyjne diody LED oraz klakson/dodatkowy serwomechanizm. Sterowanie jest możliwe w dwóch trybach: za pomocą aplikacji mobilnej (Bluetooth) lub kontrolera bezprzewodowego (nRF). Robot został zaprogramowany za pomocą technologii FreeRTOS w STM32CubeIDE. Aplikacja mobilna napisana w Flutter (Dart) przy użyciu Android Studio.

---

## 📸 Multimedia

- **Zdjęcia:** Zobacz naszego FireWheels w akcji! [photos](https://github.com/kushnirova/FireWheels/tree/main/photos)
- **Wideo:** Nagrania z testów i prezentacji możliwości robota: [link zostanie dodany później]

---

## 🛠️ Użyte technologie i narzędzia

### Robot 🤖

- **Mikrokontroler:** STM32F103C8T6
- **IDE:** STM32CubeIDE
- **Język programowania:** C
- **Sterowanie silnikami:** Toshiba TB6612FNG x2
- **Serwomechanizm:** SG90
- **Komunikacja:** Moduł Bluetooth VG6328A/HC-04, moduł radiowy nRF24L01+PA+LNA 2.4 GHz
- **Zasilanie:** Akumulator Li-Ion 3.7V 18650 (2s)
- **Elementy dodatkowe:**
    - Diody LED
    - Buzzer / Dodatkowy serwomechanizm

### Aplikacja Mobilna 📱

- **Platforma:** Android & iOS
- **Język programowania:** Dart (Flutter)
- **Narzędzia:** Android Studio
- **Komunikacja:** Bluetooth

---

## 🛠️ Postęp prac

Postępy w poszczególnych obszarach projektu:

- **Projektowanie schematów:** [schematic_pcb](https://github.com/kushnirova/FireWheels/tree/main/schematic_pcb)
- **Projektowanie obudowy:** [3d_models](https://github.com/kushnirova/FireWheels/tree/main/3d_models)
- **Oprogramowanie robota i mikrokontrolera:** [firmware](https://github.com/kushnirova/FireWheels/tree/main/firmware/FireWheels)
- **Oprogramowanie aplikacji mobilnej:** [FireWheelsApp](https://github.com/kushnirova/FireWheels/tree/main/FireWheelsApp)

---

## 📝 Wnioski

[wnioski zostaną dopisane po ukończeniu projektu]

---

## 📧 Kontakt

Masz pytania? Skontaktuj się z nami:

- Email: [21267@student.ans-elblag.pl](mailto:21267@student.ans-elblag.pl) / [21244@student.ans-elblag.pl](mailto:21244@student.ans-elblag.pl)
- GitHub: https://github.com/kushnirova / https://github.com/kowmat

---

## 📜 Licencja

**Licencja:** MIT

---

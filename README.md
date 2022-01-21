# MountainViewer </br>
Diplomarbeit, HTL Rankweil, 5BHEL (2021/22)

Projektteam: \
Johannes Humml (Projektleiter), Daniel Jussel 

Projekt Betreuung: \
Dipl.-Ing. Stüttler Christoph

## Beschreibung:
  Der MountainViewer dient dazu anvisierte Berge zu Identifizieren und deren Name und Höhe auszugeben. Die Identifikation erfolgt über den eigenen Standort (mittels GPS Modul) und Sehrichtung (Kompassmodul). Die Umsetzung erfolgt Hardwarebasiert

## Verwendete Geräte/Module:
- Entwicklungboard: Arduino Due
- GPS-Modul: GY-GPS6MV2
- Kompassmodul: Pmod CMPS2
- Display: Adafruit xxxxxxxx

## Programme:
Die oben angeführten Programme sind für folgende Tätigkeit da:
- **MountainViewer**: Hauptprogramm, dient Programm welches generell auf dem Arduino läuft
- **Mountains2MV**: Ausgeschrieben: "Mountains to MountainViewer" ist ein Windows Programm um in CSV konvertierte Kartendaten einzulesen und in ein C++ Programm ausgiebt, welches mit der im MountainViewer zu findenen Headerdatei als Library verwendet werden kann.

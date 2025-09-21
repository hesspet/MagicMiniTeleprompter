# Magic Mini Teleprompter

Eine ESP32/Smartphone/Smartuhr Device um heimlich Nachrichten in die Hand zu senden 

Eine "Spielerei"....

Ursprünglich nur als Projekt gedacht um ein wenig mehr über MAUI herauszufinden. Dann plötzlich eine Idee, warum nicht mal etwas für das Hobby "Zaubern" zu tun?

Also überlegt eine kleine Device zu bauen die man in der Hand verstecken kann und man so mal schnell eben eine Information "peeken" kann. Eins kommt zum Anderen und leider auch gerade noch mein Job durch eine Insolvenz verloren. Also ist auch ein wenig Zeit da.

* MAUI wollte ich schon die ganze Zeit mir mal etwas intensiver ansehen
* Spannend ist dabei die Kommunikation nicht mit "normalen" Bluetooth sondern der Variante mit BLE, also der Version, die vor allem deutlich weniger Energie braucht. Das ist ein Thema das mich besonders wg. meiner Smartwatch GTR 4 (https://www.amazfit.com/products/amazfit-gtr-4). Da diese Uhr locker 14 Tage im normalen Betrieb ohne Nachladen auskommt, ist sie für mich ein täglicher Begleiter. Und es gibt ein Developmentkit inkl. BLE Anbindung.

Nachdem ich den Code schon recht weit getrieben habe bin ich dann auf einen Anbieter gestolpert, der mehr oder weniger genau das anbietet was ich mir hier ausgedacht habe. Natürlich viel professioneller.

https://electricks.info/de/product/peeksmith-3/

Ich hatte einmal überlegt, das Ganze kommerziell anzugehen. Aber Electricks bietet für die „Profis“ bereits alles, was man sich wünschen kann. Also habe ich beschlossen, dieses Projekt freizugeben – und den „kleinen Hobbyzauberern“ und Amateuren, die nicht mal eben ein paar Hundert Euro für eine solche Plattform ausgeben können, eine Möglichkeit zu bieten, mit einer Bastellösung erstaunlich weit zu kommen.

Wir reden hier – in der einfachsten Ausführung – von unter 30 €, sofern ein Android-Smartphone vorhanden ist!

Ziel war es, möglichst viele Fertigelemente zu verwenden. Aktuell nutze ich das T-Display von LilyGO: 👉 https://lilygo.cc/products/lilygo%C2%AE-ttgo-t-display-1-14-inch-lcd-esp32-control-board
Das Teil ist auch bei deutschen Anbietern für etwa 15–20€ (manchmal auch günstiger) erhältlich. Noch ein Akku dazu – und die Billiglösung steht. Also für rund 25 € realisierbar. 

Weitere Komponenten sind bereits bestellt um noch andere Ideen zu realisieren. Vor allem die Bauteile von M5Stack sind für Leute ohne Lötkolben eine tolle Variante.

Ein Smartphone hat heutzutage ohnehin jeder … also los geht’s.
Allerdings: Im Moment läuft alles nur unter Android.
Fragt bitte nicht nach iPhone – ich habe kein macOS-Entwicklungsumfeld, und dies ist ein reines Hobbyprojekt. Die Musik spielt aktuell nur unter Android.

Das Programmierumfeld ist komplett kostenfrei, es kann also nichts anbrennen:

* Arduino IDE mit ESP32-Board-Erweiterung
* Visual Studio 2022 + .NET MAUI

Je nachdem, ob es hierzu Resonanz gibt, werde ich bei Interesse auch ein fertiges APK samt Anleitung bereitstellen. Das hier ist – wie gesagt – ein reines Freizeitprojekt. Wer Ideen hat, darf sich gerne melden:
📧 hesspet at gmx.de

# Roadmap

* ~~Erste Verlautbarung in einem Chat mit Zauberern~~ OK 31.07.2025
* ~~Shutdown - Aktuell läuft das Display bis der Akku all ist. Das ist natürlich kein Zustand. Im nächsten Schritt wird man per App oder via Tastenkommando das System in den sogenanten DeepSleep versetzen können. Dies erlaubt, dass der Akku monatelang nicht geladen werden muss. Eine Reaktivierung wird dann einfach per Knopfdruck möglich sein.~~ OK 01.08.2025  
* ~~Anzeige des Akkuladestandes via Balkenanzeige~~ OK 01.08.2025
* Feedbackmechanismen, um ggf. Signale an andere ESP32-Geräte zu senden – zum Beispiel zur Ansteuerung von Motoren oder ähnlichen „Zauber-Spielereien“
* Sichtung und Bewertung weiterer Controller-Plattformen
* Anbindung einer Smartwatch – liegt bereits startklar im Hintergrund: Amazfit GTR 4 👉 https://www.amazfit.com/products/amazfit-gtr-4
* Und natürlich: alle weiteren Schandtaten, solange der Vorrat reicht 😄

Gerne auch: Integration in bestehende App-APIs. Da ich beruflich ohnehin ständig mit so etwas zu tun habe, sollte das technisch alles machbar sein – die einzige Frage ist wie immer: Habe ich Zeit und genug Ideen?

# Wiki

Hier geht es dann zum Wiki dort entsteht dann die weitere Dokumentation https://github.com/hesspet/MagicMiniTeleprompter/wiki. Insbesondere werden hier dann auch Stück für Stück Ideen zur Präsentation und zum Einsatz im Rahmen von Zauberkunststücken gesammelt. Wer weiß, vielleicht gibt's auch ein paar MagicMiniTelepromter spezial Kunststücke.

# FAQ

Findet sich auch im Wiki https://github.com/hesspet/MagicMiniTeleprompter/wiki/FAQ

# Quellen:

* Repository LilyGo T-Display (Schaltplan, Übersichtsgraph, Libraries, Sample Codes, STL-Datei für ein Gehäuse (3d-Printer))
  https://github.com/Xinyuan-LilyGO/TTGO-T-Display

# Screenshots

## Android Screenshots - Version 31.7.2027

Simple Funktionalitäten

* Wähle BLE Device (ESP32 - T-Display)
* Sende eine Textnachricht
* Schnellmodus nur eine Zahl
* Auswahl einer Karte aus dem Deck

<img src="https://github.com/hesspet/MagicMiniTeleprompter/blob/main/Screenshots/Screenshot_Auswwahl_BLE_Device.jpg" width="300"> <img src="https://github.com/hesspet/MagicMiniTeleprompter/blob/main/Screenshots/Screenshot_TextSenden_1.jpg" width="300"> <img src="https://github.com/hesspet/MagicMiniTeleprompter/blob/main/Screenshots/Screenshot_TextSenden_2.jpg" width="300"> <img src="https://github.com/hesspet/MagicMiniTeleprompter/blob/main/Screenshots/Screenshot_Schnellübertragung_Zahl_2.jpg" width="300"> <img src="https://github.com/hesspet/MagicMiniTeleprompter/blob/main/Screenshots/Screenshot_Kartenauswahl_1.jpg" width="300"> <img src="https://github.com/hesspet/MagicMiniTeleprompter/blob/main/Screenshots/Screenshot_Kartenauswahl_2.jpg" width="300">

## T-Display - Nahansicht

Testbetrieb via USB, Akku ist hinter der Platine montiert. Wird im USB Betrieb geladen

<img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/T_Display_1.jpg" width="300"> <img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/T_Display_2.jpg" width="300"> <img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/T_Display_3.jpg" width="300"> <img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/T_Display_4.jpg" width="300">

## T-Display in der Hand versteckt. 

Lässt sich gut "palmieren". Wiegt so gut wie nichts. Aktuell kein Case. Gibt es aber als Zubehör von Lilygo für glaube ich 8 Euro. Ich würde es selbst aber einfach mit Tape zu machen, oder durchsichtiger Schrumpfschlau etc...

<img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/Anwendung_Peek_1.jpg" 
  width="300"> <img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/Anwendung_Peek_2.jpg" 
  width="300"> <img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/Anwendung_Peek_3.jpg" 
  width="300"> <img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/Anwendung_Peek_4.jpg" 
  width="300"> <img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/Anwendung_Peek_5.jpg" 
  width="300">

Weitere Devices:

### M5STACK StickC [Wiki](https://github.com/hesspet/MagicMiniTeleprompter/wiki/M5STACK-%E2%80%90-StickC-Plus2)
<img src="https://github.com/hesspet/MagicMiniTeleprompter/blob/main/Images/M5STACK%20%E2%80%90%20StickC%20Plus2_1.png?raw=true" 
  width="300"> <img src="https://github.com/hesspet/MagicMiniTeleprompter/blob/main/Images/M5STACK%20%E2%80%90%20StickC%20Plus2_2.png?raw=true" 
  width="300"> 


## Münzversteck

Die Münze enspricht der größe einer 1 Dollar Münze also rund 4 cm. Dann hat man hier ein guten Vergleich wie groß das Gerät in der Hand ist. Münze mit Loch bringt da noch gleich ein paar Ideen....

<img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/Anwendung_Vergleich_mit_M%C3%BCnze_Dollargr%C3%B6%C3%9Fe_4cm_1.jpg" width="400"><img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/Anwendung_Vergleich_mit_M%C3%BCnze_Dollargr%C3%B6%C3%9Fe_4cm_2.jpg" width="400">




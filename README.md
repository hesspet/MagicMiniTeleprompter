# Magic Mini Teleprompter

Eine ESP32/Smartphone/Smartuhr Device um heimlich Nachrichten in die Hand zu senden 

Eine "Spielerei"....

Ursprünglich nur als Projekt gedacht um ein wenig mehr über MAUI herauszufinden. Dann plötzlich eine Idee, warum nicht mal etwas für das Hobby "Zaubern" zu tun.

Also überlegt eine kleine Device zu bauen die man in der Hand verstecken kann und man so mal schnell eben eine Information "peeken" kann. Eins kommt zum Anderen und leider auch gerade noch mein Job durch eine Insolvenz verloren. Also ist auch ein wenig Zeit da.

Und MAUI wollte ich schon die ganze Zeit mir mal etwas intensiver ansehen.

Nachdem ich den Code schon recht weit getrieben habe bin ich dann auf einen Anbieter gestolpert, der mehr oder weniger genau das anbietet was ich mir hier ausgedacht habe. Natürlich viel professioneller.

https://electricks.info/de/product/peeksmith-3/

Ich hatte mal überlegt dies kommerziell zu machen. Aber electricks hat für die "Profis" alles was man sich wünscht. Also habe ich beschlossen, dieses Projekt frei zu geben und den kleinen Hobbyzauberern und Amateueren die nicht mal schnell ein paar hundert Euro für eine solche Plattform ausgeben können eine Möglichkeit zu geben mit einer "Bastellösung" recht weit zu kommen. Wir Reden hier in der einfachsten Form von unter 30 Euro! Wenn ein Smartphone vorhanden ist.

Ziel war es, Fertigelemente einzusetzen. Aktuell nutze ich das T-Display von Lilygo: https://lilygo.cc/products/lilygo%C2%AE-ttgo-t-display-1-14-inch-lcd-esp32-control-board Das Teil ist auch bei deuteschen Anbietern für 10-15 Euro zu bekommen. Ein Akku dazu und die Billiglösung ist fertig. Also für rund 20E zu basteln. Weitere Komponenten sind schon in der Bestellung. Vor allem die Teile von m5stack sind für Leute ohne Lötkolben eine tolle Variante.

Smartphone hat jeder... los geht's. Naja Android muss es im Moment sein. Fragt bitte nicht nach iPhone. Ich habe kein MAC Umfeld zur Entwicklung - dies ist ein Hobbyprojekt. Also aktuell spielt hier die Musik nur unter Android. 

Das Programmierumfeld ist komplett kostenfrei, so dass hier auch nichts anbrennt:

* Arduino IDE mit ESP32 Board Erweiterung
* Visual Studion 2022 + MAUI 

Je nachdem ob hierzu Resonanz besteht, werde ich auch ggf. dann ein fertiges APK machen und Anleitung etc. Das hier ist ein reines Freizeitprojekt. Wer Ideen hat, bitte mich kontaktieren. (hesspet at gmx.de)

# Roadmap

* Feedback um ggf. Signale an andere ESP zu schicken um ggf. Motoren zu steuer und so Spielerreien
* Weitere Controler sichten
* Anbind von Smartwatch (habe ich schon im Hintergrund hier liege)
* jegliche weitere Schandtaten solange der Vorrat reicht... :-)

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

## Münzversteck

Die Münze enspricht der größe einer 1 Dollar Münze also rund 4 cm. Dann hat man hier ein guten Vergleich wie groß das Gerät in der Hand ist. Münze mit Loch bringt da noch gleich ein paar Ideen....

<img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/Anwendung_Vergleich_mit_M%C3%BCnze_Dollargr%C3%B6%C3%9Fe_4cm_1.jpg" width="400"><img src="https://raw.githubusercontent.com/hesspet/MagicMiniTeleprompter/refs/heads/main/Screenshots/Anwendung_Vergleich_mit_M%C3%BCnze_Dollargr%C3%B6%C3%9Fe_4cm_2.jpg" width="400">


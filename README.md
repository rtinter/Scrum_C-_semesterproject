# HUMAN BENCHMARK

## Athena

### [Projektbeiträge: Eigener Beitrag](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/aem_projekt_beitraege/-/tree/main/Projektbeitrag?ref_type=heads) | [Projektdokumentation im Wiki](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/wikis/home)

## Produktvision
Das **Ziel** des Projektes ist es, eine unterhaltsame und benutzerfreundliche Plattform für die kognitive Leistungsmessung und -verbesserung durch Tests, im weiteren Spiele genannt, zu erstellen. Diese Spiele werden im Speziellen auf Fähigkeiten, wie Reaktionsschnelligkeit, Erinnerungsvermögen, Mustererkennung, Resilienz sowie Moral abgestimmt sein. Dadurch soll Anwärter:innen auf Assessment-Centern bei der Polizei und der Feuerwehr eine erste Abschätzung gegeben werden, ob sie sich für diese Art von Arbeit eignen und sich gegebenenfalls verbessern. (Wörtlich aus der Produktwahl übernommen.)

Die **Zielgruppe** von Human Benchmark umfasst potenzielle Teilnehmer:innen an Assessment-Centern von Feuerwehr und Polizei.

Ihr **Bedarf** besteht darin, sich effektiv auf anspruchsvolle und selektive Tests vorzubereiten, wobei die Möglichkeit besteht, sich mit anderen zu vergleichen. Zusätzlich bietet die Anwendung eine Grundlage zur Bewertung der Eignung für das Berufsfeld, indem sie mentale und kognitive Fähigkeiten trainiert.

Aufgrund des **Wettbewerbscharakters** von Assessment-Centern sind die Nutzer:innen bereit, finanzielle Ressourcen für eine optimale Vorbereitung einzusetzen. Diese Einschätzung wird durch die Vielzahl von Büchern und Anwendungen zum Thema Assessment-Center gestützt.

Der **Mehrwert** unserer Anwendung besteht darin, das Konzept der Leistungsmessung spielerisch zu vermitteln, ähnlich wie es in Assessment-Centern praktiziert wird.

## Unser Team
Gruppe: AEM-1
 
| Rolle | Teilnehmer              | Matr.-Nr. |
|-------|-------------------------|-----------|
| PO    | Jane Schönfeld          | 941120    |
| SM    | Benjamin Puhani         | 941077    |
| DEV   | Jannik Brozy            | 940986    |
| DEV   | René Marcel Tinter      | 940995    |
| DEV   | Caspar Quast            | 941155    |
| DEV   | Noah Zepner             | 941167    |
| DEV   | Timo Michaelis          | 941362    |
| DEV   | Sebastian Elisa Reineke | 941070    |
| DEV   | Karlina Jung            | 941169    |
| DEV   | Jonas Neumann           | 941341    |
| DEV   | Gerrit Koch             | 941213    |


## Table of Contents

- [Features](#features)
- [Getting Started With Development](#getting-started-with-development)
  - [Projektstruktur](#projektstruktur)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Dependencies für Linux](#dependencies-für-linux)
  - [Dependencies für Windows](#dependencies-für-windows)
  - [Building the Project](#building-the-project)
  - [Terminal Installation](#terminal-installation)
- [Anforderungsnachweise](#anforderungsnachweise)
- [Herausforderungen](#herausforderungen)
- [Limitationen](#limitationen)
- [Ausblick](#ausblick)
- [Selbsteinschätzung des Teams](#selbsteinschätzung-des-teams)

## Features

- Kognitive Leistungsmessung und -verbesserung durch Tests
- 15 Spiele in den verschiedenen Kategorien 
  - Reaktion
  - Genauigkeit
  - Merkfähigkeit
  - Problemlösung
  - Logisches Denken
- Detaillierte Statistiken und Vergleiche
- Wettbewerbscharakter
- Vorbereitung auf Assessment-Center für Polizei und Feuerwehr

## Interaktion

Zum Trainieren benötigt man eine Tastatur, Maus und ein Gehirn.

Jedes Spiel benötigt eine eigene Steuerung, diese ist in der jeweiligen Spielbeschreibung zu finden.

## Getting Started With Development

### Projektstruktur

Das Projekt ist in folgende Verzeichnisse unterteilt:
- `assets`: Enthält zusätzliche Ressourcen für Spiele, wie json oder Bilder.
- `lib`: Enthält die Bibliotheken, die für das Projekt benötigt werden.
- `src`: Enthält den Quellcode des Projekts.
  - `App`: Enthält die Implementierung der Anwendung.
  - `main`: Ist der Einstiegspunkt des Projekts. Startet die App.

[Klassendiagramm](https://dfncloud.fh-kiel.de/s/3cqAJdTNJ5f99tk)

### Prerequisites

Zum Arbeiten mit dem Projekt ist es empfohlen die Entwicklungsumgebung [CLion](https://www.jetbrains.com/de-de/clion/) zu verwenden. Die folgende Anleitung konzentriert sich auf die Verwendung von CLion.

Alternativ kann auch [Visual Studio Code](https://code.visualstudio.com/) in Verbindung mit der [C/C++ Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) verwendet werden. Hiefür müssen noch [CMake](https://cmake.org/) und [MinGW](https://sourceforge.net/projects/mingw-w64/) installiert werden.


### Installation

1. Sollte ein Projekt in CLion offen sein, dieses mit `File > Close Project` schließen.
2. Über `Get from VCS` das Projekt von der Git-URL `https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena.git` klonen.
3. Zustimmen, dass dem Projekt vertraut wird und anschließend sollte das Projekt in CLion geöffnet sein.
4. Die erforderlichen Bibliotheken werden per CMake automatisch heruntergeladen und installiert.

### Dependencies für Linux
Folgende dependencies müssen installiert werden, wenn auf Linux entwickelt werden will.
```bash
sudo apt -y install libxrandr-dev libxcursor-dev libudev-dev libopenal-dev libflac-dev libvorbis-dev libgl1-mesa-dev libegl1-mesa-dev libxinerama-dev libxi-dev clang-tidy zip
```

### Dependencies für Windows
Zum Kompilieren auf einem Windows 11 System müssen folgende Abhängigkeiten in einem konfigurierten MSYS2 installiert sein. Für die Installation der Abhängigkeiten muss folgender Befehl ausgeführt werden.

```bash
pacman -S mingw-w64-x86_64-sfml mingw-w64-x86_64-boost mingw-w64-x86_64-toolchain mingw-w64-x86_64-cmake
```

### Building the Project

1. In CLion oben rechts die Konfiguration auf `Athena` setzen.
2. Das grüne Play-Symbol in der IDE klicken.
3. Das Projekt sollte nun gebaut und ausgeführt werden.

### Terminal Installation

IDE unabhängige Installation für: Windows, Linux, Mac

Vorausgesetzte Programme: 
Cmake, Git, C++ Compiler (MingW, Visual Studio Compiler, G++)

Für Windows muss das o. g. Bash-Script innerhalb der MSYS2-Umgebung ausgeführt werden. 

```bash
git clone git@gitlab.iue.fh-kiel.de:aem/aem-2024/aem-team-1/human-benchmark/athena.git
cd athena
mkdir build && cd build
cmake ..
cmake --build .
```

Disclaimer: Der Build-Prozess wurde unter Windows 11 & Linux erfolgreich getestet.

## [Anforderungsnachweise](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/Anforderungs-nachweis.md)

## Herausforderungen

| Herausforderung | Lösung |
| --------------- | ------ |
| Scene Manager   | Anfängliche Schwierigkeiten bei der Handhabung der Darstellung und dem Seitenwechsel führten zu Verzögerungen bei der Schnittstellenimplementierung. Der Schwerpunkt lag auf der eleganten Integration neuer Tiles, da die Strukturierung der Anwendung in kleinere Spiele eine schnelle Hinzufügung neuer Elemente erforderte. Dabei traten Speicherlecks auf, die durch eine gründliche Stack-Analyse und Debugging behoben wurden. Unsere Lösung für eine solide Grundstruktur bestand in der Verwendung von Template-Programmierung und der optimalen Nutzung von Smartpointern. |
| Cmake           | Aufgrund der komplexen Projektstruktur stellte die initiale CMake-Konfiguration eine Herausforderung dar. Zur Lösung wurde ein generisches Template entwickelt, das glob-Muster zur automatischen Dateierkennung nutzt: `file(GLOB SOURCES *.cpp)` Dieser Ansatz vereinfacht die CMake-Konfiguration erheblich und erhöht die Flexibilität bei der Projektwartung, auch wenn dadurch die Expressivität verloren geht. [Wiki Eintrag CMake](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/wikis/Development/CMake )|
| Codezeilen Anforderung |Wir hatten bis zur Präsentation ca. 6000 von 8000 Zeilen, was darauf zurückzuführen ist, dass wir versucht haben, guten Code zu schreiben, der auch wiederverwendet werden kann. Dies führte dazu, dass wir in der letzten Woche vor der Abgabe des Projekts noch viel programmiert und noch weitere Spiele (4) erstellt haben, wodurch wir jetzt auf mehr als 8000 Zeilen gekommen sind. |
| ImGui | Mit ImGui zu arbeiten hat uns vor eine große Herausforderung gestellt, weil wir uns alle zunächst einarbeiten mussten. Das dadurch aufwendigere Umsetzen der grafischen Anforderungen hat uns nach und nach mit ImGui vertrauter gemacht und uns gelehrt, effektiver damit zu arbeiten (Learning by Doing).|


## Limitationen
Die Benutzung von ImGui hinderte uns bei der visuellen Gestaltung der Applikation immens, teilweise sind Spiele immenoch von diversen Usability Sünden betroffen.
Die Applikation ist aktuell komplett offline.

## Ausblick
Die Zukunft unserer Anwendung ist mehr als rosig. Wir haben einen guten Grundstein gelegt, auf den man nun aufbauen kann. Um nur einige Beispiele zu nennen, die sogar teilweise schon in der Roadmap/ als Tickets im Backlog angelegt sind:
- weitere Spiele
- mehr statistische Auswertungen (beispielsweise unter Verwendung von implot)
  - Wie lange hat man in den Spielen verbracht?
  - Wie gut war man im Allgemeinen in einem Spiel?
  - In welchen Spielen müsste ich mich verbessern?
  - Wie gut bin ich auf das Assessmentcenter vorbereitet?
- Die Anwendung könnte vorschlagen, welche Spiele zur persönlichen Verbesserung trainiert werden sollten
- Usermanagement: Account, Einloggen, Registrieren, Freunde finden, Vergleich zu anderen
- Datenbank anbinden, um die Ergebnisse zu speichern
- Monetarisierung durch Werbung oder ein Abo Modell

Wikiseite für unsere [Roadmap](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/wikis/Produkt/RoadMap) 



## Selbsteinschätzung des Teams
Jeder hat sich in unserem Team nach seinen besten Fähigkeiten eingebracht und nach besten Kräften mitgeholfen. Wir waren über eine Whatsapp Gruppe im ständigen Kontakt. Keiner hat sich durch Inaktivität ausgezeichnet, weshalb wir es ablehnen, eine oder mehrere Personen als schlechter zu betiteln, als andere. Genauso gab es niemanden der über die Maßen mehr gemacht hat, als alle anderen. Wir sind ein Team und möchten auch so benotet werden.

Unserer Ansicht nach haben wir alle Anforderungen erfüllt. Daher schätzen wir unsere erbrachte Leistung als **sehr gut** ein.

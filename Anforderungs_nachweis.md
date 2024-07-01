# Traceability Matrix

Anforderungsumsetzungen benannt nach der Anforderungs-ID + alphabetischen Buchstaben sind Referenzen auf Ausschnitte
unseres Codes, worin wir diese umgesetzt haben.

<table>
<tr>
<th>Anforderungs-ID</th>
<th>Beschreibung</th>
<th>Umsetzungsnachweis</th>
<th>Erfüllt</th>
</tr>
<tr>
<td>1</td>
<td>Erzeugung eines ausführbaren C++ Programms.</td>
<td>

[Readme - Installationsanweisung](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena#installation), [Release Page](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/releases)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>2</td>
<td>Erzeugung einer C++ Bibliothek und Einbindung dieser in ihr Programm mit sinnvoller Modularisierung und eigenem Namespace.</td>
<td>

[Verzeichnis unserer Bibliotheken](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/tree/dev/lib?ref_type=heads)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>3</td>
<td>Nutzung externer C++ Bibliotheken und Einbindung dieser in ihr Programm (Extern bedeutet hier eine Bibliothek, die nicht Teil der C++ Standardbibliothek ist).</td>
<td>

[SFML](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/CMakeLists.txt?ref_type=heads#L11), [ImGui](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/CMakeLists.txt?ref_type=heads#L17), [ImGui-Sfml](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/CMakeLists.txt?ref_type=heads#L24), [Box2D](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/CMakeLists.txt?ref_type=heads#L30),

[JSON](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/CMakeLists.txt?ref_type=heads#L35), [RapidCSV](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/CMakeLists.txt?ref_type=heads#L41)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>4</td>
<td>Nutzung von CMake.</td>
<td>

[Project Root Cmake](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/CMakeLists.txt?ref_type=heads)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>5</td>
<td>Objektorientierte Analyse einer realen Problemstellung und Umsetzung einer dazu passenden objektorientierten Architektur in C++.</td>
<td>

[UML-Klassendiagramm](https://dfncloud.fh-kiel.de/s/3cqAJdTNJ5f99tk)
</td>
<td>

</td>
</tr>
<tr>
<td>6</td>
<td>Nutzung von Funktionsüberladung.</td>
<td>

[6a](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/ui_elements/InfoBox.hpp?ref_type=heads#L23-41), [6b](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/rows_of_numbers/Sequence.hpp?ref_type=heads#L19-21), [6c](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/commons/SoundPolice.hpp?ref_type=heads#L15-19)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>7</td>
<td>Nutzung von Operatorüberladung.</td>
<td>

[7a](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/letter_salad/WordTarget.cpp?ref_type=heads#L16), [7b](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/commons/Coordinates.cpp?ref_type=heads#L7-19)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>8</td>
<td>Datei und Konsolen IO (bspw. für Logging Informationen).</td>
<td>

[8a](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/logger/Logger.cpp?ref_type=heads), [8b](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/csv/CsvParser.cpp?ref_type=heads), [8c](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/abstract_game/CsvStorage.cpp?ref_type=heads#L21-63)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>9</td>
<td>Verwendung von C++ Smart Pointern (unique_ptr, shared_ptr) bei dynamisch erzeugten Objekten.</td>
<td>

[9a](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/views/Dashboard.hpp?ref_type=heads#L7), [9b](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/scene/SceneManager.hpp?ref_type=heads#L9), [9c](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/scene/GameScene.hpp?ref_type=heads#L15), [9d](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/scene/DashboardScene.hpp?ref_type=heads#L10), [9e](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/remembering/Remembering.hpp?ref_type=heads#L53), [9f](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/calc/MathTaskFactory.hpp?ref_type=heads#L11), [9g](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/calc/Calc.hpp?ref_type=heads#L43), [9h](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/aim_trainer/AimTrainer.hpp?ref_type=heads#L36)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>10</td>
<td>Verwendung von weiteren Standard Containern zusätzlich zu std::vector und std::array.</td>
<td>

[10a](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/analogy/Analogy.hpp?ref_type=heads#L21), [10b](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/ui_elements/InfoBox.hpp?ref_type=heads#L14-20), [10c](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/commons/SoundManager.hpp?ref_type=heads#L32), [10d](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/rows_of_symbols/RowsOfSymbols.hpp?ref_type=heads#L21), [10e](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/typeracer/TypeRacer.hpp?ref_type=heads#L21), [10f](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/logger/Logger.cpp?ref_type=heads#L13)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>11</td>
<td>Spaß am Projekt</td>
<td>

[Umfrage-Ergebnisse](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/wikis/uploads/bd31b9d3b0dc8747ad2b865e54e86550/image.png)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>12</td>
<td>Nutzung von Laufzeitpolymorphismus.</td>
<td>

[12a](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/typeracer/TypeRacer.hpp?ref_type=heads#L16), [12b](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/scene/ResultsScene.hpp?ref_type=heads#L14), [12c](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/scene/GameScene.hpp?ref_type=heads#L17-18), [12d](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/scene/Scene.hpp?ref_type=heads#L14), [12e](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/calc/MathTask.hpp?ref_type=heads#L33)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>13</td>
<td>Nutzung von move-Semantik.</td>
<td>

[13a](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/scene/SceneManager.cpp?ref_type=heads#L21), [13b](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/games/letter_salad/LetterSalad.cpp#L96), [13c](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/views/Dashboard.cpp#L36)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>14</td>
<td>Vermeidung von “rohen” Zeigern (Heapallokation mit new/delete).</td>
<td>

Es wurde kein new benutzt.

```
grep -r "new" ./src ./lib
```

Zeigt alle usecases des Wortes "new". Alle sind als Variablennamen oder als Kommentar benutzt.
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>15</td>
<td>Erstellung von eigenen Template-Klassen und/oder -Funktionen.</td>
<td>

[15a](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/scene/GameScene.hpp?ref_type=heads#L17-18), [15b](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/ui_elements/Window.hpp?ref_type=heads#L29-30)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>16</td>
<td>Debugging ihrer Anwendung mittels Debugger.</td>
<td>

[16a](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/wikis/uploads/7f8a01bbdd7bfef0900b14baefaddeec/image.png), [16b](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/wikis/uploads/9780509d0f37fecdae4fd1616e606259/image.png)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>17</td>
<td>Profiling ihrer Anwendung mittels Profiler. Dokumentation der Ergebnisse.</td>
<td>

[CPU Profiling](Development/CPU%20Profiling),

[Memory Profiling](Development/Memory%20Profiling)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>18</td>
<td>Versionskontrolle mit Git.</td>
<td>

[Human Benchmark Repository](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>19</td>
<td>Durchführung einer statischen Code Analyse (linting) des selbst geschriebenen C++ Codes mit Clang-Tidy. Hier können bspw. die Funktionalitäten aus der CLion IDE genutzt werden. Fehler bzw. Verbesserungsvorschläge aus der Code Analyse sollen entsprechend sinnvoll umgesetzt werden (nicht alle Vorschläge des Tools machen immer Sinn)!</td>
<td>

[unsere .clang-tidy Datei](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/.clang-tidy?ref_type=heads)

Als Vorlage wurde, eine konfiguration von Google benutzt und von uns nach unseren Ansprüchen angepasst.

[Beispiel des Einsatzes](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/wikis/uploads/eca3ff8ec908fc524267a579f341cde5/image.png)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>20</td>
<td>

Mindestens 400 Codezeilen netto (d.h. ohne Kommentare und externen Bibliotheken = selbst geschriebener Code) pro
Teammitglied. Ermittelt bspw. mit Metrics Plugin für Clion oder https://github.com/AlDanial/cloc
</td>
<td>

```
cloc ./src/ ./lib/ ./assets/ .gitlab-ci.yml CMakeLists.txt build.sh .gitignore .clang-tidy 
```

[Ergebnis](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/wikis/uploads/dbb0937db614533b1c62559b76853086/image.png)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>21</td>
<td>Sinnvoll dokumentierter Quellcode.</td>
<td>

[21a](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/scene/SceneManager.hpp?ref_type=heads)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>22</td>
<td>Das Projekt muss mit CMake unter einer Windows msys2/mingw64 Umgebung gebaut werden können.</td>
<td>

[Anleitung zum Bauen](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/lib/scene/SceneManager.hpp?ref_type=heads)
</td>
<td>

:white_check_mark:
</td>
</tr>
<tr>
<td>23</td>
<td>

Es muss eine readme.md Datei (Markdown Format) beigefügt sein. In dieser muss folgendes enthalten sein:<br>-
Projektteilnehmer\*innen und Matrikelnummern<br>- Projekttitel und -beschreibung<br>- Um was geht es?<br>- Was macht das
Programm?<br>- Was sind Ein/Ausgaben, wie wird es genutzt, wie interagiert man?<br>- Anleitung zum Installieren aller
Dependencies unter msys2/mingw64<br>- Anleitung zum Bauen unter msys2/mingw64<br>- Beschreibung wie und wo die
Anforderungen Nr. 2-20 sinnvoll umgesetzt wurden (als Beispiele sind Fallstudien möglich)<br>- Beschreibung der
Verzeichnisstruktur, Projektstruktur und Klassenhierarchie (bspw. mit verlinkten UML Grafiken)<br>- Welche
Herausforderungen gab es, wie wurden diese gelöst?<br>- Limitationen / Ausblick, was kann das Programm noch nicht, wie
könnte es weitergehen?<br>- Selbsteinschätzung Team, wie sieht sich das Team, gibt es Teammitglieder, die besonders
herausragend waren bzw. wenig beigetragen haben (Namen erwünscht)
</td>
<td>

[README.md](https://gitlab.iue.fh-kiel.de/aem/aem-2024/aem-team-1/human-benchmark/athena/-/blob/dev/README.md?ref_type=heads)
</td>
<td>

:white_check_mark:
</td>
</tr>
</table>

Disclaimer: Die Auflistung von Beispielen ist nicht abschließend.

Legende:

- :white_check_mark: : Erfüllt
- :hourglass_flowing_sand: : In Arbeit
- :x: : Nicht erfüllt
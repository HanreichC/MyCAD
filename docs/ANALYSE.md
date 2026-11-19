# MyCAD – Standortbestimmung und Richtung (November 2026)

> Frage: Was hat MyCAD, was unterscheidet es von den großen CAD-Programmen, was können wir neu und besser denken,
> warum sollte jemand von Fusion wechseln, und was fehlt dafür noch? Grundlage: der ganze Plan, README, Code (Toolbar,
> Befehle, Importe) und eine Recherche zum Stand der großen Programme im Herbst 2026 (Quellen am Ende).
> Was hiervon beschlossen wird, kommt als Phase 12 in `PLAN.md`.

---

## 1. Kurzfassung

1. **MyCAD ist weiter, als es sich selbst beschreibt.** „Schlankes CAD“ stimmt nicht mehr: 17 Erzeugen-, 14 Ändern-,
   6 Konstruktions-Werkzeuge, Baugruppen mit geschlossenen Ketten, Normbohrungen, druckbare Gewinde, Passungen,
   Versionen, Varianten, Konfigurationen. Für Teile bis mittlere Baugruppen deckt es ab, was ein Maker in Fusion täglich
   braucht.
2. **Der größte Hebel ist nicht noch ein Werkzeug, sondern die Lücke im Markt:** Es gibt kein gutes, natives
   Fusion-artiges CAD für Linux. Fusion läuft dort nur in einer VM, Onshape nur im Browser und mit Cloud-Zwang, FreeCAD
   gilt als zäh beim Skizzieren. MyCAD ist genau dafür gebaut, sagt das aber nur halb.
3. **Die Großen gehen 2026 alle in dieselbe Richtung:** KI-Assistent in der Cloud (Autodesk Assistant, Onshape AI
   Advisor, SOLIDWORKS AURA) und Text-zu-CAD (Zoo, Adam, Backflip, Autodesk Neural CAD). Niemand macht das **lokal und
   offline**. MyCAD hat mit Handschrift-Lesen, „Absicht statt Befehl“ und Fehlern, die sich erklären, schon die Hälfte
   des Fundaments dafür.
4. **3D-Druck ist der Markt, der wächst** (MakerWorld: rund 10 Mio. aktive Nutzer im Monat, Einsteigerdrucker +26 %
   2025). MyCADs Druckansicht, „Druckbar machen“, Passungen und Gewinde sind dort einzigartig. Es fehlt aber das, was
   diese Leute ständig tun: **STL/3MF öffnen und umbauen (Remix)**.
5. **Drei Lücken hindern Wechsler heute am meisten:** kein Mesh-Import (STL/3MF/OBJ), keine Zeichnung für die Werkstatt
   (PDF mit Maßen) und die Verteilung (AppImage nur für Arch-Systeme, nicht auf Flathub).
6. **Die Oberfläche ist am Limit ihrer Form:** zwei volle Werkzeugzeilen mit 35 Plätzen und vielen Aufklappern. Statt
   eines kompletten Neuentwurfs empfehle ich **„Kontext statt Werkzeugkasten“**: Werkzeuge erscheinen an der Auswahl, die
   große Leiste wird zur ruhigen Kategorie-Kapsel. Liquid Glass bleibt, es ist ein Alleinstellungsmerkmal.

**Empfohlene Reihenfolge** (Begründung in Kapitel 7): Mesh-Brücke → Kontext-Werkzeuge → Druck-Kalibrierung →
Werkstattblatt → Flathub → lokaler Assistent → Code-Schritt. Bewusst nicht: CAM, Flächenmodellierung, Cloud-Zusammenarbeit.

---

## 2. Wo MyCAD heute steht

### 2.1 Was es kann (Stand 19.11.2026)

| Bereich | Stand |
|---|---|
| Skizze | 12 Zeichen-, 7 Ändern-Werkzeuge, 9 Bedingungen, ein Maß-Werkzeug; Maß am Maß eintippen, Tab zum nächsten; „Was fehlt noch?“ ergänzt Maße nach Absicht; 10.000-Elemente-DXF bearbeitbar |
| Körper | Extrude (alle Ausdehnungen, Verjüngung, dünnwandig), Revolve, Sweep, Loft, Rib, Web, Emboss, Grundkörper, Coil, Bohrung nach Norm, Gewinde (auch druckbar), Muster (auch entlang Pfad), Spiegeln, Press Pull, Rundung (variabel), Fase, Shell, Draft, Combine, Split, Fläche entfernen/ersetzen/teilen, Bewegen, Ausrichten, Skalieren |
| Für den Zweck | Passung (ISO 286 und 3D-Druck), „Schraube hier“, Einschmelzmuttern, Tropfen-Bohrung, Druckfasen |
| Parametrik | globale Timeline (umsortieren, gruppieren, zurückspulen), Parameter, Notiz als Parameterliste, Konfigurationen (S/M/L), Maß am Modell ändern, Abhängigkeiten sichtbar vor dem Löschen |
| Baugruppe | Komponenten, 7 Joint-Arten mit Grenzen, Ketten, geschlossene Ketten (OndselSolver), Animation mit Kollision, Werkzeuge über Komponentengrenzen |
| Prüfen | Messen ohne Werkzeug, Masse und Schwerpunkt, Schnitt, Druckansicht (Überhang, Bett, Wanddicke) mit Reparatur per Klick |
| Sicherheit | immer gespeichert, Versionen mit Time-Machine-Regel, Vergleich als Geisterbild, Varianten; Fehler erklären sich und schlagen Werte vor; Bezüge prüfen sich selbst |
| Stift | Scribble mit Druck, Schönschrift (jetzt schrittweise einstellbar), Handschrift lesen (offline), Rotstift (R2, M5, Ø8 … am Modell werden Features), Grafiktablett-Tasten |
| Austausch | Export STL, 3MF (Farben), STEP (Farben, Komponenten), DXF; Import STEP, DXF, SVG, Foto → Skizze; Drucken öffnet den Slicer |
| Oberfläche | Liquid Glass mit echtem Shader, Hell/Dunkel, Bedienungshilfen, Deutsch/Englisch, Befehlssuche mit Sätzen („4 Löcher M3 in die Ecken …“), Hilfe mit 97 Artikeln |

### 2.2 Was es besonders macht

Kein anderes Programm hat diese Kombination:

- **Fehler, die sich erklären und reparieren** (Rundung zu groß → größter Wert, der geht). Fusion meldet nur.
- **Die Notiz ist die Parameterliste**, mit Konfigurationen als Spalten. Fusion hat dafür eine Tabelle in einem
  Dialog, Onshape Konfigurationstabellen.
- **Druck im Viewport** mit Reparaturvorschlägen und Passungen, die das Spiel fürs Drucken kennen.
- **Handschrift als Befehl** (Rotstift), offline gelesen.
- **Immer gespeichert, lokal**, mit Versionen und Varianten, ganz ohne Cloud.
- **Native Linux-App** mit Wayland, Grafiktablett und Touchpad-Gesten, die KDE sonst für sich behält.

### 2.3 Ehrliche Schwächen

- **Verteilung:** Das AppImage ist für Arch-Systeme gebaut. Wer Ubuntu oder Fedora nutzt (die Mehrheit der
  Linux-Desktops), kommt nur über `install.sh` mit Container dran. Auf Flathub, wo Linux-Nutzer Programme suchen, fehlt MyCAD.
- **Kein Mesh rein:** STL, 3MF und OBJ lassen sich nicht öffnen. Im 3D-Druck ist das der häufigste Einstieg („dieses
  Modell von Printables, nur das Loch größer“).
- **Keine Zeichnung:** Wer ein Teil fräsen, drehen oder lasern lässt, braucht ein Blatt mit Maßen (PDF). Heute geht nur
  DXF der Skizze.
- **Oberfläche voll:** Die Werkzeugleiste passt bei 1500 px gerade so. Jedes weitere Werkzeug muss in einen Aufklapper
  (heute schon 9 Gruppen mit versteckten Werkzeugen).
- **Lesen der Handschrift** ist bei echter Tablett-Schrift unsicher (18 % Zeichenfehler roh). Alles, was darauf aufbaut,
  erbt das.
- **Ein-Personen-Projekt auf FreeCAD-Kern:** Robustheit hängt an OCCT und an übernommenem FreeCAD-Code. Die
  Fehlerklassen-Tests und der Fuzzer gleichen das gut aus, aber jedes große Feature erhöht die Fläche.

---

## 3. Der Markt im Herbst 2026

| Programm | Richtung 2026 | Was daraus für MyCAD folgt |
|---|---|---|
| **Fusion** | Autodesk Assistant (Tech Preview seit März 2026: Sätze → Extrude, Fillet, Hole …, auch CAM und Zeichnungen), AutoConstrain für Skizzen, KI-Zeichnungen; Neural CAD angekündigt. Personal-Lizenz: nicht kommerziell, 10 bearbeitbare Dokumente, Hub-Änderungen ärgern Nutzer; nur Cloud, kein Linux | Assistent und Auto-Bedingungen sind Standard geworden. MyCAD hat „Was fehlt noch?“ und Sätze in Strg+K, aber nur fest verdrahtet |
| **Onshape** | AI Advisor im Arbeitsbereich (Bedrock/Cloud), geplant: FeatureScript-Vervollständigung per LLM, KI-Schnellrender; nur Browser, Cloud-Pflicht; Verzweigen und Zusammenführen wie Git | Versionen/Varianten hat MyCAD lokal; Zusammenführen fehlt |
| **SOLIDWORKS 2026** | AURA (Fragen in Sprache, Schritt-für-Schritt), KI-Zeichnungen, Verbindungselemente erkennen, Auto-Mates; 3DEXPERIENCE-Cloud | Zeichnungen und Normteile bleiben Kern der „Profi“-Welt |
| **Shapr3D** | Tablet zuerst, Vision Pro, direktes Modellieren mit Historie; 2026: Sweep-Steuerung, Wrap auf Zylinder, Prusa-Export, Zeichnungen ausgebaut | Stift und Kontext-Menüs an der Auswahl funktionieren; kein Linux |
| **Plasticity** | „CAD für Künstler“, NURBS, 2026: Hidden-Line-Export (Zeichnung light), Assets-Bibliotheken, Linux ja; einmal kaufen statt Abo | Zeigt: kleine Teams gewinnen mit Fokus, gutem Gefühl und Linux; Teile-Bibliotheken sind gefragt |
| **FreeCAD 1.1** (März 2026) | Vorschauen, Ziehgriffe, Drei-Punkt-Licht, besseres Wayland, neues Transform | Basis wird besser; Nutzer kritisieren weiter Skizzen-Bedienung und Gewinde, genau MyCADs Stärken |
| **KI-Neulinge** (Zoo Design Studio, Adam/CADAM, Backflip, MecAgent, Leo) | Text, Skizze, Foto oder Scan → bearbeitbares CAD; gut für einfache Teile (Halter, Bolzen), schwach bei Komplexem; meist Cloud und Abo ($99/Monat bei Zoo Pro) | Text-zu-CAD für einfache Teile wird Erwartung. Offline und ohne Abo bietet es niemand |
| **Linux-Native** (Dune 3D, SolveSpace, build123d/CadQuery, OpenSCAD) | Klein, technisch, Code-CAD wächst | Wer auf Linux Fusion sucht, findet heute kein Programm mit Fusion-Gefühl |

**Trends, auf die sich alle einigen:**
- Assistent in Sprache, der Befehle ausführt (nicht nur Hilfe sucht).
- Skizzen bestimmen sich selbst (AutoConstrain, „Was fehlt noch?“).
- Zeichnungen entstehen automatisch aus dem Modell.
- Mesh, Foto und Scan als Eingang ins parametrische CAD.
- Daten bleiben beim Nutzer (Autodesk bietet inzwischen lokale Projekte für Fertiger an). Der Wunsch nach „lokal“
  ist alt und laut.

---

## 4. Warum von Fusion zu MyCAD wechseln?

### 4.1 Für wen MyCAD gebaut sein sollte

**Hauptzielgruppe:** Maker und Konstrukteure auf Linux, die Teile für den 3D-Druck (und Laser/CNC) entwerfen, Fusion
kennen oder kennen wollen, und weder Cloud noch Abo noch VM wollen. Zweite Gruppe: kleine Werkstätten und Freelancer, die
an die Grenzen der Fusion-Personal-Lizenz stoßen (kommerziell, 10 Dokumente).

Nicht die Zielgruppe: Teams mit PDM, Konstruktion mit tausenden Teilen, CAM-Anwender. Dort gewinnt MyCAD nicht und
sollte es nicht versuchen.

### 4.2 Die Gründe, die schon heute tragen

| Wechselgrund | Wie stark |
|---|---|
| Läuft nativ auf Linux, mit Wayland, Tablett, Touchpad-Gesten | **sehr stark**, gibt es sonst nicht mit Fusion-Gefühl |
| Lokal, immer gespeichert, Versionen und Varianten, keine Dokumentgrenze, kein Abo | **sehr stark** |
| Für den 3D-Druck gebaut: Druckansicht mit Reparatur, Passungen mit Druckspiel, druckbare Gewinde, Schraube hier, Slicer-Übergabe | **stark**, kein großes CAD hat das so |
| Fehler erklären sich, Bezüge prüfen sich, Löschen zeigt Folgen vorher | stark für Einsteiger |
| Notiz als Parameterliste mit Konfigurationen | stark für parametrische Familien (Größen S/M/L) |
| Liquid Glass, Hell/Dunkel, Deutsch | angenehm, kein Hauptgrund |
| Handschrift, Rotstift, Grafiktablett | einzigartig, aber Nische |

**Kernbotschaft (Vorschlag):** *„Das Fusion für Linux. Lokal, ohne Abo, gemacht für den 3D-Druck.“*

### 4.3 Was Wechsler heute aufhält

| Hürde | Wer sie hat | Gewicht |
|---|---|---|
| STL/3MF/OBJ lässt sich nicht öffnen und umbauen | fast alle 3D-Drucker | **hoch** |
| Keine Zeichnung (PDF mit Maßen, Bohrungstabelle) | wer fertigen lässt, Werkstätten | **hoch** für Gruppe 2 |
| Nur Arch-AppImage, nicht auf Flathub | alle außerhalb von Arch | **hoch** für Reichweite |
| Kein Assistent in Sprache (die Großen haben ihn jetzt) | Einsteiger, Umsteiger | mittel, steigend |
| Kein Teile-Katalog (Schrauben, Muttern, Lager, Magnete als Körper) | Baugruppen, Gehäuse | mittel |
| Keine SpaceMouse-Unterstützung sichtbar (zu prüfen: FreeCAD-Kern kann spnav) | Profis | mittel |
| Kein Mehrfarben-Bemalen je Fläche für AMS/MMU-Drucker | Bambu/Prusa-Mehrfarbdrucker | mittel |
| Zahnräder, Federn, Scharniere, Schnapphaken | Mechanik-Maker | mittel |
| CAM, Blech, Flächen, Rendering | kleinere Gruppen | bewusst nicht (Vision) |

---

## 5. Neu denken: Was MyCAD anders und besser machen kann

Jede Idee: das Problem heute, die Idee, warum besser als bei den Großen, Aufwand (S/M/L/XL) und Risiko.

### 5.1 Mesh-Brücke: STL rein, Körper raus · L · hoch im Nutzen

- **Problem:** Remix ist der Alltag im 3D-Druck. Fusion braucht dafür ein kostenpflichtiges Add-in oder den Mesh-Workspace,
  SOLIDWORKS liefert „wasserdicht, aber nicht bearbeitbar“. Freelancer verkaufen „STL zu STEP“ als Dienstleistung.
- **Idee in drei Stufen:**
  1. STL/3MF/OBJ als **Referenz** öffnen: halbtransparent, auf Dreiecksflächen fangen, Skizzen auf ihre Ebenen legen,
     messen. Schon das löst „ich baue es sauber nach“.
  2. **Formen erkennen:** ebene Bereiche, Zylinder (Bohrungen, Wellen), Kegel per RANSAC finden und als echte Flächen
     anbieten („Hier ist eine Bohrung Ø5,1 – als Bohrung übernehmen?“).
  3. **Mesh wird Körper** für einfache, prismatische Teile: erkannte Flächen werden zu einem Volumenkörper, danach mit
     allen Werkzeugen änderbar (Loch größer, Wand dicker). Freiform bleibt Mesh, aber schneid- und vereinbar.
- **Warum besser:** Stufe 1–2 gibt es so in keinem Maker-CAD. Es passt zu „Foto wird Skizze“, MyCAD wird zum Werkzeug
  für Ersatzteile und Remix.
- **Risiko:** Stufe 3 ist Forschung. Darum erst 1 und 2 (Nutzen sofort), Stufe 3 an echten Dateien messen.

### 5.2 Kontext statt Werkzeugkasten (Oberfläche) · M

Siehe Kapitel 6.1. Hier nur der Kern: Die Auswahl bestimmt, was angeboten wird. Fläche gewählt → Press Pull, Extrude,
Bohrung, Shell, Skizze. Kante → Rundung, Fase. Profil → Extrude, Revolve. Das spart Wege, entlastet die volle Leiste und
ist auf dem Grafiktablett (ohne Rechtsklick) viel besser bedienbar.

### 5.3 Druck-Kalibrierung: MyCAD lernt deinen Drucker · M · einzigartig

- **Problem:** Jedes Druckteil braucht Spiel, und das Spiel hängt am Drucker, Material und Düse. Heute: 0,2 mm raten,
  drucken, ärgern, nachbessern. Die 3D-Druck-Passungen in MyCAD nutzen feste Werte aus den Einstellungen.
- **Idee:** „Drucker einmessen“ erzeugt ein kleines Testteil: Bolzen und Löcher in 0,05-mm-Stufen, eine Gewindeprobe,
  eine Überhangtreppe, ein Brückentest. Drucken, ausprobieren, in MyCAD anklicken, was passt und was nicht. MyCAD
  speichert ein **Druckerprofil** (Spiel je Passungsart, Lochschrumpf je Durchmesser, Überhanggrenze, kleinste Wand) und
  nimmt es überall: Passung, Bohrung, Gewinde, Einschmelzmutter, Druckansicht, „Druckbar machen“.
- **Warum besser:** Kein CAD macht das. Slicer kalibrieren Flussrate und Temperatur, aber nicht die Geometrie, die der
  Konstrukteur entwerfen muss. Passt perfekt zu 10.5/10.6.
- **Aufwand:** Testteil ist ein parametrisches Design, Profil ist eine Einstellungsgruppe, die Werkzeuge lesen sie schon
  fast (Passung, Gewinde-Clearance). Gering bis mittel.

### 5.4 Werkstattblatt: Zeichnung ohne Zeichnen · L

- **Problem:** Die Vision hat „Drawing“ ausgeschlossen. Ohne PDF mit Maßen kann man aber kein Teil fertigen lassen,
  und die Großen automatisieren Zeichnungen gerade per KI.
- **Idee:** Keine TechDraw-Werkbank, sondern **ein Knopf**: MyCAD wählt die Ansichten (drei Seiten + Iso, Schnitt durch
  Bohrungen), setzt die **Maße aus der Absicht**, die es schon kennt (Skizzenmaße, Bohrungsnorm als Bohrungstabelle,
  Passung als „Ø20 H7“, Gewinde „M5“, Fasen). Schriftfeld aus dem Design (Name, Material, Masse, Version). Export PDF
  und DXF. Ändern geht über das Modell, nicht über das Blatt.
- **Warum besser:** Für 90 % der Maker-Teile reicht genau das, ohne Zeichnungs-Lernkurve. Und es kennt MyCADs eigene
  Absichten (Passungen, Normbohrungen), die eine generische Ableitung nicht hat.
- **Risiko:** Bemaßungs-Layout ohne Überlappen ist schwer. Darum erst Ansichten + Bohrungs-/Passungstabelle +
  Hauptmaße, keine vollständige Bemaßung.

### 5.5 Lokaler Assistent: „Sag, was du willst“ – offline · L

- **Problem:** Die Großen haben jetzt Assistenten, alle in der Cloud (Datenschutz, Abo, Netz nötig). MyCAD hat feste
  Sätze in Strg+K (Löcher, Rundung, Fase, Muster).
- **Idee:** Ein kleines Sprachmodell **lokal** (llama.cpp, quantisiert, Download auf Wunsch) übersetzt Sätze in eine
  **kleine, geprüfte Befehlssprache**, die MyCAD schon spricht (die Strukturen hinter 11.10 und dem Rotstift). Jede
  Antwort ist eine Vorschau mit Timeline-Schritten, Enter übernimmt, Strg+Z nimmt zurück. Dazu: „Warum ist das rot?“
  erklärt einen Fehler, „Was hängt an dieser Skizze?“ zeigt Abhängigkeiten.
- **Warum besser:** Offline, kostenlos, Daten bleiben auf dem Rechner. Das Modell darf nur Befehle vorschlagen, die
  MyCAD prüft, also keine erfundene Geometrie.
- **Risiko:** Größe (1–4 GB), Qualität kleiner Modelle. Darum: die Befehlssprache zuerst (ohne KI nutzbar, testbar),
  das Modell ist austauschbar, optional, und ohne Modell bleibt Strg+K wie heute.

### 5.6 Code-Schritt in der Timeline · M

- **Problem:** Code-CAD (OpenSCAD, build123d, CadQuery) wächst, besonders auf Linux. KI-Neulinge erzeugen Code
  (Adam: OpenSCAD) statt Geometrie. Klick-CAD und Code-CAD leben getrennt.
- **Idee:** Ein Timeline-Schritt „Code“: ein Python-Stück (build123d-artig, auf MyCADs eigenen Funktionen), das einen
  Körper erzeugt oder ändert, mit Parametern aus der Notiz. Zahnräder, Gitter, Lochmuster nach Formel, Texte aus Listen.
  Wie jeder Schritt umsortierbar, unterdrückbar, mit Fehlermodell.
- **Warum besser:** Das Beste aus beiden Welten in einer Datei, und der lokale Assistent (5.5) kann Code schreiben, den
  man lesen und ändern kann, statt Black-Box-Geometrie.
- **Risiko:** Sicherheit (Code aus fremden Dateien). Darum nur nach Bestätigung ausführen, wie Makros in Office.

### 5.7 „Zu groß fürs Druckbett“ und Druckfertig von Ende zu Ende · M

- **Idee 1, Teilen mit Verbindern:** Ein Teil größer als das Bett (Profil aus 5.3 kennt die Größe) → Vorschlag, wo
  geteilt wird, mit Schwalbenschwanz, Stiften oder Schraubenlaschen; die Verbinder bekommen das Spiel aus dem Profil.
- **Idee 2, Druckrichtung vorschlagen:** die Lage mit der wenigsten Stützfläche und der kleinsten Höhe, als Vorschau
  zum Durchblättern (heute wählt man die Unterseite selbst).
- **Idee 3, Mehrfarben je Fläche:** Flächen anmalen (Aussehen je Fläche gibt es schon) und als Farbzuweisung in den
  3MF schreiben, damit AMS/MMU-Drucker ohne erneutes Bemalen im Slicer drucken.
- **Warum besser:** Die Arbeit, die heute zwischen CAD und Slicer hängt, passiert dort, wo man sie versteht.

### 5.8 Bibliothek: eigene Teile und Normteile · M

- Eigene Körper und Komponenten aus früheren Designs per Ziehen einfügen (Plasticity hat 2026 genau das als „Assets“,
  Shapr3D „Projekte importieren“).
- Normteile als **echte Körper**: Schrauben, Muttern, Scheiben, Einschmelzmuttern, Kugellager (608, 625 …),
  Magnete (Würfel/Scheibe), Alu-Profile 2020/2040. „Schraube hier“ setzt dann auch die Schraube ein, inklusive Stückliste.
- Zweck-Werkzeuge erweitern: Zahnrad (Evolvente), Feder, Scharnier (auch druckbar in einem Stück), Schnapphaken,
  Gehäuse mit Deckel. Jeweils als Schritt mit Parametern, wie die Passung.

### 5.9 Stift zuerst, konsequent · M

MyCAD ist das einzige Desktop-CAD mit ernsthafter Stift-Unterstützung auf Linux. Nächste Schritte:
- Radialmenü auf einer Stift-Taste (statt Rechtsklick), mit den Kontext-Werkzeugen aus 5.2.
- Skizzieren mit dem Stift: gezeichnete Linien und Kreise werden sofort Skizzengeometrie mit Bedingungen (Scribble →
  Skizze gibt es, aber als eigener Schritt).
- Gesten: Häkchen = Fertig, Kritzeln = Löschen, Pfeil von einer Fläche weg = Press Pull.
- Die Lese-Qualität ist der Engpass (18 % Fehler bei echter Schrift). Optional: Erkennung auf die eigene Schrift
  anlernen (einige hundert Zeilen), lokal.

### 5.10 Versionen zusammenführen · M · niedrig in der Priorität

Varianten gibt es, Übernehmen auch, Zusammenführen nicht (Onshape kann es). Für eine Person seltener nötig als im
Team. Erst, wenn jemand danach fragt.

---

## 6. Oberfläche: verbessern, vereinfachen, neu gestalten?

### 6.1 Befund

- **Oben:** zwei Zeilen mit 35 Plätzen (FILE, CREATE, MODIFY, CONSTRUCT, ASSEMBLE, INSPECT, UTILITIES), 9 davon
  Aufklapper mit bis zu 6 Werkzeugen. Bei 1500 px voll (Plan 11.11). Auf dem 13–14"-Laptop wird es eng.
- **Links:** Browser, 290 px breit, meist mit wenig Inhalt („Unnamed › Design“).
- **Unten:** Timeline (jetzt mit Rollen und Pfeilen), Wiedergabe-Knöpfe.
- **Rechts:** ViewCube, Fensterknöpfe; Werkzeug-Dialoge erscheinen als Inspector.
- **Viele Wege, ein Ziel:** Werkzeugleiste, Rechtsklick-Menüs, Strg+K, Doppelklick auf Flächen, Rotstift. Das ist
  mächtig, aber für Einsteiger unübersichtlich.

### 6.2 Empfehlung: kein Komplett-Neuentwurf, sondern „Kontext zuerst“

Liquid Glass ist ein echtes Alleinstellungsmerkmal und technisch teuer erkauft. Ein neuer Look würde Arbeit vernichten,
ohne ein Problem zu lösen. Das Problem ist die **Menge an gleichzeitig sichtbaren Werkzeugen**, nicht ihr Aussehen.

1. **Kontext-Leiste an der Auswahl** (MyStyle: Glas-Kapsel, schwebt neben der Auswahl, wie Shapr3D und das
   iPadOS-Bearbeitungsmenü): 4–6 Werkzeuge, die zur Auswahl passen, plus „Mehr…“ (öffnet Strg+K gefiltert). Auf dem
   Grafiktablett über eine Stift-Taste auch als Radialmenü.
2. **Werkzeugleiste als Kategorien:** Eine Zeile mit den Kategorien als Knöpfen (Skizze, Erzeugen, Ändern,
   Konstruieren, Baugruppe, Prüfen, Drucken). Ein Klick öffnet ein Glas-Popover mit allen Werkzeugen der Kategorie in
   einem Raster mit Namen. Die 5–6 häufigsten Werkzeuge bleiben direkt sichtbar (Skizze, Extrude, Bohrung, Rundung,
   Press Pull, Messen). Ergebnis: eine Zeile statt zwei, Platz für neue Werkzeuge ohne Umbruch, auf kleinen
   Bildschirmen ruhiger.
3. **Browser schmaler und klüger:** standardmäßig eingeklappt zu einer Kapsel mit dem Design-Namen; aufgeklappt mit
   Körpern, Komponenten, Skizzen, **Parametern und Notizen** (heute verteilt). Vorschaubilder der Körper.
4. **„Drucken“ als eigene Kategorie:** Druckansicht, Druckbar machen, Druckrichtung, Kalibrierung (5.3), Teilen (5.7),
   An Slicer senden. Heute verteilt auf INSPECT, FILE und Strg+K.
5. **Erster Start mit Vorlagen:** Statt eines leeren Designs Vorlagen mit Notiz-Parametern (Box mit Deckel, Wandhalter,
   Gehäuse für Platine X × Y, Distanzhülse, Kabelclip). Ändern der Notiz ändert das Teil. Das zeigt in 30 Sekunden, was
   MyCAD kann.
6. **Timeline:** Mini-Vorschau beim Überfahren eines Schritts (Zustand nach dem Schritt), Filter nach Körper/Komponente.

Was ich **nicht** empfehle: Workspaces wie in Fusion (Design/Render/Manufacture) einzuführen. MyCADs eine Arbeitsfläche
ist einfacher und eine echte Stärke.

---

## 7. Bestehendes verbessern

Aus dem Plan und dem heutigen Stand, nach Nutzen sortiert:

| Punkt | Warum |
|---|---|
| Robustheit Rundung/Fase an schwierigen Kanten (OCCT 8 hilft), klare Teilergebnisse statt Fehlschlag | häufigster Frust in jedem CAD |
| SpaceMouse über spnav (prüfen, ob der FreeCAD-Kern es mitbringt und nur die Einstellung fehlt) | Profis erwarten es |
| Skizzen: Auto-Bedingungen nach dem Zeichnen ganzer Formen (Fusion AutoConstrain), „Was fehlt noch?“ als Standard beim Verlassen | Fusion hat es 2025/26 ausgebaut |
| Handschrift lesen: auf eigene Schrift anlernen (optional) | alles mit Stift erbt die Qualität |
| Foto → Skizze an echten Handyfotos messen (D16–D19 wartet darauf) | Ersatzteil-Workflow |
| Große Skizzen: inkrementeller Löser (C12), nur wenn Nutzer daran stoßen | heute 0,4 s je Linie bei 10.000 Elementen |
| Baugruppen: Kollision für viele Teile (C13) | erst ab einigen hundert Körpern |
| Hilfe: kurze Lernpfade („Von Fusion umsteigen“: Begriffe, Tastenkürzel, was anders ist) | senkt die Wechselhürde direkt |

---

## 8. Vorschlag Phase 12 (Reihenfolge nach Nutzen für den Wechsel, Abhängigkeiten berücksichtigt)

| Nr. | Paket | Aufwand | Warum jetzt |
|---|---|---|---|
| 12.1 | **Mesh-Brücke Stufe 1+2**: STL/3MF/OBJ als Referenz öffnen, fangen, messen, Skizze auf Mesh-Ebene; Ebenen/Zylinder erkennen und übernehmen | L | größte Hürde für 3D-Drucker, verbindet Foto→Skizze und Remix |
| 12.2 | **Kontext-Leiste** an der Auswahl + Radialmenü auf Stift-Taste | M | entlastet die volle Leiste, macht Platz für alles Weitere |
| 12.3 | **Werkzeugleiste als Kategorien** (eine Zeile, Popover mit Namen), Kategorie „Drucken“ | M | baut auf 12.2, Platz für 12.4–12.7 |
| 12.4 | **Druckerprofil und Kalibrier-Testteil**, alle Druck-Werkzeuge lesen das Profil | M | einzigartig, klein, starker Grund für Maker |
| 12.5 | **Werkstattblatt**: Ansichten + Bohrungs-/Passungstabelle + Hauptmaße → PDF/DXF | L | Hürde für alle, die fertigen lassen |
| 12.6 | **Flathub** (Flatpak) neben dem AppImage, Hinweis „Läuft auf jedem Linux“ | M | Reichweite; ohne das bleibt MyCAD für Ubuntu/Fedora versteckt |
| 12.7 | **Normteile als Körper** + Zweck-Werkzeuge Zahnrad, Scharnier, Schnapphaken | M | Baugruppen und Mechanik |
| 12.8 | **Mehrfarben je Fläche → 3MF**, Druckrichtung vorschlagen, Teilen mit Verbindern | M | Druckfertig von Ende zu Ende |
| 12.9 | **Lokaler Assistent**: erst Befehlssprache (ohne KI testbar), dann optionales lokales Modell | L | die Großen haben es; offline ist unser Vorteil |
| 12.10 | **Code-Schritt** in der Timeline | M | nach 12.9, Assistent kann dann Code schreiben |
| 12.11 | **Vorlagen beim ersten Start** + Hilfe-Pfad „Von Fusion umsteigen“ | S | macht alles Vorige sichtbar |

**Bewusst nicht** (bestätigt die Vision): CAM, Flächen/T-Splines, Blech, Rendering-Workspace, Simulation,
Cloud-Zusammenarbeit, Windows/macOS. Jede davon würde MyCAD zum kleineren Fusion machen statt zum besseren für
seine Zielgruppe. Einzige Neubewertung: **Zeichnung**, aber als Werkstattblatt ohne eigene Werkbank (12.5).

---

## 9. Entscheidungen für dich

1. **Zielgruppe und Botschaft:** „Das Fusion für Linux, lokal, ohne Abo, gemacht für den 3D-Druck.“ Passt das, oder
   soll MyCAD breiter (auch Werkstätten) zielen?
2. **Zeichnung:** Die Vision schließt sie aus. Werkstattblatt (12.5) ja oder nein?
3. **Oberfläche:** Kontext-Leiste und Kategorien (evolutionär) oder ein mutigerer Neuentwurf?
4. **KI:** lokaler Assistent mit optionalem Modell (1–4 GB Download) – gewollt?
5. **Verteilung:** Flathub ja? Das heißt auch: Bauen außerhalb von Arch, Flatpak-Regeln (Sandbox, Portale für
   Tablett-Zugriff und Slicer-Start).
6. **Reihenfolge:** Phase 12 wie vorgeschlagen, oder etwas vorziehen?

---

## Quellen

- Fusion: [March 2026 Product Update](https://www.autodesk.com/products/fusion-360/blog/march-2026-product-update-whats-new/),
  [AutoConstrain](https://www.autodesk.com/products/fusion-360/blog/autoconstrain-for-fusion-is-here/),
  [Year in Review 2025](https://www.autodesk.com/products/fusion-360/blog/autodesk-fusion-year-in-review-2025/),
  [Automate Drawing Creation with Autodesk Assistant](https://www.autodesk.com/products/fusion-360/blog/automate-drawing-creation-autodesk-assistant/),
  [AI Drawing Automation](https://www.autodesk.com/products/fusion-360/blog/ai-drawing-automation-in-autodesk-fusion-revolutionizing-the-design-process/),
  [Your Data Where You Need It](https://www.autodesk.com/products/fusion-360/blog/your-fusion-data-where-you-need-it/),
  [Fusion for Personal Use](https://www.autodesk.com/products/fusion-360/blog/fusion-for-personal-use-vs-autodesk-fusion/),
  [Personal-Lizenz im Detail (stacksheriff)](https://stacksheriff.com/3d-printing/fusion-360-free-personal-license/),
  [Fusion-Alternativen (stacksheriff)](https://stacksheriff.com/3d-printing/fusion-360-alternatives/),
  [Autodesk-Forum: Cloud vs. Offline](https://forums.autodesk.com/t5/fusion-360-feedback-hub/closed-what-s-your-experience-working-in-the-cloud-vs-offline/m-p/9529938)
- Onshape: [AI Advisor im Design-Bereich (DE247)](https://www.digitalengineering247.com/article/onshape-ai-advisor-now-embedded-directly-in-the-design-environment),
  [Onshape AI Blog](https://www.onshape.com/es/blog/ai-artificial-intelligence-cloud-native-cad-pdm-platform),
  [What's New: AI Advisor](https://www.onshape.com/en/resource-center/what-is-new/ai-advisor-configurable-variable-studios-simulation)
- SOLIDWORKS: [What's New 2026](https://www.solidworks.com/product/whats-new-2026.md),
  [AI in SOLIDWORKS (GoEngineer)](https://www.goengineer.com/en-us/blog/ai-in-solidworks),
  [AI Companions 2026 (CADimensions)](https://resources.cadimensions.com/cadimensions-resources/new-solidworks-ai-companions-and-features-coming-in-2026)
- Shapr3D: [Changelog](https://support.shapr3d.com/hc/en-us/articles/7536511116188-Changelog),
  [Wikipedia](https://en.wikipedia.org/wiki/Shapr3D),
  [Vision Pro](https://www.shapr3d.com/blog/introducing-shapr3d-for-apple-vision-pro),
  [CIMdata-Kommentar](https://www.cimdata.com/de/news/item/28501-shapr3d-democratizing-cad-across-organizations-commentary)
- Plasticity: [2026.2 (Digital Production)](https://digitalproduction.com/2026/10/21/plasticity-2026-2),
  [2026.1 (CG Channel)](https://cgchannel.com/2026/04/plasticity-2026-1-is-out/)
- FreeCAD: [Release Notes 1.1](https://wiki.freecad.org/Release_notes_1.1),
  [FreeCAD 1.1 released (Blog)](https://freecad.github.io/Website/news/freecad-version-1-1-released/),
  [AlternativeTo-Zusammenfassung](https://alternativeto.net/news/2026/3/freecad-1-1-adds-three-point-lighting-part-design-previews-and-major-fem-upgrades)
- KI-CAD: [AI CAD Tools 2026 (Superkind)](https://superkind.ai/blog/ai-cad-tools),
  [Best AI CAD Tools (llms.blog)](https://www.llms.blog/posts/best-ai-cad-tools),
  [AI CAD Copilots 2026 (MecAgent)](https://mecagent.com/blog/ai-cad-tools-2026),
  [Adam/CADAM](https://www.developersdigest.tech/blog/adam-ai-cad-yc-w25-open-source-text-to-cad),
  [AI CAD Tools tested (RapidDirect)](https://www.rapiddirect.com/blog/best-ai-cad-tools-review/)
- Linux und offene CAD: [Fusion-Alternativen für Linux (AlternativeTo)](https://alternativeto.net/software/fusion-360/?platform=linux),
  [CAD für Linux (All3DP)](https://all3dp.com/2/cad-software-for-linux-best-tools/),
  [Dune 3D (Hackaday)](https://hackaday.com/tag/dune3d/),
  [build123d](https://github.com/gumyr/build123d)
- Nutzerstimmen: [Time for a change of CAD? (V1 Engineering)](https://forum.v1engineering.com/t/time-for-a-change-of-cad/31203),
  [FreeCAD tips for a Fusion refugee](https://groups.google.com/g/3d-printing-tips--tricks/c/lGfhqTXdtmM),
  [From Fusion to Onshape (Printables)](https://www.printables.com/article/from-fusion-to-onshape-my-cad-workflow-rebuild-J5EMv45)
- 3D-Druck-Markt: [Bambu Lab 2025 (3DPrint.com)](https://3dprint.com/324181/bambu-lab-says-2025-was-a-breakout-year-10-million-monthly-users-and-real-business-growth/),
  [MakerWorld-Daten (3D Printing Industry)](https://3dprintingindustry.com/news/bambu-lab-data-highlights-sustained-3d-printing-activity-and-creator-growth-on-makerworld-249474/)
- Mesh zu CAD: [Mesh-to-CAD Reverse Engineering (Novedge)](https://novedge.com/blogs/design-news/mesh-to-cad-reverse-engineering-in-modern-design-software),
  [STL to SolidWorks (SourceCAD)](https://sourcecad.com/blog/stl-to-solidworks/),
  [Solid evidence (EVERYTHING to solid)](https://dev.to/open-madscience/solid-evidence-278)

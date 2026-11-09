# Handschrift-Modell für Scribbles

Scribbles lesen Handschrift offline mit **DE·HTR v2** (`naeyn/de-htr-web-v2`): ein kleines Modell für deutsche
Handschrift (ResNet18 + BiLSTM, CTC, 10,4 MB int8). Es läuft mit onnxruntime direkt in MyCAD, ohne Netz.

- Modellkarte: https://huggingface.co/naeyn/de-htr-web-v2 (Revision `6241c1ff0fd42725e0dc46fcd3217469cac851bb`)
- Code: https://github.com/naeyn/de-htr-web
- Lizenz: Apache-2.0 für Gewichte und Code, siehe `LICENSE`
- Trainingsdaten und deren Namensnennung: `NOTICE-training-data.md`
  (ScaDS.AI German Handwriting, CC BY 4.0, Burghardt, Alzin, Nestler et al., Universität Leipzig;
  fhswf/german_handwriting, AFL-3.0, FH Südwestfalen)

`model.onnx` liegt nicht im Repo: CMake lädt die Datei beim Konfigurieren und prüft sie gegen
SHA-256 `b576a0a1281b9be46b2574028b75575e041b7d7cb650f063886e733467cc1499`. Danach wird sie als Qt-Ressource
`:/mycad/htr/model.onnx` in DesignGui eingebaut. Fehlt onnxruntime (`onnxruntime-cpu` im Dev-Container) oder
schlägt der Download fehl, baut MyCAD ohne Erkennung: Die Schönschrift räumt dann weiter auf, liest aber nicht.

`config.json` ist die unveränderte Konfiguration des Modells. Das Alphabet daraus steht wörtlich in
`ScribbleRead.cpp`. Ø und ± kennt das Modell nicht; die CAD-Korrektur dort ergänzt sie.

Prüfung mit dem echten Modell: `tests/scribble_read_check.cpp`.

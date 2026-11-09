# Training-data NOTICE (de-htr-tiny / de-htr-web v2)

The released model weights are licensed Apache-2.0 **for the rights held by this project**. This notice provides dataset-level attribution under a conservative reading of CC attribution duties for AI training (cf. Creative Commons guidance on CC-licensed works in AI training).

## Data actually in the released v2 weights

The released de-htr-web v2 checkpoint (Run I) was trained **exclusively on real handwriting**: the ScaDS.AI corpus (gold lines, word crops, page-XML extra lines; CC BY 4.0) and fhswf/german_handwriting (AFL-3.0; its ablation showed a material gain of −0.94 CER, so it is included, contrary to the earlier default-off plan). No synthetic data, no Leipzig corpora, no pseudo-labels are in the training path of the released weights. The synthetic corpora and fonts below were used only in ablation arms and in the released renderer/pipeline artifacts.

## Real handwriting images

| Corpus | Use | License | Attribution |
|---|---|---|---|
| ScaDS.AI German Line- & Word-Level Handwriting (Zenodo, DOI 10.5281/zenodo.18301532, v1.0) | Train/val/test lines, words, and page-XML ground-truth line crops | CC BY 4.0 | Burghardt, Alzin, Nestler et al., ScaDS.AI / Universität Leipzig. Changes: cropping, grayscale normalization, NFC text normalization, writer-disjoint re-splitting. |
| fhswf/german_handwriting (Hugging Face) | Stage-3 auxiliary training; **included in the release candidate (ablation gain −0.94 CER)** | AFL-3.0 | FH Südwestfalen handwriting recognition project. Images are never redistributed by this project. Writer identity is approximated by capture-day (documented assumption). |

## Synthetic text corpora (rendered to images; text never redistributed)

Rendered synthetic images embed source-corpus text verbatim and are **not published**. The renderer, corpus lock (digests), font list, and seed are released instead.

| Corpus | License | Attribution / notes |
|---|---|---|
| German Wikipedia dump 2026-07-01 | CC BY-SA 4.0 | German Wikipedia contributors. ShareAlike applies to the text, which is not redistributed. |
| German Wikinews dump (acquired 2026-07-29, digest-pinned) | CC BY 2.5 | German Wikinews contributors. |
| OpenLegalData court decisions (dump-20260520) | ODbL 1.0 | openlegaldata.io. ODbL notice: this produced work uses the OpenLegalData database; ODbL does not clear copyright in individual contents — only official decision text (amtliche Werke, § 5 UrhG) is used. |
| CPP-BT Bundestag plenary protocols (2026-01-17) | CC0 1.0 / § 5 UrhG amtliche Werke | Deutscher Bundestag; CPP-BT corpus. Bundestag disclaims third-party clearance; procedural text only, parentheticals stripped. |
| Tatoeba German sentences (deu, detailed export) | CC BY 2.0 FR | Tatoeba contributors (aggregate attribution; usernames omitted from the local derivative). |

Explicitly **absent** from the training path of released weights: Leipzig Corpora Collection (CC BY-NC-SA 3.0 — removed 2026-07-29 and replaced by the sources above), IAM (research-only), any VLM-generated pseudo-labels (replaced by page-XML ground truth from the ScaDS archive).

## Fonts

Synthetic rendering used 59 handwriting fonts from the Google Fonts repository, all SIL OFL 1.1, digest-pinned to revision 7ff85c87f93ea6cca5f41c69f2e4edcb90240f26 (see `data/raw/synthetic-fonts/fonts-v2.json` for per-font attribution; 5 fonts excluded after a glyph-fidelity audit).

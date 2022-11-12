# muskit's GMMK Pro Custom Firmware

This is my custom keymap for the GMMK Pro (ANSI layout). This repository was forked from QMK. You can find my code at [`keyboards/gmmk/pro/ansi/keymaps/msk/`](keyboards/gmmk/pro/ansi/keymaps/msk/).

**To compile:**
`qmk compile -kb gmmk/pro/ansi -km msk`

**To flash (and automatically compile):**
`qmk flash -kb gmmk/pro/ansi -km msk`

## RGB Indices Reference
```
RGB CODES
|67| _0, _6, 12, 18, 23, 28, 34, 39, 44, 50, 56, 61, 66, 69,     __, |68| 
|70|                                                                 |71|
|73| _1, _7, 13, 19, 24, 29, 35, 40, 45, 51, 57, 62, 78, 85,     72, |74|
|76| _2, _8, 14, 20, 25, 30, 36, 41, 46, 52, 58, 63, 89, 93,     75, |77| 
|80| _3, _9, 15, 21, 26, 31, 37, 42, 47, 53, 59, 64,     96,     86, |81| 
|83| _4,     10, 16, 22, 27, 32, 38, 43, 48, 54, 60,     90, 94, 82, |84|
|87| _5, 11, 17,             33,             49, 55, 65, 95, 97, 79  |88| 
|91|                                                                 |92|
```

# Quantum Mechanical Keyboard Firmware

[![Current Version](https://img.shields.io/github/tag/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/tags)
[![Discord](https://img.shields.io/discord/440868230475677696.svg)](https://discord.gg/Uq7gcHh)
[![Docs Status](https://img.shields.io/badge/docs-ready-orange.svg)](https://docs.qmk.fm)
[![GitHub contributors](https://img.shields.io/github/contributors/qmk/qmk_firmware.svg)](https://github.com/qmk/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/qmk/qmk_firmware.svg?style=social&label=Fork)](https://github.com/qmk/qmk_firmware/)

This is a keyboard firmware based on the [tmk\_keyboard firmware](https://github.com/tmk/tmk_keyboard) with some useful features for Atmel AVR and ARM controllers, and more specifically, the [OLKB product line](https://olkb.com), the [ErgoDox EZ](https://ergodox-ez.com) keyboard, and the [Clueboard product line](https://clueboard.co).

## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [Docsify](https://docsify.js.org/) and hosted on [GitHub](/docs/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls), or by clicking the "Edit this page" link at the bottom of any page.

## Supported Keyboards

* [Planck](/keyboards/planck/)
* [Preonic](/keyboards/preonic/)
* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Clueboard](/keyboards/clueboard/)
* [Cluepad](/keyboards/clueboard/17/)
* [Atreus](/keyboards/atreus/)

The project also includes community support for [lots of other keyboards](/keyboards/).

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

## Official Website

[qmk.fm](https://qmk.fm) is the official website of QMK, where you can find links to this page, the documentation, and the keyboards supported by QMK.

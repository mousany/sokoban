# Sokoban

This repo contains the framework of the Sokoban game for the Longan Nano development board. And it is the final project of the course Computer Architecture I.

In this project, a Sokoban game is implemented on the Longan Nano development board. The game is based on the framework provided by the course. The framework is modified to support the game. The game is implemented in C language and RISC-V assembly, and is compiled by the RISC-V toolchain platformio.

For full details of this project, please see course website.

## Project Structure

The project is based on the framework provided by the course. The framework is modified to support the game. The project structure is shown below.

```
.
├── LICENSE
├── Makefile
├── README.md
├── dfu-util
├── include
│   ├── README
│   ├── fatfs
│   │   ├── diskio.h
│   │   ├── ff.h
│   │   ├── ffconf.h
│   │   └── tf_card.h
│   ├── gd32v_pjt_include.h
│   ├── gd32vf103_libopt.h
│   ├── lcd
│   │   ├── bmp.h
│   │   ├── lcd.h
│   │   └── oledfont.h
│   ├── systick.h
│   └── utils.h
├── platformio.ini
└── src
    ├── assembly
    │   └── example.S
    ├── fatfs
    │   ├── 00history.txt
    │   ├── 00readme.txt
    │   ├── ff.c
    │   ├── ffsystem.c
    │   ├── ffunicode.c
    │   └── tf_card.c
    ├── lcd
    │   └── lcd.c
    ├── main.c
    ├── systick.c
    └── utils.c
```

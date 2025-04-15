/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * @Hardwares: Basic/Fire/Gray(PortA) + Module AIN4-20mA
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5Module-4-20mA:https://github.com/m5stack/M5Module-4-20mA
 */

#include <M5Stack.h>
#include "MODULE_4_20MA.h"
#include <M5GFX.h>

M5GFX display;
M5Canvas canvas(&display);
MODULE_4_20MA meter;

void show_current_value(void) {
    canvas.clear(BLACK);
    canvas.setCursor(80, 0);
    canvas.setTextSize(2);
    canvas.setTextColor(YELLOW);
    canvas.printf("4-20mA");
    canvas.setColor(ORANGE);
    canvas.drawLine(0, 25, 320, 25);
    canvas.setTextSize(2);
    canvas.setTextColor(GREEN);
    for (int i = 0; i < 4; i++) {
        canvas.setCursor(0, 30 + 30 * i);
        canvas.printf("CH%d Current:%.2fmA", i + 1,
                      (float)(meter.getCurrentValue(i)) / 100.0);
    }
    canvas.pushSprite(0, 0);
}

void setup() {
    M5.begin(true, false, true);
    M5.Power.begin();
    display.begin();
    canvas.setColorDepth(8);
    canvas.setFont(&fonts::efontCN_12);
    canvas.createSprite(display.width(), display.height());
    while (!(meter.begin(&Wire, MODULE_4_20MA_ADDR, 21, 22, 100000UL))) {
        canvas.clear(BLACK);
        canvas.setCursor(10, 0);
        canvas.println("No Module!");
        canvas.pushSprite(0, 0);
    }
}

void loop() {
    show_current_value();
}
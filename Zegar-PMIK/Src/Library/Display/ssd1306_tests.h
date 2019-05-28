/**
 * \file ssd1306_tests.h
 * \brief Biblioteka zewnetrzna do obslugi wyswietlacza OLED.
 * Plik zawiera testy wyswietlacza OLED.
 */

/**
 * This Library was originally written by Olivier Van den Eede (4ilo) in 2016.
 * Some refactoring was done and SPI support was added by Aleksander Alekseev (afiskon) in 2018.
 *
 * https://github.com/afiskon/stm32-ssd1306
 */

#ifndef __SSD1306_TEST_H__
#define __SSD1306_TEST_H__

void ssd1306_TestBorder();
void ssd1306_TestFonts();
void ssd1306_TestFPS();
void ssd1306_TestAll();

#endif // __SSD1306_TEST_H__

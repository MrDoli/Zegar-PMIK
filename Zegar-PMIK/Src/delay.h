/*
 * delay.h
 *
 * Author: Marcin Dolicher, Micha³ Stolarz
*/

/*
 * Define a delay function for debouncing button from keypad.
 */

static unsigned int msc = 0; // zmienna przechowujaca czas pozostaly czas opoznienia

void DelayTick(void);        // aktualizacja czasu opoznienia
void Delay(unsigned int ms); // ustawienie czasu opoznienia i zawieszenie dzialania programu

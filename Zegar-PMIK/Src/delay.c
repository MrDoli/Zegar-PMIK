/*
 * delay.c
 *
 * Author: Marcin Dolicher, Micha³ Stolarz
*/
#include "delay.h"

void DelayTick(void){
	// dekrementacja licznika (o ile jest wiekszy od 0)
	if (msc > 0){
		--msc;
	}
}

void Delay(unsigned int ms){
	// zmiana wartosci licznika
	// testowanie czy jest on wiekszy od 0
	msc = ms;
	while (msc > 0){
		//__NOP;
		//__NOP;
	}
}	


#ifndef MAIN_H_INC
#define MAIN_H_INC

#include <allegro.h>
#include <stdio.h>

#define BUFFER_SIZE 8

#define FREQ 44100

int max(int arg1, int arg2) {if(arg1 > arg2) return arg1; return arg2; }
int min(int arg1, int arg2) {if(arg1 < arg2) return arg1; return arg2; }
int workout(int arg1, int arg2, int mode);

#endif

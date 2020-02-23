ALLEGRO_MACOSX=1

allegSynth: main.c main.h
	gcc -o allegSynth main.c -L./lib -I ./include -lalleg

test:
	otool -L ./allegSynth

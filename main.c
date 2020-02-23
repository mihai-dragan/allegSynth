/*This is the main source file
for Stanleys Software Synthesizer.

Copyright James Stanley 2006

ssp.shorturl.com*/

#include "main.h"

int main() {

  allegro_init();

  AUDIOSTREAM *stream;
  int i, val = 0;
  int pitch = 0, done = 0, inc = 1;
  int mode = 0;
  int timer = 0;
  int key1 = 0, key2 = 0, key3 = 0, key4 = 0, key5 = 0;
  unsigned char *buffer;
  char *modes[5] = { "XOr", "Or", "And", "Max", "Min" };

  install_keyboard();
  install_timer();
  if (install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL) != 0) {
    allegro_message("Audio error. %s", allegro_error);
    exit(0);
  }

  if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 320, 200, 0, 0) != 0) {
    allegro_message("Video error. %s", allegro_error);
    exit(0);
  }

  set_window_title("SoftSynth by James Stanley");

  stream = play_audio_stream(BUFFER_SIZE, 8, 0, FREQ, 255, 128);
  textprintf_centre_ex(screen, font, 160, 100, makecol(255,255,255),makecol(0,0,0),"   %d, %s, %d   ",inc, modes[mode], voice_get_frequency(stream->voice));


  if(stream) {
    while (!key[KEY_ESC]) {
      buffer = get_audio_stream_buffer(stream);
      if(buffer) {
        for (i = 0; i < BUFFER_SIZE; i++) {
          done = 0;

          if(mode == 1 || mode == 3) buffer[i] = 0; else buffer[i] = 0xFF;//if we're on Or or Max mode, this fixes it.

          if(key[KEY_Q]) { buffer[i] = workout(buffer[i],(pitch >> 9) & 0xFF, mode); done = 1; }
          if(key[KEY_W]) { buffer[i] = workout(buffer[i],(pitch >> 8) & 0xFF, mode); done = 1; }
          if(key[KEY_E]) { buffer[i] = workout(buffer[i],(pitch >> 7) & 0xFF, mode); done = 1; }
          if(key[KEY_R]) { buffer[i] = workout(buffer[i],(pitch >> 6) & 0xFF, mode); done = 1; }
          if(key[KEY_T]) { buffer[i] = workout(buffer[i],(pitch >> 5) & 0xFF, mode); done = 1; }
          if(key[KEY_Y]) { buffer[i] = workout(buffer[i],(pitch >> 4) & 0xFF, mode); done = 1; }
          if(key[KEY_U]) { buffer[i] = workout(buffer[i],(pitch >> 3) & 0xFF, mode); done = 1; }
          if(key[KEY_I]) { buffer[i] = workout(buffer[i],(pitch >> 2) & 0xFF, mode); done = 1; }
          if(key[KEY_O]) { buffer[i] = workout(buffer[i],(pitch >> 1) & 0xFF, mode); done = 1; }
          if(key[KEY_P]) {
            if(timer <= 25) {
              buffer[i] = workout(buffer[i],0xFF, mode);
              done = 1;
              timer++;
            }
          } else timer = 0;

          if(key[KEY_A]) { buffer[i] = workout(buffer[i],(val >> 24) & 0xFF, mode); done = 1; }
          if(key[KEY_S]) { buffer[i] = workout(buffer[i],(val >> 22) & 0xFF, mode); done = 1; }
          if(key[KEY_D]) { buffer[i] = workout(buffer[i],(val >> 20) & 0xFF, mode); done = 1; }
          if(key[KEY_F]) { buffer[i] = workout(buffer[i],(val >> 18) & 0xFF, mode); done = 1; }
          if(key[KEY_G]) { buffer[i] = workout(buffer[i],(val >> 16) & 0xFF, mode); done = 1; }
          if(key[KEY_H]) { buffer[i] = workout(buffer[i],(val >> 14) & 0xFF, mode); done = 1; }
          if(key[KEY_J]) { buffer[i] = workout(buffer[i],(val >> 12) & 0xFF, mode); done = 1; }
          if(key[KEY_K]) { buffer[i] = workout(buffer[i],(val >> 10) & 0xFF, mode); done = 1; }
          if(key[KEY_L]) { buffer[i] = workout(buffer[i],(val >>  8) & 0xFF, mode); done = 1; }

          if(key[KEY_Z]) { buffer[i] = workout(buffer[i],(val >> 1) & 0xFF, mode); done = 1; }
          if(key[KEY_X]) { buffer[i] = workout(buffer[i],(val >> 2) & 0xFF, mode); done = 1; }
          if(key[KEY_C]) { buffer[i] = workout(buffer[i],(val >> 3) & 0xFF, mode); done = 1; }
          if(key[KEY_V]) { buffer[i] = workout(buffer[i],(val >> 4) & 0xFF, mode); done = 1; }
          if(key[KEY_B]) { buffer[i] = workout(buffer[i],(val >> 5) & 0xFF, mode); done = 1; }
          if(key[KEY_N]) { buffer[i] = workout(buffer[i],(val >> 6) & 0xFF, mode); done = 1; }
          if(key[KEY_M]) { buffer[i] = workout(buffer[i],(val >> 7) & 0xFF, mode); done = 1; }

          if(key[KEY_4_PAD]) {
            if(key1 == 0) {
              inc -= 5;
              key1 = 1;
              if(inc < -99) inc = -99;
              if(inc > 101) inc = 101;
              textprintf_centre_ex(screen, font, 160, 100, makecol(255,255,255),makecol(0,0,0),"   %d, %s, %d   ",inc, modes[mode], voice_get_frequency(stream->voice));
            }
          }
          else {
            key1 = 0;
          }
          if(key[KEY_5_PAD]) { inc = 1; textprintf_centre_ex(screen, font, 160, 100, makecol(255,255,255),makecol(0,0,0),"   %d, %s, %d   ",inc, modes[mode], voice_get_frequency(stream->voice)); }
          if(key[KEY_6_PAD]) {
            if(key2 == 0) {
              inc += 5;
              key2 = 1;
              if(inc < -99) inc = -99;
              if(inc > 101) inc = 101;
              textprintf_centre_ex(screen, font, 160, 100, makecol(255,255,255),makecol(0,0,0),"   %d, %s, %d   ",inc, modes[mode], voice_get_frequency(stream->voice));
            }
          }
          else {
            key2 = 0;
          }

          if(key[KEY_SPACE]) {
            if(key3 == 0) {
              mode++;
              key3 = 1;
              textprintf_centre_ex(screen, font, 160, 100, makecol(255,255,255),makecol(0,0,0),"   %d, %s, %d   ",inc, modes[mode], voice_get_frequency(stream->voice));
            }
          }
          else {
            key3 = 0;
          }
          if(mode == 5) { mode = 0; textprintf_centre_ex(screen, font, 160, 100, makecol(255,255,255),makecol(0,0,0),"   %d, %s, %d   ",inc, modes[mode], voice_get_frequency(stream->voice)); }

          if(key[KEY_1_PAD]) {
            if(key4 == 0) {
              voice_set_frequency(stream->voice, (voice_get_frequency(stream->voice)-250));
              key4 = 1;
              textprintf_centre_ex(screen, font, 160, 100, makecol(255,255,255),makecol(0,0,0),"   %d, %s, %d   ",inc, modes[mode], voice_get_frequency(stream->voice));
            }
          }
          else {
            key4 = 0;
          }
          if(key[KEY_2_PAD]) { voice_set_frequency(stream->voice, 44100); textprintf_centre_ex(screen, font, 160, 100, makecol(255,255,255),makecol(0,0,0),"   %d, %s, %d   ",inc, modes[mode], voice_get_frequency(stream->voice)); }
          if(key[KEY_3_PAD]) {
            if(key5 == 0) {
              voice_set_frequency(stream->voice, (voice_get_frequency(stream->voice)+250));
              key5 = 1;
              textprintf_centre_ex(screen, font, 160, 100, makecol(255,255,255),makecol(0,0,0),"   %d, %s, %d   ",inc, modes[mode], voice_get_frequency(stream->voice));
            }
          }
          else {
            key5 = 0;
          }

          if(done == 0) { buffer[i] = 0; pitch = 0; val = 0; }
          val += pitch;
          pitch += inc;
          if (pitch > 0x480000) pitch = 0x10000;
        }

        free_audio_stream_buffer(stream);
      }
    }
    stop_audio_stream(stream);
  }
  return(0);
} END_OF_MAIN()

int workout(int arg1, int arg2, int mode) {
  switch(mode) {
    case 0://XOr
      return arg1 ^ arg2;
      break;
    case 1://Or
      return arg1 | arg2;
      break;
    case 2://And
      return arg1 & arg2;
      break;
    case 3://Max
      return max(arg1, arg2);
      break;
    case 4://Min
      return min(arg1, arg2);
      break;
  }
  return 0xFF;//Just return full on if mode is undefined
}

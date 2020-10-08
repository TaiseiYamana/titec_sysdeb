#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Value_Slider.H>
#include <iostream>

#include "./sdk/SDL-1.2.7/include/SDL.h"
#include "./sdk/SDL_mixer-1.2.5/include/SDL_mixer.h"

using namespace std;


Mix_Chunk *chunk;

SDL_lnit(SDL_INIT_AUDIO); //SDL初期化

Mix_OpenAudio(22050,AUDIO_S16,2,4096); //SDL_Mixerオープン

chunk = Mix_LoadWAV("./wavfile/C4.wav") //効果音ファイルをロード

Mix_AllocateChannels(5);                // 同時発声数を設定



void play_chunk(){
Mix_PlayChannel( -1,chunk,0 );  
}

void print_value(Fl_Value_Slider*o, long) {
  cout << (int)o->value() << endl;
}

int main(int argc, char **argv) {
 Fl_Window *w = new Fl_Window(400, 200);
 Fl_Value_Slider* o = new Fl_Value_Slider(80, 10, 300, 25, "Volume : ");
 o->align(FL_ALIGN_LEFT);
 o->type(FL_HORIZONTAL);
 o->range(0,300);
 o->step(1);
 o->callback((Fl_Callback*)print_value);
 
 Fl_Button *button;
 button = new Fl_Button(100, 40, 150, 150, "ド");
 button->callback(play_chunk);
 button->down_box(FL_FLAT_BOX);
 button->clear_visible_focus();


 w->end();
 w->show(argc, argv);
 return Fl::run();
}

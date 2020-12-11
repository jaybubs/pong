#include <Score.h>

Score::Score() {
}
Score::~Score() {
}

void Score::display(SDL_Renderer* tRenderer) {
  text.loadFromRenderedText("test", {255,255,255}, tRenderer) ;
}

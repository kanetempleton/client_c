#include "MapEditor.h"

void renderMapEditor(ControlPanel* pan, SDL_Renderer* r) {
    SDL_Rect buttonRect = {478,424,128,32};
    SDL_Rect txtRect = {478,424,128,16};
    //SDL_RenderCopy(r,pan->longButtonTexture,NULL,&buttonRect);
    renderButton(pan->buttons[0],r);
    SDL_RenderCopy(r,pan->text[0],NULL,&txtRect);
}

#include <stdlib.h>
#include "GUI.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2_ttf/SDL_ttf.h"
#include "../net/client.h"
#include "text/KeyboardHandler.h"
#include "text/KeyboardConstants.h"

int quit = 0;

GUI * newGUI() {
    return (GUI*)malloc(sizeof(GUI));
}

void initGUI(GUI * me) {
    printf("initgui\n");
    pthread_mutex_init(&guiLock,NULL);
    me->updateString=malloc(sizeof(char)*257);
    for (int i=0; i<256; i++) {
        *(me->updateString+i)='*';
    }
    *(me->updateString+256)='\0';
    me->loginState = newLoginState();
    me->gameState = newGameState();
    me->currentState = malloc(sizeof(int));
    *(me->currentState)=0;
    yourPlayer = newPlayer();

    yourSettings = malloc(sizeof(GUISettings));
    yourSettings->mapEditMode = malloc(sizeof(int));
    *(yourSettings->mapEditMode) = 0;
    yourSettings->cursorID = malloc(sizeof(int));
    *(yourSettings->cursorID) = -1;
    yourSettings->mapSend = malloc(sizeof(int));
    *(yourSettings->mapSend) = 0;
    yourSettings->tempMapString = malloc(MAP_WIDTH*MAP_HEIGHT*3+1);
    yourSettings->holdingMouse = malloc(sizeof(int));
    *(yourSettings->holdingMouse) = 0;

    //guiSprites = newSpriteCache();
    //initializeSpriteCache(guiSprites);
    //initializeFonts();
}

void deleteGUI(GUI * me) {
    free(me->updateString);
    deleteLoginState(me->loginState);
    free(me->loginState);
    //free(me);
}


void loadGUIWindow(GUI * me) {
    SDL_Window* Main_Window; //window for the GUI to load in

    SDL_Event e; //events from hardware/os

    //initialize SDL video
    if(SDL_Init(SDL_INIT_VIDEO) < 0 )
        printf("Error initializing SDL video: %s\n",SDL_GetError());
    //initialize SDL image
    int imgFlags = IMG_INIT_PNG;
    if(!(IMG_Init(imgFlags)&imgFlags))
        printf("Error initializing SDL image: %s\n",IMG_GetError());
    // initialize SDL2_ttf
    if (TTF_Init() < 0)
        printf("Error initializing SDL2_ttf\n");

    //initialize main window and renderer
    Main_Window = SDL_CreateWindow("Multiplayer C Game : Client",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, GUI_WINDOW_WIDTH, GUI_WINDOW_HEIGHT, 0);
    Main_Renderer = SDL_CreateRenderer(Main_Window, -1, SDL_RENDERER_ACCELERATED);

    initPlayer(yourPlayer,Main_Renderer);
    initializeSpriteCache(yourPlayer->guiSprites,Main_Renderer);

    //test font open
    TTF_Font* Sans = TTF_OpenFont("data/assets/fonts/Arial.ttf",16);
    if (Sans==NULL)
        printf("YOUR FONT WAS A NULL!!!!!!!\n");

    //initiailize fonts
    SDL_Color White = {255,255,255};
    TTF_Font* Arial = TTF_OpenFont("data/assets/fonts/Arial.ttf",16);

    //initialize login state
    //LoginState* loginState = newLoginState();
    initLoginState(me->loginState,Main_Renderer);

    //main rendering loop
    int textUpdateRequired = 0;
    int tick = 0;
    int numticks = 0;
    while (!quit) {

        //render the background
        //SDL_RenderCopy(Main_Renderer, Background_Tx, NULL, NULL); //throw background texture onto canvas


        /* render the current animation step of our shape */
        //SDL_RenderCopy(Main_Renderer, BlueShapes, &SrcR, &DestR);

        //render login text
        //pthread_mutex_lock(&guiLock);
        if (*(me->currentState)==0)
            renderLoginState(me->loginState,Arial,White,textUpdateRequired);
        else if (*(me->currentState)==1) {
            if (((tick++) % 200000) == 0) {
                renderGameState(me->gameState);
                tick=0;
                numticks++;
                if (numticks%12000==0)
                    printf("num ticks: %d\n",numticks);
            }
        }
        if (textUpdateRequired>0)
            textUpdateRequired = 0;

        SDL_RenderPresent(Main_Renderer);
        SDL_PumpEvents();
        //pthread_mutex_unlock(&guiLock);

        while( SDL_PollEvent( &e ) != 0 ) {
            //SDL_PumpEvents();
            if( e.type == SDL_QUIT ) {
                printf("quit\n");
                SDL_DestroyRenderer(Main_Renderer);
                SDL_DestroyWindow(Main_Window);
                Main_Window=NULL;
                Main_Renderer=NULL;
                quit=1;
            }
            if (e.type == SDL_WINDOWEVENT) {
                if (e.window.event==SDL_WINDOWEVENT_CLOSE) {
                    printf("closed\n");
                    SDL_DestroyRenderer(Main_Renderer);
                    SDL_DestroyWindow(Main_Window);
                    Main_Window=NULL;
                    Main_Renderer=NULL;
                    quit=1;
                }
            }
            if (e.type == SDL_MOUSEMOTION) {
                //printf("mouse motion\n");
                //printf("mouse is moving\n");
                //printf("pos: (%d,%d)\n",e.motion.x,e.motion.y);
                if (*(me->currentState)==1)
                    processMouseMotion_Game(me->gameState,e.button.x,e.button.y);
            }
            if (e.type == SDL_MOUSEBUTTONDOWN) {
                printf("mouse clicked\t");
                printf("pos: (%d,%d)\n",e.button.x,e.button.y);
                *(yourSettings->holdingMouse)=1;
                if (*(me->currentState)==0)
                    processClicks_Login(me->loginState,e.button.x,e.button.y);
                else if (*(me->currentState)==1)
                    processClicks_Game(me->gameState,e.button.x,e.button.y);
            }
            if (e.type == SDL_MOUSEBUTTONUP) {
                *(yourSettings->holdingMouse)=0;
                //printf("mouse is up\n");
                //printf("pos: (%d,%d)\n",e.button.x,e.button.y);
            }
            if (e.type == SDL_MOUSEWHEEL) {
                //printf("scrollin\n");
                //printf("pos: (%d,%d)\n",e.wheel.x,e.wheel.y);
            }
            if (e.type == SDL_KEYDOWN) {
            //    printf("key down\n");
                //printf("key: (%d)\n",e.key.keysym.scancode);
                //addKey(loginState->usernameText,e.key.keysym.sym);
                if (*(me->currentState)==0)
                    textUpdateRequired = processKeys_Login(me->loginState,e.key.keysym.sym);
                else if (*(me->currentState)==1) //game state
                    processKeys_Game(me->gameState,e.key.keysym.sym);
                //textUpdateRequired = 1;
            }
            if (e.type == SDL_KEYUP) {
                //printf("key up\n");
                //printf("key: (%d)\n",e.key.keysym.scancode);
            }
        }
        SDL_Delay(5);

    }

//meh


    /* The renderer works pretty much like a big canvas:
    when you RenderCopy() you are adding paint, each time adding it
    on top.
    You can change how it blends with the stuff that
    the new data goes over.
    When your 'picture' is complete, you show it
    by using SDL_RenderPresent(). */

    /* SDL 1.2 hint: If you're stuck on the whole renderer idea coming
    from 1.2 surfaces and blitting, think of the renderer as your
    main surface, and SDL_RenderCopy() as the blit function to that main
    surface, with SDL_RenderPresent() as the old SDL_Flip() function.*/

    printf("about to destroy...\n");

    /*SDL_DestroyTexture(BlueShapes);
    SDL_DestroyTexture(Background_Tx);
    SDL_DestroyRenderer(Main_Renderer);
    SDL_DestroyWindow(Main_Window);*/
    SDL_Quit();
    printf("destroyed. goodbye\n");
    shutDownClient();
}

void quitGUI() {
    quit = 1;
}











/*
int main(int argc, char * argv[]) {

    //SDL_Surface* hello = NULL;
    //SDL_Surface* screen = NULL;

    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    //Set up screen
    //screen = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );

    //create the window
    SDL_Window * screen = SDL_CreateWindow("My Game Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_RESIZABLE); //also SDL_WINDOW_OPENGL

    //Load image
    //hello = SDL_LoadBMP( "hello.bmp" );

    //create renderer for the window
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, 0);

    //render black background
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer); //update screen by rendering current buffer

    //Apply image to screen
    //SDL_BlitSurface( hello, NULL, screen, NULL );

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");  // make the scaled rendering look smoother.
    SDL_RenderSetLogicalSize(renderer, 640, 480);

    SDL_Texture * sdlText;
    sdlText = SDL_CreateTexture(renderer,
                               SDL_PIXELFORMAT_ARGB8888,
                               SDL_TEXTUREACCESS_STATIC,
                               600, 400);
    SDL_RenderCopy(renderer,sdlText,NULL,NULL);

    //Update Screen
    //SDL_Flip( screen );

    //Pause
    //SDL_Delay( 2000 );

    //Free the loaded image
    //SDL_FreeSurface( hello );

    //Quit SDL
    int i=0;
    while (i<100000) {
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);//what the fuck lmao
        i++;
    }


    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(screen);
    SDL_Quit();

    return 0;
}*/








//

/* now onto the fun part.
This will render a rotating selection of the blue shapes
in the middle of the screen *//*
int i;
int n;
for (i = 0; i < 20; ++i) {
  for(n = 0; n < 90; ++n) {
    //SrcR.x = SrcR.x + 10;
    //SrcR.y = SrcR.y+ 10;
    //DestR.x = DestR.x + 1;
    //DestR.y = DestR.y + 1;*/

    /* render background, whereas NULL for source and destination
    rectangles just means "use the default" *//*
    SDL_RenderCopy(Main_Renderer, Background_Tx, NULL, NULL); *///throw background texture onto canvas

    /* render the current animation step of our shape */
    /*SDL_RenderCopy(Main_Renderer, BlueShapes, &SrcR, &DestR);
    SDL_RenderPresent(Main_Renderer);
    SDL_PumpEvents();*/ //this fuckin line is important bruh

    /*while( SDL_PollEvent( &e ) != 0 ) {
        if( e.type == SDL_QUIT ) {
            exit(0);
        }
    }
    //SDL_Delay(500);
  }
}

*/

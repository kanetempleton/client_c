#include <stdio.h>
#include "net/client.h"
#include "gfx/GUI.h"
#include <pthread.h>
#include <stdlib.h>
#include "net/communication/HandleReplies.h"
#include <string.h>
#include <unistd.h>

int chode = 0;

int main(int argc, char *argv[]) {

    /*char buf[10];
    sprintf(buf,"%d",getpid());
    system("renice -n 20 -p 7314");*/

    int dontusethegui = 0;
    if (argc>1)
        dontusethegui = strtol(argv[1],NULL,10);

    Client * mainClient = newClient();
    //GUI * gui = newGUI();
    mainGUI = newGUI();
    //if (dontusethegui == 1)
        //deleteGUI(gui);

    //startClient((void*)client);a
    if (dontusethegui == 0)
        initGUI(mainGUI);
    //startGUI(gui);
    pthread_t clientThread;
    //pthread_t guiThread; nvm we dont need this

    ReplyHandler* rh = newReplyHandler();
    initReplyHandler(rh,mainGUI);
    initClient(mainClient,rh,0);

    int rc1 = pthread_create(&clientThread,NULL,&startClient,(void*)mainClient);
    void * rval1;
    if (!dontusethegui)
        loadGUIWindow(mainGUI);
    rc1 = pthread_join(clientThread, &rval1);
    //exit(0);
    /*
    int rc2 = pthread_create(&clientThread,NULL,&startClient,(void*)client);
    void * rval2;
    rc2 = pthread_join(clientThread, &rval2);*/
    //loadGUIWindow();



    return 0;
}

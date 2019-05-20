#ifndef H_CONTROL
#define H_CONTROL
typedef struct {
    GUI * gui;
    Client * client;
} Control;
Control* createControl();
void initControl(Control* ctrl);
void deleteControl(Control* ctrl);
#endif

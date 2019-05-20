#include "KeyboardHandler.h"
#include "KeyboardConstants.h"
#include "SDL2/SDL.h"
#include <stdlib.h>

TextInput * newTextInputField() {
    return (TextInput*) malloc(sizeof(TextInput));
}

void initTextInputField(TextInput* field, int size) {
    field->maxLength = malloc(sizeof(int));
    field->end = malloc(sizeof(int));
    field->build = malloc(sizeof(char)*size+1);
    *(field->maxLength) = size;
    *(field->end) = 0;
    *(field->build) = '\0';
}

void deleteTextInputField(TextInput* field) {
    free(field->maxLength);
    free(field->end);
    free(field->build);
    free(field);
}

int addKey(TextInput* field, int keyid) {
    char addMe;
    int add = 1;
    int rv = 1;
    switch (keyid) {
        case SDLK_DELETE:
        case SDLK_BACKSPACE:
            if (*(field->end)>0)
                delKey(field,1);
            add=0;
            break;
        case SDLK_TAB:
            rv=2;
            add=0;
            break;
        default:
            add=1;
            addMe=getCharForCode(keyid);
            if (*(field->end) >= *(field->maxLength))
                add=0;
            break;
    }
    if (add) { //append char to text field
        *(field->build+*(field->end)) = addMe;
        *(field->end)=*(field->end)+1;
        *(field->build+*(field->end)) = '\0';
    }
    return rv;
}

void delKey(TextInput* field, int numKeys) {
    if (*(field->end) == 0)
        return;
    *(field->build+*(field->end)) = ' ';
    *(field->end)=*(field->end)-1;
    *(field->build+*(field->end)) = '\0';
}

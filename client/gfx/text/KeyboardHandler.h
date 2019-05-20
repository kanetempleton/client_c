#ifndef H_KEYBOARDHANDLER
#define H_KEYBOARDHANDLER
typedef struct {
    char * build;
    int * maxLength;
    int * end;
} TextInput;
TextInput * newTextInputField();
void initTextInputField(TextInput* field, int size);
void deleteTextInputField(TextInput* field);
int addKey(TextInput* field, int keyid);
void delKey(TextInput* field, int numKeys);
#endif

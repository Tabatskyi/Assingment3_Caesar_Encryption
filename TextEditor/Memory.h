#pragma once
#include "RevertableCommand.h"
#include "Coursor.h"

class Memory
{
public:
    Memory(unsigned int lines, unsigned int length, unsigned int commandsMemorySize);
    ~Memory();

    int initializeMemory();
    int initializeCommandsMemory();
    void printCommands();
    void freeMemory();
    int resizeLines();
    int resizeLength();
    void saveCommand(RevertableCommand* command);
    void print();
    void find(char* text);
    void createClipboard(unsigned int size);
    void deleteClipboard();

    unsigned int currentLine, currentLinesNum, currentLengthNum, commandsMemorySize, undoStep;

    char** textMemory;
    char* clipboard;
    RevertableCommand** commandsMemory;
    Coursor coursor;
};

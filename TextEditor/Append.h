#pragma once
#include "Memory.h"

class Append : public RevertableCommand
{
public:
    Append(unsigned int currentLine, char* input);

    void Do(Memory* memory);
    void Undo(Memory* memory);
private:
    int line;
    char* text;
};



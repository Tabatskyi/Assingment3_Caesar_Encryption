#pragma once
#include "Memory.h"

class NewLine : public RevertableCommand
{
public:
    NewLine(unsigned int currentLine);
    ~NewLine();

    void Do(Memory* memory);
    void Undo(Memory* memory);
private:
    int line;
};




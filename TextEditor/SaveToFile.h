#pragma once
#include "Memory.h"


class SaveToFile : Command
{
public:
    SaveToFile(char* filename);
    ~SaveToFile();

    void Do(Memory* memory);
private:
    FILE* file;
    char* filename;
};





#pragma once
#include "Memory.h"

class LoadFromFile : Command
{
public:
    LoadFromFile(char* filename);
    ~LoadFromFile();

    void Do(Memory* memory);
private:
    char* filename;
};
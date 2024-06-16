#include "LoadFromFile.h"


LoadFromFile::LoadFromFile(char* filename)
{
    this->filename = filename;
}

LoadFromFile::~LoadFromFile()
{
    delete[] filename;
}

void LoadFromFile::Do(Memory* memory)
{
    char* text = new char[memory->currentLengthNum];
    FILE* file = fopen(filename, "r");

    if (file != NULL)
    {
        memory->currentLine = 0;
        while (fgets(text, memory->currentLengthNum, file) != NULL)
        {
            if (memory->currentLine + 1 >= memory->currentLinesNum)
            {
                memory->resizeLines();
            }
            text[strlen(text) - 1] = 0;
            strcpy(memory->textMemory[memory->currentLine], text);
            memory->currentLine++;
        }
        fclose(file);
        memory->currentLine--;
        printf(">Load successful\n");
        memory->coursor.SetPosition(memory->currentLine, strlen(memory->textMemory[memory->currentLine]));
    }
    else
    {
        perror(">Error opening file\n");
    }
}

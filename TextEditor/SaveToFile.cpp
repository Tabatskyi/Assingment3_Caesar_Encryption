#include "SaveToFile.h"

SaveToFile::SaveToFile(char* filename)
{
    this->filename = filename;
}

SaveToFile::~SaveToFile()
{
    free(file);
}

void SaveToFile::Do(Memory* memory)
{
    file = fopen(filename, "w");
    if (file != NULL)
    {
        for (int i = 0; i <= memory->currentLine; i++)
        {
            fprintf(file, "%s\n", memory->textMemory[i]);
        }
        fclose(file);
        std::cout << ">Save successful\n";
    }
    else
    {
        std::cout << ">Error opening file\n";
    }
}
#include "Append.h"

Append::Append(unsigned int currentLine, char* input)
{
    text = input;
    line = currentLine;
}

void Append::Do(Memory* memory)
{
    if (strlen(memory->textMemory[line]) + strlen(text) < memory->currentLengthNum)
    {
        strcat(memory->textMemory[line], text);
    }
    else
    {
        memory->resizeLength();
        strcat(memory->textMemory[line], text);
    }
    memory->coursor.SetPosition(memory->currentLine, strlen(memory->textMemory[memory->currentLine]));
}

void Append::Undo(Memory* memory)
{
	memory->textMemory[line][strlen(memory->textMemory[line]) - strlen(text)] = '\0';
    memory->coursor.SetPosition(memory->currentLine, strlen(memory->textMemory[memory->currentLine]));
}
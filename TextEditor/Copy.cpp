#include "Copy.h"


Copy::Copy(unsigned int line, unsigned int index, unsigned int symbolsCount)
{
    this->line = line;
    this->index = index;
    count = symbolsCount;
    copiedText = new char[count];
}

Copy::~Copy()
{
	delete[] copiedText;
}

void Copy::Do(Memory* memory)
{
    char* lineText = memory->textMemory[line];
    unsigned int lineLength = strlen(lineText);

    if (index + count > lineLength)
        count = lineLength - index;

    strncpy(copiedText, lineText + index, count);
    copiedText[count] = '\0';

    memory->createClipboard(strlen(copiedText));

    strcpy(memory->clipboard, copiedText);
}
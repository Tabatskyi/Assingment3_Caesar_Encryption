#include "Delete.h"
#include "Insert.h"


Delete::Delete(unsigned int line, unsigned int index, unsigned int symbolsCount)
{
	this->line = line;
	this->index = index;
	count = symbolsCount;
	deletedText = new char[count];
}

Delete::~Delete() 
{
    delete[] deletedText;
}

void Delete::Do(Memory* memory)
{
    char* lineText = memory->textMemory[line];
    unsigned int lineLength = strlen(lineText);

    if (index + count > lineLength) 
        count = lineLength - index; 

    strncpy(deletedText, lineText + index, count);
    deletedText[count] = '\0';  

    memmove(lineText + index, lineText + index + count, lineLength - index - count + 1); 
}

void Delete::Undo(Memory* memory)
{
    Insert* insert = new Insert(line, index, deletedText);
    insert->Do(memory);
}

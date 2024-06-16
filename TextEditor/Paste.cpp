#include "Paste.h"
#include "Insert.h"
#include "Delete.h"


Paste::Paste(int line, int column)
{
    this->line = line;
    index = column;
}

Paste::~Paste()
{
    delete[] text;
}

void Paste::Do(Memory* memory) 
{
    text = new char[strlen(memory->clipboard) + 1];
    strcpy(text, memory->clipboard);

    if (index >= strlen(memory->textMemory[line]))
        index = strlen(memory->textMemory[line]);

	Insert* insert = new Insert(line, index, text);
    insert->Do(memory);
    memory->coursor.SetPosition(line, index + strlen(text));
}

void Paste::Undo(Memory* memory)
{
	Delete* deleteCommand = new Delete(line, index, strlen(text));
	deleteCommand->Do(memory);
    memory->coursor.SetPosition(line, index);
}
#include "Cut.h"
#include "Delete.h"
#include "Insert.h"


Cut::Cut(unsigned int line, unsigned int index, unsigned int count)
{
	this->line = line;
	this->index = index;
	this->count = count;
	this->cuttedText = new char[count];
}

Cut::~Cut()
{
	delete[] cuttedText;
}

void Cut::Do(Memory* memory) 
{
	Delete* deleteCommand = new Delete(line, index, count);
	deleteCommand->Do(memory);

	memory->createClipboard(count);
	strcpy(cuttedText, deleteCommand->deletedText);
	cuttedText[count] = '\0';
	strcpy(memory->clipboard, cuttedText);
}

void Cut::Undo(Memory* memory)
{
	Insert* insert = new Insert(line, index, cuttedText);
	insert->Do(memory);
}
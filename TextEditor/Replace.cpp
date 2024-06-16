#include "Replace.h"
#include "Delete.h"
#include "Insert.h"

Replace::Replace(unsigned int line, unsigned int index, char* textToInsert)
{
	this->line = line;
	this->index = index;
	this->textToInsert = textToInsert;
	count = strlen(textToInsert);
	replacedText = new char(count);
}

Replace::~Replace()
{
	delete[] textToInsert;
	delete[] replacedText;
}

void Replace::Do(Memory* memory) 
{
	Delete* deleteCommand = new Delete(line, index, count);
	deleteCommand->Do(memory);
	strcpy(replacedText, deleteCommand->deletedText);

	Insert* insert = new Insert(line, index, textToInsert);
	insert->Do(memory);
	memory->coursor.SetPosition(line, index + count);
}

void Replace::Undo(Memory* memory)
{
	Delete* deleteCommand = new Delete(line, index, count);
	deleteCommand->Do(memory);

	Insert* insert = new Insert(line, index, replacedText);
	insert->Do(memory);
	memory->coursor.SetPosition(line, index);
}
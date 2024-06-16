#pragma once
#include "Memory.h"
class Replace : public RevertableCommand
{
public:
	Replace(unsigned int line, unsigned int index, char* textToInsert);
	~Replace();

	void Do(Memory* memory);
	void Undo(Memory* memory);
private:
	unsigned int line, index, count;
	char* replacedText;
	char* textToInsert;
};


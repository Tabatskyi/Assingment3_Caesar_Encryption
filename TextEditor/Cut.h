#pragma once
#include "Memory.h"
class Cut : public RevertableCommand
{
public:
	Cut(unsigned int line, unsigned int index, unsigned int count);
	~Cut();

	void Do(Memory* memory);
	void Undo(Memory* memory);
private:
	unsigned int line, index, count;
	char* cuttedText;
};


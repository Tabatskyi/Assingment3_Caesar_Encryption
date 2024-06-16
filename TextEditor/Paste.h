#pragma once
#include "Memory.h"
class Paste : public RevertableCommand
{
public:
	Paste(int line, int column);
	~Paste();

	void Do(Memory* memory);
	void Undo(Memory* memory);
private:
	unsigned int line, index;
	char* text;
};


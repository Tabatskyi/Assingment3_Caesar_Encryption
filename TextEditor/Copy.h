#pragma once
#include "Memory.h"
class Copy : public Command
{
public:
	Copy(unsigned int line, unsigned int index, unsigned int symbolsCount);
	~Copy();

	void Do(Memory* memory);
private:
	unsigned int line, index, count;
	char* copiedText;
};


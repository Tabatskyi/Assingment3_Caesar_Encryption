#include "NewLine.h"

NewLine::NewLine(unsigned int currentLine)
{
    line = currentLine + 1;
}

NewLine::~NewLine() = default;

void NewLine::Do(Memory* memory)
{
    if (line >= memory->currentLinesNum)
        memory->resizeLines();

    memory->currentLine = line;
    memory->coursor.SetPosition(memory->currentLine, 0);
}

void NewLine::Undo(Memory* memory)
{
	memory->currentLine = line - 1;
	memory->currentLinesNum--;
    memory->coursor.SetPosition(memory->currentLine, 0);
}
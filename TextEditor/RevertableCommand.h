#pragma once

#include "Command.h"

class Memory;

class RevertableCommand : public Command
{
public:
    virtual ~RevertableCommand() = default;

    virtual void Do(Memory* memory) = 0;
    virtual void Undo(Memory* memory) = 0;
};
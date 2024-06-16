#include "Memory.h"

Memory::Memory(unsigned int lines, unsigned int length, unsigned int commandsMemorySize)
{
    undoStep = 0;
    currentLine = 0;
    currentLinesNum = lines;
    currentLengthNum = length;
    this->commandsMemorySize = commandsMemorySize;
 
    initializeMemory();
    initializeCommandsMemory();
}

Memory::~Memory()
{
	freeMemory();
}

void Memory::freeMemory()
{
    for (unsigned int i = 0; i < currentLinesNum; i++)
    {
        delete textMemory[i];
    }
    delete textMemory;
    delete commandsMemory;
    delete clipboard;
}


int Memory::initializeMemory()
{
    textMemory = new char* [currentLengthNum];

    if (!textMemory)
    {
        perror(">Memory allocation failed.\n");
        return 1;
    }

    for (unsigned int i = 0; i < currentLengthNum; i++)
    {
        textMemory[i] = new char[currentLengthNum];
        textMemory[i][0] = '\0';
    }

    return 0;
}


int Memory::initializeCommandsMemory()
{
    commandsMemory = new RevertableCommand* [commandsMemorySize];

    if (!commandsMemory)
    {
        perror(">Memory allocation failed.\n");
        return 1;
    }

    for (unsigned int i = 0; i < commandsMemorySize; i++)
    {
        commandsMemory[i] = nullptr;
    }

    return 0; 
}


int Memory::resizeLines() 
{
    unsigned int newLinesNum = currentLinesNum * 2;
    char** newMemory = new char*[newLinesNum];
    memcpy(newMemory, textMemory, newLinesNum * sizeof(char*));

    if (!newMemory)
    {
        perror("Memory reallocation failed");
        return 1;
    }

    for (unsigned int i = currentLinesNum; i < newLinesNum; i++)
    {
        newMemory[i] = new char[currentLengthNum];
        if (!newMemory[i]) 
        {
            perror("Memory allocation failed for new lines");
            return 1;
        }
        newMemory[i][0] = '\0';
    }

    currentLinesNum = newLinesNum;
    textMemory = newMemory;
    return 0;
}


int Memory::resizeLength() 
{
    unsigned int newLengthNum = currentLengthNum * 2;
    for (unsigned int i = 0; i < currentLinesNum; i++)
    {
        char* newLine = new char[newLengthNum];

        strcpy(newLine, textMemory[i]);
        if (!newLine)
        {
            perror("Memory reallocation failed for line resizing");
            return 1;
        }
        textMemory[i] = new char[newLengthNum];
        strcpy(textMemory[i], newLine);
        delete[] newLine;
    }

    currentLengthNum = newLengthNum;
    return 0;
}

void Memory::print()
{
	for (unsigned int i = 0; i <= currentLine; i++)
	{
		printf("%d: %s\n", i, textMemory[i]);
	}
}

void Memory::find(char* text) 
{
    unsigned int position;
    bool found;

    found = false;
    for (unsigned int i = 0; i <= currentLine; i++)
    {
        char* result = strstr(textMemory[i], text);

        position = result - textMemory[i];
        while (result != NULL)
        {
            position = result - textMemory[i];
            printf(">Found occurrence at %u %u\n", i, position);
            found = true;

            result = strstr(result + strlen(text), text);
        }
    }
    if (!found)
    {
        printf(">No occurrence found\n");
    }
}

void Memory::printCommands() 
{
    std::cout << "Current commands in memory:" << std::endl;
    for (unsigned int i = 0; i < commandsMemorySize; i++) 
    {
        if (commandsMemory[i] != nullptr) 
           std::cout << i << ": Command at " << commandsMemory[i] << std::endl;
        else 
           std::cout << i << ": [Empty]" << std::endl;
    }
}

void Memory::saveCommand(RevertableCommand* command)
{
    if (undoStep > 0)
    {
        for (int i = commandsMemorySize - undoStep; i >= 0; i--)
        {
            commandsMemory[i + undoStep] = commandsMemory[i];
        }
        for (int i = 0; i < undoStep; i++)
		{
			commandsMemory[i] = nullptr;
		}
    }
    undoStep = 0;

    delete[] commandsMemory[0];

    for (unsigned int i = 1; i < commandsMemorySize; i++)
    {
        commandsMemory[i - 1] = commandsMemory[i];

    }
    commandsMemory[commandsMemorySize - 1] = command;
}


void Memory::createClipboard(unsigned int size) 
{
    clipboard = new char[size];
}

void Memory::deleteClipboard() 
{
	delete clipboard;
}
#include "Memory.h"
#include "Append.h"
#include "NewLine.h"
#include "SaveToFile.h"
#include "LoadFromFile.h"
#include "Insert.h"
#include "Delete.h"
#include "Copy.h"
#include "Cut.h"
#include "Paste.h"
#include "Replace.h"
#include "Coursor.h"


static bool validatePosition(unsigned int line, unsigned int index, Memory* memory)
{
	if (line >= memory->currentLinesNum || index >= memory->currentLengthNum)
	{
		printf("Error: Index out of range");
		return false;
	}
	return true;
}


int main()
{
    char command;
    Memory* memory = new Memory(128, 256, 3);

    do
    {
        printf(">");
        (void)scanf(" %c", &command);

        if (command == 'a')
        {
            char* inputBuffer = (char*)malloc(memory->currentLengthNum * sizeof(char));
            printf(">Enter text to append: ");
            (void)scanf(" %[^\n]s", inputBuffer);
            Append* append = new Append(memory->currentLine, inputBuffer);
            append->Do(memory);
            memory->saveCommand(append);
        }
        else if (command == 'n')
        {
            printf(">New line started\n");
            NewLine* newLine = new NewLine(memory->currentLine);
            newLine->Do(memory);
            memory->saveCommand(newLine);
        }
        else if (command == 's')
        {
            char filename[100];
            printf(">Enter filename for saving: ");
            (void)scanf(" %s", filename);
            SaveToFile* saveToFile = new SaveToFile(filename);
            saveToFile->Do(memory);
        }
        else if (command == 'l')
        {
            char filename[100];
            printf(">Enter filename for loading: ");
            (void)scanf(" %s", filename);
            LoadFromFile* loadFromFile = new LoadFromFile(filename);
            loadFromFile->Do(memory);
        }
        else if (command == 'p')
        {
            unsigned int x, y;
            memory->coursor.GetPosition(x, y);
            Insert* showCoursor = new Insert(x, y, "|");
            showCoursor->Do(memory);
            memory->print();
            showCoursor->Undo(memory);
        }
        else if (command == 'i')
        {
            char* inputBuffer = new char[memory->currentLengthNum];
            unsigned int line, index;

            memory->coursor.GetPosition(line, index);

            printf(">Enter text to insert: ");
            (void)scanf(" %[^\n]", inputBuffer);

            Insert* insert = new Insert(line, index, inputBuffer);
            insert->Do(memory);
            memory->saveCommand(insert);
        }
        else if (command == 'f')
        {
            char* inputBuffer = new char[memory->currentLengthNum];
            printf(">Enter text to search: ");
            (void)scanf(" %[^\n]", inputBuffer);

            memory->find(inputBuffer);
        }
        else if (command == 'd')
        {
            unsigned int line, index, symbolsCount;

            memory->coursor.GetPosition(line, index);

            printf(">Choose symbols count to delete: ");
            (void)scanf("%u", &symbolsCount);
            
            Delete* deleteCommand = new Delete(line, index, symbolsCount);
            deleteCommand->Do(memory);
            memory->saveCommand(deleteCommand);
        }
        else if (command == 'u')
        {
            unsigned int size = memory->commandsMemorySize;
            memory->undoStep++;

            if (memory->undoStep >= size or memory->commandsMemory[size - memory->undoStep] == nullptr)
            {
				printf(">No more commands to undo\n");
				continue;
			}
            memory->commandsMemory[size - memory->undoStep]->Undo(memory);
        }
        else if (command == 'z')
        {
            unsigned int size = memory->commandsMemorySize;
            if (memory->undoStep == 0)
			{
				printf(">No more commands to redo\n");
				continue;
			}
            memory->commandsMemory[size - memory->undoStep]->Do(memory);
            memory->undoStep--;
        }
        else if (command == 'x')
        {
            unsigned int line, index, symbolsCount;

            memory->coursor.GetPosition(line, index);

            printf(">Choose symbols count to cut: ");
            (void)scanf("%u", &symbolsCount);
            
            Cut* cut = new Cut(line, index, symbolsCount);
            cut->Do(memory);
            memory->saveCommand(cut);
        }
        else if (command == 'c')
        {
            unsigned int line, index, symbolsCount;

            memory->coursor.GetPosition(line, index);

            printf(">Choose symbols count to copy: ");
            (void)scanf("%u", &symbolsCount);

            Copy* copy = new Copy(line, index, symbolsCount);
            copy->Do(memory);
        }
        else if (command == 'v')
        {
            unsigned int line, index;

            memory->coursor.GetPosition(line, index);

            Paste* paste = new Paste(line, index);
            paste->Do(memory);
            memory->saveCommand(paste);
        }
		else if (command == 'r')
		{
            char* inputBuffer = new char[memory->currentLengthNum];
            unsigned int line, index;

            memory->coursor.GetPosition(line, index);

            printf(">Enter replacement text: ");
            (void)scanf(" %[^\n]", inputBuffer);

            Replace* replace = new Replace(line, index, inputBuffer);
            replace->Do(memory);
            memory->saveCommand(replace);
		}
        else if (command == 'e')
        {
            memory->freeMemory();
            memory->currentLine = 0;

            printf(">Memory erased\n");
            
            memory->initializeMemory();
        }
        else if (command == 'q')
        {
            printf(">Goodbye!\n");
        }
        else if (command == 'm')
        {
            char direction;
            printf(">Enter direction (a=left, d=right, w=up, s=down): ");
            (void)scanf(" %c", &direction);

            unsigned int x, y;
            memory->coursor.GetPosition(x, y);

            switch (direction)
            {
            case 'a': // left
                if (y > 0) 
                    memory->coursor.SetPosition(x, y - 1);
                break;
            case 'd': // right
                if (y < memory->currentLengthNum - 1) 
                    memory->coursor.SetPosition(x, y + 1);
                break;
            case 'w': // up
                if (x > 0) 
                    memory->coursor.SetPosition(x - 1, y);
                break;
            case 's': // down
                if (x < memory->currentLinesNum - 1) 
                    memory->coursor.SetPosition(x + 1, y);
                break;
            default:
                printf(">Invalid direction\n");
            }
        }
        else 
            printf(">unknown command\n");

    } while (command != 'q');

    delete memory;

    return 0;
} 
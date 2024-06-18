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
#include <Windows.h>

using namespace std;

static bool validatePosition(unsigned int line, unsigned int index, Memory* memory)
{
	if (line >= memory->currentLinesNum || index >= memory->currentLengthNum)
	{
		cout << "Error: Index out of rang\n";
		return false;
	}
	return true;
}

static char* shiftChars(char* text, int shift)
{
    typedef char*(*shiftChar_ptr_t)(char*, int);

    HINSTANCE handle = LoadLibrary(TEXT("CaesarCifer.dll"));
    if (handle == nullptr || handle == INVALID_HANDLE_VALUE)
    {
        cout << "DLL not found\n";
        return nullptr;
    }

    shiftChar_ptr_t shiftChar_ptr = (shiftChar_ptr_t)GetProcAddress(handle, "shiftChars");
    if (shiftChar_ptr == nullptr)
    {
        cout << "Function not found\n";
        return nullptr;
    }

    char* newText = shiftChar_ptr(text, shift);

    FreeLibrary(handle);

    return newText;
}


int main()
{
    char command;
    Memory* memory = new Memory(128, 256, 3);

    do
    {
        cout << ">";
        cin >> command;

        if (command == 'a')
        {
            char* inputBuffer = (char*)malloc(memory->currentLengthNum * sizeof(char));
            cout << ">Enter text to append: ";
            cin.ignore();
            cin.getline(inputBuffer, memory->currentLengthNum);
            Append* append = new Append(memory->currentLine, inputBuffer);
            append->Do(memory);
            memory->saveCommand(append);
        }
        else if (command == 'n')
        {
            cout << ">New line started\n";
            NewLine* newLine = new NewLine(memory->currentLine);
            newLine->Do(memory);
            memory->saveCommand(newLine);
        }
        else if (command == 's')
        {
            char filename[100];
            cout << ">Enter filename for saving: ";
            cin >> filename;
            SaveToFile* saveToFile = new SaveToFile(filename);
            saveToFile->Do(memory);
        }
        else if (command == 'l')
        {
            char filename[100];
            cout << ">Enter filename for loading: ";
            cin >> filename;
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

            cout << ">Enter text to insert: ";
            cin.ignore();
            cin.getline(inputBuffer, memory->currentLengthNum);

            Insert* insert = new Insert(line, index, inputBuffer);
            insert->Do(memory);
            memory->saveCommand(insert);
        }
        else if (command == 'f')
        {
            char* inputBuffer = new char[memory->currentLengthNum];
            cout << ">Enter text to search: ";
            cin.ignore();
            cin.getline(inputBuffer, memory->currentLengthNum);

            memory->find(inputBuffer);
        }
        else if (command == 'd')
        {
            unsigned int line, index, symbolsCount;

            memory->coursor.GetPosition(line, index);

            cout << ">Choose symbols count to delete: ";
            cin >> symbolsCount;
                    
            Delete* deleteCommand = new Delete(line, index, symbolsCount);
            deleteCommand->Do(memory);
            memory->saveCommand(deleteCommand);
        }
        else if (command == 'u')
        {
            unsigned int size = memory->commandsMemorySize;
            memory->undoStep++;

            if (memory->undoStep >= size || memory->commandsMemory[size - memory->undoStep] == nullptr)
            {
				cout << ">No more commands to undo\n";
				continue;
			}
            memory->commandsMemory[size - memory->undoStep]->Undo(memory);
        }
        else if (command == 'z')
        {
            unsigned int size = memory->commandsMemorySize;
            if (memory->undoStep == 0)
			{
				cout << ">No more commands to redo\n";
				continue;
			}
            memory->commandsMemory[size - memory->undoStep]->Do(memory);
            memory->undoStep--;
        }
        else if (command == 'x')
        {
            unsigned int line, index, symbolsCount;

            memory->coursor.GetPosition(line, index);

            cout << ">Choose symbols count to cut: ";
            cin >> symbolsCount;
                    
            Cut* cut = new Cut(line, index, symbolsCount);
            cut->Do(memory);
            memory->saveCommand(cut);
        }
        else if (command == 'c')
        {
            unsigned int line, index, symbolsCount;

            memory->coursor.GetPosition(line, index);

            cout << ">Choose symbols count to copy: ";
            cin >> symbolsCount;

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

            cout << ">Enter replacement text: ";
            cin.ignore();
            cin.getline(inputBuffer, memory->currentLengthNum);

            Replace* replace = new Replace(line, index, inputBuffer);
            replace->Do(memory);
            memory->saveCommand(replace);
		}
        else if (command == 'e')
        {
            memory->freeMemory();
            memory->currentLine = 0;

            cout << ">Memory erased\n";
                    
            memory->initializeMemory();
        }
        else if (command == 'q')
        {
            cout << ">Goodbye!\n";
        }
        else if (command == 'm')
        {
            char direction;
            cout << ">Enter direction (a=left, d=right, w=up, s=down): ";
            cin >> direction;

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
                cout << ">Invalid direction\n";
            }
        }
        else if (command == 'j')
		{
			unsigned int x, y;
			cout << ">Enter position (x y): ";
			cin >> x >> y;

			if (validatePosition(x, y, memory))
				memory->coursor.SetPosition(x, y);
		}
        else if (command == '/')
        {
            int shift;
            cout << ">Enter shift amount to encode: ";
            cin >> shift;

            if (shift > 26)
                shift %= 26;

            for (int i = 0; i <= memory->currentLine; i++)
            {
                char* newLine = shiftChars(memory->textMemory[i], shift);
                memory->textMemory[i] = newLine;
            }
		}
        else if (command == '\\')
        {
            int shift;
            cout << ">Enter shift amount to decode: ";
            cin >> shift;

            if (shift > 26)
				shift %= 26;

            for (int i = 0; i <= memory->currentLine; i++)
            {
                char* newLine = shiftChars(memory->textMemory[i], -shift);
                memory->textMemory[i] = newLine;
            }
								}
        else 
            cout << ">unknown command\n";

    } while (command != 'q');

    delete memory;

    return 0;
}
#include <iostream>

extern "C"
{
	__declspec(dllexport) char* shiftChars(char* text, float shift)
    {
        for (int i = 0; text[i] != '\0'; i++)
        {
            int shiftedChar = (int)text[i];
            if ((shiftedChar >= 'a' && shiftedChar <= 'z') || (shiftedChar >= 'A' && shiftedChar <= 'Z'))
            {
                shiftedChar = shiftedChar + shift;
                if ((shiftedChar > 'Z' && shiftedChar < 'a' && (int)text[i] < 'a') || shiftedChar > 'z')
                {
                    shiftedChar -= 26 * abs(round(shift / 26));
                }
                else if ((shiftedChar > 'Z' && shiftedChar < 'a' && (int)text[i] >= 'a') || shiftedChar < 'A')
                {
                    shiftedChar += 26 * abs(round(shift / 26));
                }
                text[i] = (char)shiftedChar;
            }
        }
        return text;
    }
};
extern "C"
{
	__declspec(dllexport) char* shiftChars(char* text, int shift)
	{
		for (int i = 0; text[i] != '\0'; i++)
		{
			int shiftedChar = (int)text[i];
			if ((shiftedChar >= 'a' && shiftedChar <= 'z') || (shiftedChar >= 'A' && shiftedChar <= 'Z'))
			{
				shiftedChar = shiftedChar + shift;
				if ((shiftedChar > 'z' && shiftedChar < 'A') || shiftedChar > 'Z')
				{
					shiftedChar = shiftedChar - 26;
				}
				else if ((shiftedChar < 'a' && shiftedChar > 'Z') || shiftedChar < 'A')
				{
					shiftedChar = shiftedChar + 26;
				}
				text[i] = (char)shiftedChar;
			}
		}
		return text;
	}
};
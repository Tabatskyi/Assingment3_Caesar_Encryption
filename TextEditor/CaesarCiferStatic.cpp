char* shiftChars(char* text, int shift)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        int shiftedChar = (int)text[i];
        if ((shiftedChar >= 'a' && shiftedChar <= 'z') || (shiftedChar >= 'A' && shiftedChar <= 'Z'))
        {
            shiftedChar += shift;

            if ((shiftedChar > 'Z' && text[i] < 'a') || shiftedChar > 'z')
            {
                shiftedChar -= 26;
            }
            else if ((shiftedChar < 'a' && text[i] >= 'a') || shiftedChar < 'A')
            {
                shiftedChar += 26;
            }
            text[i] = (char)shiftedChar;
        }
    }
    return text;
}
;
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#pragma once

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <iostream>

class Command
{
public:
    virtual ~Command() = default;
};
#include "Coursor.h"


Coursor::Coursor()
{
	x = 0;
	y = 0;
}

Coursor::~Coursor() = default;

void Coursor::SetPosition(unsigned int x, unsigned int y)
{
	this->x = x;
	this->y = y;
}

void Coursor::GetPosition(unsigned int &x, unsigned int &y)
{
	x = this->x;
	y = this->y;
}
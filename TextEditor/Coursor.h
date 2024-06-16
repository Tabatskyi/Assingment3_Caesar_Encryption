#pragma once
class Coursor
{
public:
	Coursor();
	~Coursor();
	void SetPosition(unsigned int x, unsigned int y);
	void GetPosition(unsigned int &x, unsigned int &y);
private:
	int x;
	int y;
};
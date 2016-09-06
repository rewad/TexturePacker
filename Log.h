#pragma once
#include <iostream>
class Log
{
public: 
	static Log *GetInstance();

	void Message(const char *message);
	void Warning(const char *message);
	void Error(const char *message);

private:
	void CreateLog();
	FILE *p_file;
	static Log *p_instance;
};


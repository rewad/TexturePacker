#include "Log.h"

Log *Log::p_instance = nullptr;

Log *Log::GetInstance()
{
	if (p_instance == nullptr)
	{
		p_instance = new Log();
		p_instance->CreateLog();
	}
	return p_instance;
}

void Log::Message(const char *message)
{
	fprintf(p_file, "%s\n", message);
}

void Log::Warning(const char *message)
{
	fprintf(p_file, "WARNING: %s\n", message);
}

void Log::Error(const char *message)
{ 
	fprintf(p_file, "ERROR: %s\n", message);
	fclose(p_file);
	exit(1);
}

void Log::CreateLog()
{
	if (p_file != NULL) return;
	p_file = fopen("log.txt", "w+");
}

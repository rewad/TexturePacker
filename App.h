#pragma once
#include "Log.h" 
#include <string>

#define MESSAGE(X) Log::GetInstance()->Message((X));
#define WARNING(X) Log::GetInstance()->Warning((X));
#define ERROR(X) Log::GetInstance()->Error((X));



#define SAFE_DELETE(X) if((X)) {delete (X);(X)=nullptr;}

#define byte unsigned char
#define uint32 unsigned int
#define int32 signed int
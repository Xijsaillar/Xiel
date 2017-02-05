#include "XEngine.h"

int main()
{
	try
	{
		XEngine::GetInstance().Go();
	}
	catch (char* e)
	{
		throw e;
	}
	return 0;
}
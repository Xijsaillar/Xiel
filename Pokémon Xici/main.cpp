#include "XEngine.h"

// Project -> System -> Subsystem
//int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
int main()
{
	try
	{
		XEngine::GetInstance().Go();
	}
	catch (char* e)
	{
		//MessageBoxA(NULL, e, "Exception Occured", MB_OK | MB_ICONERROR);
	}
}
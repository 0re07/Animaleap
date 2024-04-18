#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <DxLib.h>
#include "Application.h"

#ifdef DEBUG
#define new new(_NORMAL_BLOCK,_FILE_,_LINE_);
#endif // DEBUG

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	// ÉÅÉÇÉäÉäÅ[ÉNåüèo
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	auto& application = Application::GetInstance();

	if (!application.Init())
	{
		return -1;
	}
	application.Run();
	application.Destroy();

	return 0;
}
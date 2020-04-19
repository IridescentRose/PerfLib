#include <perflib.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <malloc.h>
#include <stdio.h>

PSP_MODULE_INFO("MELIB TEST", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_VFPU | THREAD_ATTR_USER);
PSP_HEAP_SIZE_KB(-1024);

int main(int argc, char* argv[])
{
	pspDebugScreenInit();

	PFL_Init(false);
	PFL_SetTargetFrameRate(60);

	int myInt = 0;

	while (1)
	{
		PFL_BeginCPURecord();
		pspDebugScreenSetXY(0, 0);
		pspDebugScreenPrintf("MY COUNTER: %d\n", myInt);
		pspDebugScreenPrintf("CPU TIME: %.3f ms\n", PFL_GetCPUTime());
		pspDebugScreenPrintf("CPU PERCENT: %.3f %%\n", PFL_GetCPUPercentage());

		myInt++;

		PFL_EndCPURecord();
		sceDisplayWaitVblankStart();
	}

	sceKernelExitGame();

	return 0;
}
#include <perflib.h>
#include <pspkernel.h>
#include <psprtc.h>


u32 tickResolution;
u64 lastTick;
bool advancedProfile;
/**
* This method clears the internal timers and mechanisms of PFL
*/
void PFL_Init(bool fullProfile) {
	tickResolution = sceRtcGetTickResolution();
	sceRtcGetCurrentTick(&lastTick);
	advancedProfile = fullProfile;
}

/**
* This method begins a record of when the CPU has begun doing tasks. This should be put immediately at the beginning of your game loop.
*/
void PFL_BeginCPURecord() {
	sceRtcGetCurrentTick(&lastTick);
}

double cpu_dt = 0.0;
double vbl_dt = 0.001;

u32 cpuAbsTime = 0;
u32 gpuAbsTime = 0;
u32 vblAbsTime = 1;

/**
* This method ends a record of when the CPU has finished doing tasks. This should be put before the final rendering call of your game loop.
*/
void PFL_EndCPURecord() {
	u64 temp = lastTick;
	sceRtcGetCurrentTick(&lastTick);
	cpu_dt = (double)(lastTick - temp) / ((double)tickResolution);
	cpuAbsTime = lastTick - temp;
}

/**
* This method extracts the CPU time taken between the last Start and End of the CPU performance recording (in milliseconds).
*/
double PFL_GetCPUTime() {
	return cpu_dt * 1000.0;
}

int cpuFreq = 333;

/**
* This method sets the expected frequency for percentage calculations.
*/
void PFL_SetCPUFrequency(int frequency) {
	cpuFreq = frequency;
}

int targetFrameRate = 60;
double fpsTime;

/**
* This method helps in calculation of the CPU and GPU percentages by setting a targeted framerate. Percentages above 100 mean that the CPU and or GPU is taking longer than expected.
*/
void PFL_SetTargetFrameRate(int framerate) {
	targetFrameRate = framerate;
	fpsTime = 1.0 / (double)framerate;
}

/**
* Returns the current frame rate target.
*/
int PFL_GetTargetFrameRate() {
	return targetFrameRate;
}

/**
* This method extracts the CPU time taken between the last Start and End of the CPU performance recording. This method requires the VBL time as well.
*/
double PFL_GetCPUPercentage() {
	if (!advancedProfile) {
		return cpu_dt / fpsTime;
	}
	else {
		return (double)(cpuAbsTime - vblAbsTime) * 10000.0 / ((double)cpuFreq / 2.0);
	}
}

/**
* This method begins a record of when the GPU begins doing tasks. This should be put immediately after sceGuFinish() and before sceGuSync(0, 0)
*/
void PFL_BeginGPURecord() {
	sceRtcGetCurrentTick(&lastTick);
}

double gpu_dt = 0.0;

/**
* This method ends a record of when the GPU has finished doing tasks. This should be put immediately after sceGuSync(0, 0)
*/
void PFL_EndGPURecord() {
	u64 temp = lastTick;
	sceRtcGetCurrentTick(&lastTick);
	gpu_dt = (double)(lastTick - temp) / ((double)tickResolution);
	gpuAbsTime = lastTick - temp;
}

/**
* This method begins a record of when the system is waiting for a VBlank. This should be put immediately before sceDisplayWaitVblankStart() and swap buffers.
*/
void PFL_BeginVBLRecord() {
	sceRtcGetCurrentTick(&lastTick);
}


/**
* This method begins a record of when the system has finished a VBlank. This should be put immediately after sceGuSwapBuffers().
*/
void PFL_EndVBLRecord() {
	u64 temp = lastTick;
	sceRtcGetCurrentTick(&lastTick);
	vbl_dt = (double)(lastTick - temp) / ((double)tickResolution);
	vblAbsTime = lastTick - temp;
}

/**
* This method extracts the total GPU time taken.
*/
double PFL_GetGPUTime() {
	return gpu_dt;
}

/**
* This method extracts the total GPU time as a percentage. This method requires the VBL time as well.
*/
double PFL_GetGPUPercentage() {
	if (!advancedProfile) {
		return gpu_dt / fpsTime;
	}
	else {
		return (double)(gpuAbsTime - vblAbsTime) * 10000.0 / ((double)cpuFreq / 2.0);
	}
}

/**
* This method extracts the total VBL time taken.
*/
double PFL_GetVBLTime() {
	return vbl_dt;
}
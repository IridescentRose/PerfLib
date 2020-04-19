#pragma once

#ifdef __cplusplus  
extern "C" {
#endif 

	/**
	* This method clears the internal timers and mechanisms of PFL
	*/
	void PFL_Init();

	/** 
	* This method begins a record of when the CPU has begun doing tasks. This should be put immediately at the beginning of your game loop.
	*/
	void PFL_StartCPURecord();

	/** 
	* This method ends a record of when the CPU has finished doing tasks. This should be put before the final rendering call of your game loop.
	*/
	void PFL_EndCPURecord();

	/** 
	* This method extracts the CPU time taken between the last Start and End of the CPU performance recording (in milliseconds).
	*/
	float PFL_GetCPUTime();

	/**
	* This method sets the expected frequency for percentage calculations.
	*/
	void PFL_SetCPUFrequency(int frequency);

	/**
	* This method helps in calculation of the CPU and GPU percentages by setting a targeted framerate. Percentages above 100 mean that the CPU and or GPU is taking longer than expected.
	*/
	void PFL_SetTargetFrameRate(int framerate);

	/**
	* Returns the current frame rate target.
	*/
	int PFL_GetTargetFrameRate();

	/**
	* This method extracts the CPU time taken between the last Start and End of the CPU performance recording. This method requires the VBL time as well.
	*/
	float PFL_GetCPUPercentage();

	/**
	* This method begins a record of when the GPU begins doing tasks. This should be put immediately after sceGuFinish() and before sceGuSync(0, 0)
	*/
	void PFL_BeginGPURecord();
	
	/**
	* This method ends a record of when the GPU has finished doing tasks. This should be put immediately after sceGuSync(0, 0)
	*/
	void PFL_EndGPURecord();

	/**
	* This method begins a record of when the system is waiting for a VBlank. This should be put immediately before sceDisplayWaitVblankStart() and swap buffers.
	*/
	void PFL_BeginVBLRecord();

	/**
	* This method begins a record of when the system has finished a VBlank. This should be put immediately after sceGuSwapBuffers().
	*/
	void PFL_EndVBLRecord();

	/**
	* This method extracts the total GPU time taken.
	*/
	float PFL_GetGPUTime();

	/**
	* This method extracts the total GPU time as a percentage. This method requires the VBL time as well.
	*/
	float PFL_GetGPUPercentage();

	/**
	* This method extracts the total VBL time taken.
	*/
	float PFL_GetVBLTime();


#ifdef __cplusplus  
}
#endif 
# PerfLib
A small and portable performance measuring library for the PSP. 

The library is a simple concept to grasp and is very simple to set up. It helps with tracking CPU and GPU performance statistics. It also features a "frame-relative" mode which helps you see whether it is the CPU or GPU that takes up more time (given you track the VBL time).

# How To Use The PerfLib Library
Currently the PerfLib is a set of standalone instructions which help you track performance. It must be started with `PFL_Init(bool framerelative);` if not using "frame-relative", one must set a target framerate via `PFL_SetTargetFrameRate(int fps);`. After that, see `PFL_BeginCPURecord();` and `PFL_EndCPURecord();` for placement in code. The same goes for the GPU and VBLank times. The data collected is returned by `PFL_GetCPUTime();`, `PFL_GetGPUTime();`, `PFL_GetVBLTime();` for the time in milliseconds. For percentages, use `PFL_GetCPUPercentage();` and `PFL_GetGPUPercentage();`. There is included documentation in the header and samples.

To use the library, add it to your include and library path, and make sure to link with `-lperf`

Good Luck!

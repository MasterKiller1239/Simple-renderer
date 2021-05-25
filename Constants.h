#pragma once
#define ZERO 0.00001
#define ZERO_MINUS -0.00001f
#define PI 3.14159f
#define TWO_PI 6.28318f
#define INV_PI 0.31831f
#define INV_TWO_PI 0.159155f;
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned short ushort;
#include <chrono>
typedef std::chrono::high_resolution_clock chronoClock;
typedef chronoClock::time_point chronoTime;
typedef std::chrono::duration<double> chronoDouble;
inline chronoDouble chronoDuration(chronoTime t1, chronoTime t2) {
	return  std::chrono::duration_cast<chronoDouble>(t2 - t1);
}
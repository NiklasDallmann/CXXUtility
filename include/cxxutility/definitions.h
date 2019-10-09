#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#ifdef __NVCC__
	#define HOST_DEVICE __host__ __device__
#else
	#define HOST_DEVICE
#endif

#endif // DEFINITIONS_H

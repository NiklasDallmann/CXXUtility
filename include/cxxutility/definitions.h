#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#ifdef __NVCC__
	#define HOST_DEVICE __host__ __device__
#else
	///
	/// Auxiliary macro for projects using CUDA.
	/// 
	/// If the annotated function is compiled with NVCC this macro expands to `__host__ __device__`. This is espacially useful when code is shared between
	/// translation units compiled by NVCC and the host compiler. This might be the case when functions or methods are defined in headers.
	/// 
	/// \since	0.1.0
	///
	#define HOST_DEVICE
#endif

#define CXX_UNUSED(x) \
void(x)

#if defined(__clang__)
#define CXX_CLANG __clang_version__
#endif

#if defined(__GNUC__)
#define CXX_GCC (__GNUC__ * 10 + __GNUC_MINOR__)
#endif

#endif // DEFINITIONS_H

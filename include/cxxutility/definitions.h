#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define CXX_UNUSED(x) \
void(x)

#if defined(__clang__)
#define CXX_CLANG __clang_version__
#endif

#if defined(__GNUC__)
#define CXX_GCC (__GNUC__ * 10 + __GNUC_MINOR__)
#endif

#if defined(__NVCC__)
#define CXX_NVCC
#endif

#ifdef CXX_NVCC
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

#ifndef CXX_NVCC
#ifdef __SSE__
#define CXX_SSE
#endif

#ifdef __SSE2__
#define CXX_SSE2
#endif

#ifdef __SSE3__
#define CXX_SSE3
#endif

#ifdef __SSE4_1__
#define CXX_SSE4_1
#endif

#ifdef __SSE4_2__
#define CXX_SSE4_2
#endif

#ifdef __FMA__
#define CXX_FMA
#endif

#ifdef __AVX__
#define CXX_AVX
#endif

#ifdef __AVX2__
#define CXX_AVX2
#endif
#endif // ifndef CXX_NVCC

#endif // DEFINITIONS_H

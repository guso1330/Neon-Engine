#pragma once

#include "nepch.h"

/* Windows */
#ifdef _WIN32
	#ifdef _WIN64
		#define NE_PLATFORM_WIN64
	#else
		#error "Win x86 is not support at this time"
	#endif
/* Apple */
#elif defined(__APPLE__) || defined(__MACH__)
	#include "TargetConditionals.h"
	#if TARGET_IPHONE_SIMULATOR
		  #error "iOS Simulators are not supported at this time"
	#elif TARGET_OS_IPHONE
		  #error "iOS devices are not supported at this time"
	#elif TARGET_OS_MAC
		  #define NE_PLATFORM_MACOS
	#else
		#error "Unknown Apple platform"
	#endif
/* Android */
#elif defined(__ANDROID__)
	#error "android devices are not supported at this time"
/* Linux */
#elif defined(__linux__)
	#error "linux is not supported at this time"
/* Unix */
#elif defined(__unix__)
	#error "unix is not supported at this time"
/* Posix */
#elif defined(_POSIX_VERSION)
	#error "posix is not supported at this time"
/* Compiler error */
#else
	#error "Unknown compiler"
#endif

#define NE_ASSERT(x, ...) { if(!(x)) { NE_ERROR("Assertion Failed: {0}", __VA_ARGS__); exit(EXIT_FAILURE); } }
#define NE_CORE_ASSERT(x, ...) { if(!(x)) { NE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); exit(EXIT_FAILURE); } }

namespace Neon { namespace Core {
	#if __cplusplus >= 201402L // C++14 and beyond
		using std::make_unique;
	#else
		template<typename T, typename... Args>
		std::unique_ptr<T> make_unique(Args &&... args)
		{
			NE_CORE_ASSERT(!std::is_array<T>::value, "Neon::make_unique: arrays are not supported at this time");
			return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
		}
	#endif
}}

#define NEON_ENGINE_VERSION "0.0.1"
#define NEON_ENGINE_TITLE "Neon Engine"
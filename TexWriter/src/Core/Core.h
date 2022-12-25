#pragma once

#include <memory>
#include "Debugging/DebugBreak.h"


// Platform detection using predefined macros
#ifdef _WIN32

	/* Windows x64/x86 */
#ifdef _WIN64
	/* Windows x64  */
#ifndef TW_PLATFORM_WINDOWS
#define TW_PLATFORM_WINDOWS
#endif
#else
	/* Windows x86 */
#error "x86 Builds are not supported!"
#endif


#elif defined(__APPLE__) || defined(__MACH__)

#include <TargetConditionals.h>
/* TARGET_OS_MAC exists on all the platforms
 * so we must check all of them (in this order)
 * to ensure that we're running on MAC
 * and not some other Apple platform */
#if TARGET_IPHONE_SIMULATOR == 1
#error "IOS simulator is not supported!"

#elif TARGET_OS_IPHONE == 1
#define TW_PLATFORM_IOS
#error "IOS is not supported!"

#elif TARGET_OS_MAC == 1
#define TW_PLATFORM_MACOS
#error "MacOS is not supported!"

#else
#error "Unknown Apple platform!"
#endif


 /* We also have to check __ANDROID__ before __linux__
  * since android is based on the linux kernel
  * it has __linux__ defined
  */
#elif defined(__ANDROID__)
#define TW_PLATFORM_ANDROID
#error "Android is not supported!"

#elif defined(__linux__)
#define TW_PLATFORM_LINUX
#error "Linux is not supported!"

#else
		/* Unknown compiler/platform */
#error "Unknown platform!"
#endif // End of platform detection



#ifdef TW_DEBUG
#define TW_ENABLE_ASSERTS
#endif




// DLL support
#ifdef TW_PLATFORM_WINDOWS
// Okay!
#else
#error Texture Forge only supports Windows!
#endif // End of DLL support

#ifdef TW_DEBUG
#define TW_ENABLE_ASSERTS
#endif

#ifdef TW_ENABLE_ASSERTS
#define TW_ASSERT(x, ...) { if(!(x)) { TW_LOG_ERROR("Assertion Failed: {0}", __VA_ARGS__); TW_DEBUGBREAK(); } }
#else
#define TW_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define TW_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)


namespace TexWriter {
		
	/*
		Custom memory handlers to hide unique and shared pointers.
	*/

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template<typename T1, typename T2>
	constexpr Ref<T2> CastRef(const Ref<T1>& ref)
	{
		return std::static_pointer_cast<T2>(ref);
	}

}
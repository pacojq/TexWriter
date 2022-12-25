#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

#include "ImGui/Modules/ImGuiConsole.h"

namespace TexWriter {

	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};

}

// CORE LOG MACROS
#define TW_LOG_FATAL(...)   ::TexWriter::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define TW_LOG_ERROR(...)   ::TexWriter::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TW_LOG_WARN(...)    ::TexWriter::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TW_LOG_INFO(...)    ::TexWriter::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TW_LOG_TRACE(...)   ::TexWriter::Log::GetCoreLogger()->trace(__VA_ARGS__)

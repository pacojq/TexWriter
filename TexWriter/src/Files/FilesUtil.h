#pragma once

#include "Core/Core.h"

namespace TexWriter {

	class FilesUtil
	{
	public:
		static std::string SplitFileName(const std::string& path);
		
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
	
}
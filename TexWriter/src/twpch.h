#pragma once

#define TW_VERSION_MAJOR 0
#define TW_VERSION_MINOR 2
#define TW_VERSION_PATCH 0

#ifdef TW_PLATFORM_WINDOWS

#ifndef NOMINMAX
#define NOMINMAX 1
#endif
#include <Windows.h>

#endif

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <sstream>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "Core/Log.h"
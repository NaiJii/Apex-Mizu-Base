#pragma once

#ifndef NOMINMAX
#define NOMINMAX 
#endif

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <Windows.h>
#include <intrin.h>
#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <span>
#include <algorithm>
#include <map>
#include <unordered_map>
#include <format>
#include <ranges>
#include <shared_mutex>

#include "deps/xorstr.h"	
#include "util/hash.h"
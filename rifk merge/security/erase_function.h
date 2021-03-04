#pragma once

#include "string_obfuscation.h"
#include "../macros.h"



// NOLINTNEXTLINE
#define erase_fn(a) constexpr auto concat(w, __LINE__) = &a;\
    erase_function(reinterpret_cast<uint8_t*>((void*&)concat(w, __LINE__)))
#define erase_end __asm _emit 0x90; 0x90, 0x90, 0x90, 0x90;

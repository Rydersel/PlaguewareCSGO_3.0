/* This file is part of  csgo-fake-opening by B3akers, licensed under the MIT license:
*
* MIT License
*
* Copyright (c) b3akers 2020
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "sdk.hpp"
#include "utils.hpp"

#include <stdio.h>

create_interface_fn get_module_factory( HMODULE module ) {
    return reinterpret_cast<create_interface_fn>( GetProcAddress( module, "CreateInterface" ) );
}

template<typename T>
T* get_interface( create_interface_fn f, const char* szInterfaceVersion ) {
    return reinterpret_cast<T*>( f( szInterfaceVersion, nullptr ) );
}

void sdk::init( ) {
	auto input_sys_factory = get_module_factory( GetModuleHandleW( L"inputsystem.dll" ) );
	auto localize_sys_factory = get_module_factory( GetModuleHandleW( L"localize.dll" ) );

	input_system = get_interface<i_input_system>( input_sys_factory, "InputSystemVersion001" );
	localize = get_interface<i_localize>( localize_sys_factory, "Localize_001" );

	panorama_marshall_helper = *reinterpret_cast<uintptr_t**>( utils::pattren_scan( "client.dll", "68 ? ? ? ? 8B C8 E8 ? ? ? ? 8D 4D F4 FF 15 ? ? ? ? 8B CF FF 15 ? ? ? ? 5F 5E 8B E5 5D C3" ) + 1 );
	inventory_manager = *reinterpret_cast<cs_inventory_manager**>( utils::pattren_scan( "client.dll", "B9 ?? ?? ?? ?? 8D 44 24 10 89 54 24 14" ) + 0x1 );
	gc_client = **reinterpret_cast<gc_client_system***>( utils::pattren_scan( "client.dll", "8B 0D ? ? ? ? 6A 00 83 EC 10" ) + 0x2 );
	ui_engine_source = **reinterpret_cast<ui_engine_source2***>( utils::pattren_scan( "client.dll", "8B 35 ? ? ? ? 8B D3 33 C9 8B 3E E8 ? ? ? ? 50 8B CE FF 97 ? ? ? ? 5F 5E B0 01 5B 8B E5 5D C2 04 00" ) + 0x2 );
}

namespace sdk {
	i_input_system* input_system = nullptr;
	i_localize* localize = nullptr;
	cs_inventory_manager* inventory_manager = nullptr;
	gc_client_system* gc_client = nullptr;
	ui_engine_source2* ui_engine_source = nullptr;
	uintptr_t* panorama_marshall_helper = nullptr;
};
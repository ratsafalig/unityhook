#include <BlackBone/Process/Process.h>
#include <BlackBone/Patterns/PatternSearch.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>
#include <BlackBone/Syscalls/Syscall.h>

#include <iostream>
#include "fstream"

#include "Python.h"

#include "il2cpp-config.h"
#include "il2cpp-api.h"
#include "il2cpp-api-types.h"
#include "il2cpp-class-internals.h"

using namespace blackbone;

int main( int /*argc*/, char* /*argv[]*/ )
{
	auto processes = Process::EnumByName(L"Tariff.exe");
	
	for (int i = 0; i < processes.size(); i++) {
		
		Process self;

		self.Attach(processes[i]);

		if (auto func = blackbone::MakeRemoteFunction<decltype(&il2cpp_domain_get)>(self, L"GameAssembly.dll", "il2cpp_domain_get"))
		{
			std::cout << "il2cpp_domain_get start" << std::endl;
			auto result = func();

			auto val = result.result();

			char charArray[10];

			// Copy the contents of the const char* to the char array
			strncpy(charArray, val->friendly_name, sizeof(charArray) - 1);

			std::cout << "il2cpp_domain_get end " << charArray << std::endl;
		}

		return 0;
	}
}
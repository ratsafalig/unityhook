#include <iostream>

#include "Windows.h"
#include "windows.h"

#include <BlackBone/Process/Process.h>
#include <BlackBone/Patterns/PatternSearch.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>
#include <BlackBone/Syscalls/Syscall.h>

#include "MinHook.h"

int main()
{
    auto all = blackbone::Process::EnumByNameOrPID(0, L"");

    return 0;
}


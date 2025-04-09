#include <BlackBone/Process/Process.h>
#include <BlackBone/Patterns/PatternSearch.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>
#include <BlackBone/Syscalls/Syscall.h>
#include <iostream>

using namespace blackbone;

int main( int /*argc*/, char* /*argv[]*/ )
{
    asmjit::X86RegData a;
    // List all process PIDs matching name
    auto pids = Process::EnumByName(L"explorer.exe");

    // List all process PIDs matching either by PID only
    auto procInfo = Process::EnumByNameOrPID(0x1234, L"");

    // List all processes
    auto all = Process::EnumByNameOrPID(0, L"");
}
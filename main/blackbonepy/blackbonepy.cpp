#include "blackbonepy.h"

#include <BlackBone/Process/Process.h>
#include <BlackBone/Patterns/PatternSearch.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>
#include <BlackBone/Syscalls/Syscall.h>

#include "stdlib.h"
#include "iostream"

#include "pybind11/pybind11.h"
#include <pybind11/stl.h>

std::vector<DWORD> EnumByName(const wchar_t * name)
{
    auto pids = blackbone::Process::EnumByName(name);

    return pids;
};

PYBIND11_MODULE(blackbonepy, m)
{
    m.def("EnumByName", &EnumByName);
}
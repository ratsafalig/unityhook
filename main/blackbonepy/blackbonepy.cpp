#include "blackbonepy.h"

#include <BlackBone/Process/Process.h>
#include <BlackBone/Patterns/PatternSearch.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>
#include <BlackBone/Syscalls/Syscall.h>

#include "stdlib.h"
#include "iostream"

#include "pybind11/pybind11.h"
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(blackbonepy, m)  
{  
    py::class_<blackbone::Process>(m, "Process")
        .def(py::init<>())
        .def("Attach", py::overload_cast<DWORD, DWORD>(&blackbone::Process::Attach))
        .def("EnumByName", &blackbone::Process::EnumByName);
}
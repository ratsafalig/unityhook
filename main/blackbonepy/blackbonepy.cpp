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
    py::enum_<blackbone::eModType>(m, "eModType")
        .value("mt_mod32", blackbone::eModType::mt_mod32)
        .value("mt_mod64", blackbone::eModType::mt_mod64)
        .value("mt_default", blackbone::eModType::mt_default)
        .value("mt_unknown", blackbone::eModType::mt_unknown);

    py::enum_<blackbone::eModSeachType>(m, "eModSeachType")
        .value("LdrList", blackbone::eModSeachType::LdrList)
        .value("PEHeaders", blackbone::eModSeachType::PEHeaders)
        .value("Sections", blackbone::eModSeachType::Sections);

    py::class_<blackbone::ModuleDataPtr>(m, "ModuleDataPtr");

    py::class_<blackbone::ModuleData>(m, "ModuleData");

    py::class_<blackbone::ProcessModules::mapModules>(m, "mapModules");

    py::class_<blackbone::Process>(m, "Process")
        .def(py::init<>())
        .def("Attach", py::overload_cast<DWORD, DWORD>(&blackbone::Process::Attach))
        .def("Detach", &blackbone::Process::Detach)
        .def("Resume", &blackbone::Process::Resume)
        .def("EnumByName", &blackbone::Process::EnumByName)
        .def("modules", &blackbone::Process::modules, py::return_value_policy::reference);

    py::class_<blackbone::ProcessModules>(m, "ProcessModules")
        .def("GetAllModules", [](blackbone::ProcessModules & self) {
        auto result = self.GetAllModules();
        return result;
    }, py::return_value_policy::automatic);
}
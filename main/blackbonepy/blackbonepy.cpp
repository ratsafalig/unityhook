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

    py::class_<blackbone::ModuleData, std::shared_ptr<blackbone::ModuleData>>(m, "ModuleData")
        .def_readwrite("name", &blackbone::ModuleData::name)
        .def_readwrite("fullPath",&blackbone::ModuleData::fullPath)
        .def_readwrite("baseAddress", &blackbone::ModuleData::baseAddress);

    py::class_<blackbone::ProcessModules::mapModules>(m, "mapModules");

    py::class_<blackbone::Process>(m, "Process")
        .def(py::init<>())
        .def("Attach", py::overload_cast<DWORD, DWORD>(&blackbone::Process::Attach))
        .def("Detach", &blackbone::Process::Detach)
        .def("Resume", &blackbone::Process::Resume)
        .def("EnumByName", &blackbone::Process::EnumByName)
        .def("CreateAndAttach", &blackbone::Process::CreateAndAttach)
        .def("modules", &blackbone::Process::modules, py::return_value_policy::reference);

    py::class_<blackbone::ProcessModules>(m, "ProcessModules")
        .def("GetAllModules", &blackbone::ProcessModules::GetAllModules)
        .def("GetMainModule", &blackbone::ProcessModules::GetMainModule)
        .def("GetExport", [](blackbone::ProcessModules & self, wchar_t * dll, char * name) {
            return self.GetExport(dll, name).result();
        });

    py::class_<blackbone::exportData>(m, "exportData")
        .def_readwrite("forwardName", &blackbone::exportData::forwardName)
        .def_readwrite("forwardModule", &blackbone::exportData::forwardModule)
        .def_readwrite("procAddress", &blackbone::exportData::procAddress)
        .def_readwrite("forwardOrdinal", &blackbone::exportData::forwardOrdinal)
        .def_readwrite("forwardByOrd", &blackbone::exportData::forwardByOrd);
}
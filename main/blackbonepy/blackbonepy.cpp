#include "blackbonepy.h"

#include <BlackBone/Process/Process.h>
#include <BlackBone/Patterns/PatternSearch.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>
#include <BlackBone/Syscalls/Syscall.h>

#include "stdlib.h"
#include "iostream"

#include "pybind11/pybind11.h"
#include <pybind11/stl.h>

#include "il2cpp-config.h"
#include "il2cpp-api.h"
#include "il2cpp-api-types.h"
#include "il2cpp-class-internals.h"

namespace py = pybind11;

typedef int (*A)(HWND a, LPCWSTR b, LPCWSTR c, UINT d);

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

    py::class_<Il2CppImage>(m, "Il2CppImage")
        .def_readwrite("name", &Il2CppImage::name);

    m.def("il2cpp_get_corlib", [](blackbone::Process & target) {
        if (auto func = blackbone::MakeRemoteFunction<decltype(&il2cpp_get_corlib)>(target, L"GameAssembly.dll", "il2cpp_get_corlib"))
        {
            auto result = func().result();
            return result;
        }
    });

    m.def("il2cpp_stop_gc_world", [](blackbone::Process& target) {
        if (auto func = blackbone::MakeRemoteFunction<decltype(&il2cpp_stop_gc_world)>(target, L"GameAssembly.dll", "il2cpp_stop_gc_world"))
        {
            auto result = func().result();
            return result;
        }
    });

    m.def("il2cpp_start_gc_world", [](blackbone::Process& target) {
        if (auto func = blackbone::MakeRemoteFunction<decltype(&il2cpp_start_gc_world)>(target, L"GameAssembly.dll", "il2cpp_start_gc_world"))
        {
            auto result = func().result();
            return result;
        }
    });
}
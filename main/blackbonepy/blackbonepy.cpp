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

#include "fstream"

namespace py = pybind11;

static DWORD CALLBACK VoidFn(void*){
    std::cout << "void fn called" << std::endl;
    std::ofstream outputFile("D:/Users/LP/Desktop/unityhook/output.txt", std::ios::out | std::ios::app);
    outputFile << "void fn" << std::endl;
    outputFile.flush();
    outputFile.close();

    return 0;
};

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
	py::class_<blackbone::ThreadPtr>(m, "ThreadPtr");

    py::class_<blackbone::ModuleData, std::shared_ptr<blackbone::ModuleData>>(m, "ModuleData")
        .def_readwrite("name", &blackbone::ModuleData::name)
        .def_readwrite("fullPath",&blackbone::ModuleData::fullPath)
        .def_readwrite("baseAddress", &blackbone::ModuleData::baseAddress);

    py::class_<blackbone::Thread, std::shared_ptr<blackbone::Thread>>(m, "Thread")
        .def("Suspend", &blackbone::Thread::Suspend)
        .def("Resume", &blackbone::Thread::Resume);

    py::class_<blackbone::ProcessModules::mapModules>(m, "mapModules");

    py::class_<blackbone::Process>(m, "Process")
        .def(py::init<>())
        .def("Attach", [](blackbone::Process& self, DWORD handle) {
            return self.Attach(handle, PROCESS_ALL_ACCESS);
        })
        .def("Detach", &blackbone::Process::Detach)
        .def("Resume", &blackbone::Process::Resume)
        .def("EnumByName", &blackbone::Process::EnumByName)
        .def("CreateAndAttach", [](blackbone::Process & self, wchar_t * path) {
            return self.blackbone::Process::CreateAndAttach(path);
        })
        .def("threads", &blackbone::Process::threads, py::return_value_policy::reference)
        .def("modules", &blackbone::Process::modules, py::return_value_policy::reference);

    py::class_<blackbone::ProcessModules>(m, "ProcessModules")
        .def("GetAllModules", &blackbone::ProcessModules::GetAllModules)
        .def("GetMainModule", &blackbone::ProcessModules::GetMainModule)
        .def("GetExport", [](blackbone::ProcessModules & self, wchar_t * dll, char * name) {
            return self.GetExport(dll, name).result();
        });

    py::class_<blackbone::ProcessThreads>(m, "ProcessThreads")
        .def("getAll", &blackbone::ProcessThreads::getAll)
        .def("getMain", &blackbone::ProcessThreads::getMain);

    py::class_<blackbone::exportData>(m, "exportData")
        .def_readwrite("forwardName", &blackbone::exportData::forwardName)
        .def_readwrite("forwardModule", &blackbone::exportData::forwardModule)
        .def_readwrite("procAddress", &blackbone::exportData::procAddress)
        .def_readwrite("forwardOrdinal", &blackbone::exportData::forwardOrdinal)
        .def_readwrite("forwardByOrd", &blackbone::exportData::forwardByOrd);

    py::class_<Il2CppImage>(m, "Il2CppImage")
        .def_readwrite("name", &Il2CppImage::name)
        .def_readwrite("typeCount", &Il2CppImage::typeCount)
        .def_readwrite("nameNoExt", &Il2CppImage::nameNoExt)
        .def_readwrite("exportedTypeCount", &Il2CppImage::exportedTypeCount);
    py::class_<Il2CppDomain>(m, "Il2CppDomain")
        .def_readwrite("domain_id", &Il2CppDomain::domain_id);

    m.def("il2cpp_get_corlib", [](blackbone::Process & target) {
        if (auto func = blackbone::MakeRemoteFunction<decltype(&il2cpp_get_corlib)>(target, L"GameAssembly.dll", "il2cpp_get_corlib"))
        {
            auto result = func().result();

            std::cout << "typeCount " << result->typeCount << std::endl;
            std::cout << "exportedTypeCount " << result->exportedTypeCount << std::endl;
            std::cout << "nameNoExt " << result->nameNoExt << std::endl;

            return *result;
        }
    },py::return_value_policy::reference);

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

    m.def("il2cpp_object_header_size", [](blackbone::Process& target) {
        if (auto func = blackbone::MakeRemoteFunction<decltype(&il2cpp_object_header_size)>(target, L"GameAssembly.dll", "il2cpp_object_header_size"))
        {
            auto result = func().result();

            return result;
        }
    });

    m.def("il2cpp_class_for_each", [](blackbone::Process& target) {
        if (auto func = blackbone::MakeRemoteFunction<decltype(&il2cpp_class_for_each)>(target, L"GameAssembly.dll", "il2cpp_class_for_each"))
        {
            std::cout << "il2cpp_class_for_each" << std::endl;

            auto result = func([](Il2CppClass* klass, void* userData) {
                std::cout << "klass->name " << klass->name << std::endl;
            }, nullptr);
        }
    });

    m.def("il2cpp_stats_dump_to_file", [](blackbone::Process& target, const char* path) {
        if (auto func = blackbone::MakeRemoteFunction<decltype(&il2cpp_stats_dump_to_file)>(target, L"GameAssembly.dll", "il2cpp_stats_dump_to_file"))
        {
            std::cout << "il2cpp_stats_dump_to_file" << std::endl;

            func(path);
        }
    });

    m.def("il2cpp_domain_get", [](blackbone::Process& target) {
        if (auto func = blackbone::MakeRemoteFunction<decltype(&il2cpp_domain_get)>(target, L"GameAssembly.dll", "il2cpp_domain_get"))
        {
            std::cout << "il2cpp_domain_get start" << std::endl;
            auto result = func();

            auto val = result.result();

            char charArray[10];

            // Copy the contents of the const char* to the char array
            strncpy(charArray, val->friendly_name, sizeof(charArray) - 1);

            std::cout << "il2cpp_domain_get end " << charArray << std::endl;
        }
    });
}
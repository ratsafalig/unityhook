#include <BlackBone/Process/Process.h>
#include <BlackBone/Patterns/PatternSearch.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>
#include <BlackBone/Syscalls/Syscall.h>

#include <iostream>
#include "fstream"

#include "Python.h"

using namespace blackbone;

int main( int /*argc*/, char* /*argv[]*/ )
{
    Py_InitializeEx(0);

	std::ifstream file("D:\\Users\\LP\\Desktop\\unityhook\\python\\test.py");

    // Get the size of the file
    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the file content into a string
    std::string content;
    content.resize(fileSize);
    file.read(&content[0], fileSize);

    // Close the file
    file.close();

    // Access the content as a const char*
    const char* utf8Content = content.c_str();

    PyRun_SimpleString(utf8Content);

    Py_FinalizeEx(); 
}
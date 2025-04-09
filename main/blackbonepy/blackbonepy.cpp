#include "blackbonepy.h"

#include <BlackBone/Process/Process.h>
#include <BlackBone/Patterns/PatternSearch.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>
#include <BlackBone/Syscalls/Syscall.h>

#include "stdlib.h"

#include <boost/python.hpp>

//std::vector<char*> test() {
//	std::vector<char*> result;
//	char* str = (char*)malloc(100);
//	strcpy(str, "hello");
//	result.push_back(str);
//	return result;
//}

char const* greet()
{
    return "greeting, hello";
};

BOOST_PYTHON_MODULE(blackbonepy)
{
    asmjit::X86RegData a;
    using namespace boost::python;
    def("greet", greet);
	//def("test", test);
}

int main() {
    return 0;
}
#include "blackbonepy.h"

#include <boost/python.hpp>

char const* greet()
{
    return "greeting, hello";
};

BOOST_PYTHON_MODULE(blackbonepy)
{
    using namespace boost::python;
    def("greet", greet);
}
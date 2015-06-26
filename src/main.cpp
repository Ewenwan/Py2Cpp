#include <climits>
#include <iostream>

#include <tuple>

#include <Python.h>
#include "py2cpp.hpp"

using namespace dubzzz::Py2Cpp;

int main(int argc, char* argv[])
{
  {
    // PyObject*
    PyObject* pyo { Py_None };
    PyObject* out { CppBuilder<PyObject*>()(pyo) };
    std::cout << "PyObject*:\t" << out << std::endl;
  }
  
  {
    // bool
    PyObject* pyo { Py_True };
    bool b { CppBuilder<bool>()(pyo) };
    std::cout << std::boolalpha << "bool:\t" << b << std::endl;
  }
  
  {
    // int
    PyObject* pyo { PyLong_FromLong(-50) };
    int v { CppBuilder<int>()(pyo) };
    std::cout << "int:\t" << v << std::endl;
  }
  
  {
    // unsigned int
    PyObject* pyo { PyLong_FromUnsignedLong(1024) };
    unsigned int v { CppBuilder<unsigned int>()(pyo) };
    std::cout << "uint:\t" << v << std::endl;
  }
  
  {
    // long
    PyObject* pyo { PyLong_FromLong(-50) };
    long v { CppBuilder<long>()(pyo) };
    std::cout << "long:\t" << v << std::endl;
  }
  
  {
    // unsigned long
    PyObject* pyo { PyLong_FromUnsignedLong(ULONG_MAX) };
    unsigned long v { CppBuilder<unsigned long>()(pyo) };
    std::cout << "ulong:\t" << v << std::endl;
  }
  
  {
    // long long
    PyObject* pyo { PyLong_FromLongLong(LLONG_MIN) };
    long long v { CppBuilder<long long>()(pyo) };
    std::cout << "long long:\t" << v << std::endl;
  }
  
  {
    // unsigned long long
    PyObject* pyo { PyLong_FromUnsignedLongLong(ULLONG_MAX) };
    unsigned long long v { CppBuilder<unsigned long long>()(pyo) };
    std::cout << "ulong long:\t" << v << std::endl;
  }

  {
    // double (from pylong)
    PyObject* pyo1 { PyLong_FromLong(50) };
    double v1 { CppBuilder<double>()(pyo1) };
    std::cout << "double:\t" << v1 << std::endl;
    
    // double
    PyObject* pyo2 { PyFloat_FromDouble(1.1) };
    double v2 { CppBuilder<double>()(pyo2) };
    std::cout << "double:\t" << v2 << std::endl;
  }

  {
    // tuple<int, int, double>
    PyObject* pyo {
        PyTuple_Pack(3,
          PyLong_FromLong(-50),
          PyLong_FromLong(750),
          PyFloat_FromDouble(1.1)) };
    std::tuple<int,int,double> out { CppBuilder<std::tuple<int,int,double>>()(pyo) };
    std::cout << "tuple<int,int,double>:\t" << std::get<0>(out) << ", " << std::get<1>(out) << ", " << std::get<2>(out) << std::endl;  
  }

  return 0;
}


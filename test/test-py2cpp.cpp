#include <Python.h>
#include "gtest/gtest.h"

#include <climits>
#include <memory>
#include <sstream>
#include "py2cpp.hpp"

using namespace dubzzz::Py2Cpp;
PyObject *py_main;
PyObject *py_dict;

namespace
{
  struct decref
  {
    void operator() (PyObject* pyo)
    {
      Py_DECREF(pyo);
    }
  };
}


static bool uncaught_exception()
{
  if (!! PyErr_Occurred())
  {
    PyErr_Clear();
    return true;
  }
  return false;
}

/** bool **/

TEST(CppBuilder_bool, True)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("True", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(true, CppBuilder<bool>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}
TEST(CppBuilder_bool, False)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("False", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(true, !CppBuilder<bool>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

/** int **/

TEST(CppBuilder_int, Zero)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("0", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(0, CppBuilder<int>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_int, Any)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("5", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(5, CppBuilder<int>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_int, MinValue)
{
  std::ostringstream out; out << INT_MIN;
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(INT_MIN, CppBuilder<int>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_int, MaxValue)
{
  std::ostringstream out; out << INT_MAX;
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(INT_MAX, CppBuilder<int>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_int, LessThanMinValue)
{
  std::ostringstream out; out << INT_MIN << "-1";
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<int>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_int, MoreThanMaxValue)
{
  std::ostringstream out; out << INT_MAX << "+1";
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<int>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

/** unsigned int **/

TEST(CppBuilder_uint, Zero)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("0", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(0, CppBuilder<unsigned int>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_uint, Any)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("5", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(5, CppBuilder<unsigned int>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_uint, MaxValue)
{
  std::ostringstream out; out << UINT_MAX;
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(UINT_MAX, CppBuilder<unsigned int>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_uint, LessThanZero)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("-1", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<unsigned int>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_uint, MoreThanMaxValue)
{
  std::ostringstream out; out << UINT_MAX << "+1";
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<unsigned int>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

/** long **/

TEST(CppBuilder_long, Zero)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("0", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(0, CppBuilder<long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_long, Any)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("5", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(5, CppBuilder<long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_long, MinValue)
{
  std::ostringstream out; out << LONG_MIN;
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(LONG_MIN, CppBuilder<long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_long, MaxValue)
{
  std::ostringstream out; out << LONG_MAX;
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(LONG_MAX, CppBuilder<long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_long, LessThanMinValue)
{
  std::ostringstream out; out << LONG_MIN << "-1";
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<long>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_long, MoreThanMaxValue)
{
  std::ostringstream out; out << LONG_MAX << "+1";
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<long>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

/** unsigned long **/

TEST(CppBuilder_ulong, Zero)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("0", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(0, CppBuilder<unsigned long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_ulong, Any)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("5", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(5, CppBuilder<unsigned long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_ulong, MaxValue)
{
  std::ostringstream out; out << ULONG_MAX;
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(ULONG_MAX, CppBuilder<unsigned long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_ulong, LessThanZero)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("-1", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<unsigned long>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_ulong, FarLessThanZero)
{
  std::ostringstream out; out << LONG_MIN << "-1"; // in order to get a PyLong
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<unsigned long>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_ulong, MoreThanMaxValue)
{
  std::ostringstream out; out << ULONG_MAX << "+1";
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<unsigned long>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

/** long long **/

TEST(CppBuilder_llong, Zero)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("0", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(0, CppBuilder<long long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_llong, Any)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("5", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(5, CppBuilder<long long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_llong, MinValue)
{
  std::ostringstream out; out << LLONG_MIN;
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(LLONG_MIN, CppBuilder<long long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_llong, MaxValue)
{
  std::ostringstream out; out << LLONG_MAX;
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(LLONG_MAX, CppBuilder<long long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_llong, LessThanMinValue)
{
  std::ostringstream out; out << LLONG_MIN << "-1";
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<long long>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_llong, MoreThanMaxValue)
{
  std::ostringstream out; out << LLONG_MAX << "+1";
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<long long>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

/** unsigned long **/

TEST(CppBuilder_ullong, Zero)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("0", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(0, CppBuilder<unsigned long long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_ullong, Any)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("5", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(5, CppBuilder<unsigned long long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_ullong, MaxValue)
{
  std::ostringstream out; out << ULLONG_MAX;
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(ULLONG_MAX, CppBuilder<unsigned long long>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_ullong, LessThanZero)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("-1", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<unsigned long long>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_ullong, FarLessThanZero)
{
  std::ostringstream out; out << LONG_MIN << "-1"; // in order to get a PyLong
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<unsigned long long>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_ullong, MoreThanMaxValue)
{
  std::ostringstream out; out << ULLONG_MAX << "+1";
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(out.str().c_str(), Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_THROW(CppBuilder<unsigned long long>()(pyo.get()), std::overflow_error);
  EXPECT_FALSE(uncaught_exception());
}

/** std::string **/

TEST(CppBuilder_string, String)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("'hello'", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ("hello", CppBuilder<std::string>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_string, Unicode)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("u'hello'", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ("hello", CppBuilder<std::string>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_string, UnicodeExotic)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(
      "u'\u15c7\u25d8\u0034\u2b15'", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ("\xe1\x97\x87\xe2\x97\x98\x34\xe2\xac\x95", CppBuilder<std::string>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

/** std::wstring **/

TEST(CppBuilder_wstring, String)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("'hello'", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(L"hello", CppBuilder<std::wstring>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_wstring, Unicode)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("u'hello'", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(L"hello", CppBuilder<std::wstring>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

TEST(CppBuilder_wstring, UnicodeExotic)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String(
      "u'\u15c7\u25d8\u0034\u2b15'", Py_eval_input, py_dict, NULL) }; //utf-16
  ASSERT_NE(nullptr, pyo.get());
  EXPECT_EQ(L"\xe1\x97\x87\xe2\x97\x98\x34\xe2\xac\x95", CppBuilder<std::wstring>()(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

/** MISC **/

TEST(CppBuilder_mix, AnyValue)
{
  std::unique_ptr<PyObject, decref> pyo { PyRun_String("{ \
        'positions':[ \
        { \
          'x': 5, \
          'y': 10, \
        }, { \
          'x': -1, \
          'y': 2, \
        }], \
      }", Py_eval_input, py_dict, NULL) };
  ASSERT_NE(nullptr, pyo.get());
  
  std::map<std::string, std::vector<std::map<std::string, int>>> elt;
  std::vector<std::map<std::string, int>> positions;
  positions.push_back({ {"x", 5}, {"y", 10} });
  positions.push_back({ {"x", -1}, {"y", 2} });
  elt["positions"] = positions;
  
  auto Functor = CppBuilder<std::map<std::string, std::vector<std::map<std::string, int>>>>();
  EXPECT_EQ(elt, Functor(pyo.get()));
  EXPECT_FALSE(uncaught_exception());
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  Py_Initialize();
  py_main = PyImport_AddModule("__main__");
  py_dict = PyModule_GetDict(py_main);
  int ret { RUN_ALL_TESTS() };
  Py_Finalize();
  return ret;
}


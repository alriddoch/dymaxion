// This file may be redistributed and modified only under the terms of
// the GNU General Public License (See COPYING for details).
// Copyright (C) 2014 Alistair Riddoch

#ifndef TESTS_TEST_H
#define TESTS_TEST_H

#include "compose.hpp"

#include <functional>
#include <iostream>

namespace Test {

class Test
{
 public:
  char const * name;
  std::function<void()> method;
};

class Suite
{
 protected:
  int m_error_count;
  // Need to track not just counts, but also details of the failures,
  // which basically requires macros.
  std::list<std::string> m_errorReports;

  std::list<Test> m_tests;

  void addFailure(std::string const & s)
  {
    m_errorReports.push_back(s);
  }

 public:
  virtual ~Suite();

  virtual void setup() = 0;
  virtual void teardown() = 0;

  std::size_t errorCount() const;

  const std::list<std::string> & errorReports() const;

  void addTest(Test t);

  int run();

  template <typename V>
  int assertTrue(char const * n, V const & val,
                 char const * func, char const * file, int line);

  template <typename L, typename R>
  int assertEqual(char const * l, L const & lval,
                  char const * r, R const & rval,
                  char const * func, char const * file, int line);

  template <typename L, typename R>
  int assertNotEqual(char const * l, L const & lval,
                     char const * r, R const & rval,
                     char const * func, char const * file, int line);

  template <typename L, typename R>
  int assertGreater(char const * l, L const & lval,
                    char const * r, R const & rval,
                    char const * func, char const * file, int line);

  template <typename L, typename R>
  int assertNotGreater(char const * l, L const & lval,
                       char const * r, R const & rval,
                       char const * func, char const * file, int line);

  template <typename L, typename R>
  int assertLess(char const * l, L const & lval,
                 char const * r, R const & rval,
                 char const * func, char const * file, int line);

  template <typename L, typename R>
  int assertNotLess(char const * l, L const & lval,
                    char const * r, R const & rval,
                    char const * func, char const * file, int line);

  template <typename T>
  int assertNull(char const * n, T const * ptr,
                 char const * func, char const * file, int line);

  template <typename T>
  int assertNotNull(char const * n, T const * ptr,
                    char const * func, char const * file, int line);

};

inline
Suite::~Suite()
{
}

std::size_t Suite::errorCount() const
{
  return m_errorReports.size();
}

const std::list<std::string> & Suite::errorReports() const
{
  return m_errorReports;
}

void Suite::addTest(Test t)
{
  m_tests.push_back(t);
}

int Suite::run()
{
  int error_count = 0;

  std::list<Test>::const_iterator Iend = m_tests.end();
  std::list<Test>::const_iterator I = m_tests.begin();
  for (; I != Iend; ++I)
  {
    setup();
    (*I).method();
    teardown();

    if (!m_errorReports.empty())
    {
      ++error_count;

      std::cerr << "Test \"" << (*I).name << "\" failed:" << std::endl;

      std::list<std::string>::const_iterator I = m_errorReports.begin();
      std::list<std::string>::const_iterator Iend = m_errorReports.end();
      for (; I != Iend; ++I)
      {
        std::cerr << *I << std::endl;
      }

      m_errorReports.clear();
    }
  }

  return error_count;
}

template <typename V>
int Suite::assertTrue(char const * n, V const & val,
                      char const * func, char const * file, int line)
{
  if (!val)
  {
    addFailure(String::compose("%1:%2: %3: Assertion '%4' failed.",
                               file, line, func, n));
    return -1;
  }
  return 0;
}

template <typename L, typename R>
int Suite::assertEqual(char const * l, L const & lval,
                       char const * r, R const & rval,
                       char const * func, char const * file, int line)
{
  if (lval != rval)
  {
    addFailure(String::compose("%1:%2: %3: Assertion '%4 == %5' failed. "
                               "%6 != %7",
                               file, line, func, l, r, lval, rval));
    return -1;
  }
  return 0;
}

template <typename L, typename R>
int Suite::assertNotEqual(char const * l, L const & lval,
                          char const * r, R const & rval,
                          char const * func, char const * file, int line)
{
  if (lval == rval)
  {
    addFailure(String::compose("%1:%2: %3: Assertion '%4 != %5' failed. "
                               "%6 == %7",
                               file, line, func, l, r, lval, rval));
    return -1;
  }
  return 0;
}

template <typename L, typename R>
int Suite::assertGreater(char const * l, L const & lval,
                         char const * r, R const & rval,
                         char const * func, char const * file, int line)
{
  if (!(lval > rval))
  {
    addFailure(String::compose("%1:%2: %3: Assertion '%4 > %5' failed. "
                               "%6 <= %7",
                               file, line, func, l, r, lval, rval));
    return -1;
  }
  return 0;
}

template <typename L, typename R>
int Suite::assertNotGreater(char const * l, L const & lval,
                            char const * r, R const & rval,
                            char const * func, char const * file, int line)
{
  if (lval > rval)
  {
    addFailure(String::compose("%1:%2: %3: Assertion '%4 !> %5' failed. "
                               "%6 > %7",
                               file, line, func, l, r, lval, rval));
    return -1;
  }
  return 0;
}

template <typename L, typename R>
int Suite::assertLess(char const * l, L const & lval,
                      char const * r, R const & rval,
                      char const * func, char const * file, int line)
{
  if (!(lval < rval))
  {
    addFailure(String::compose("%1:%2: %3: Assertion '%4 < %5' failed. "
                               "%6 >= %7",
                               file, line, func, l, r, lval, rval));
    return -1;
  }
  return 0;
}

template <typename L, typename R>
int Suite::assertNotLess(char const * l, L const & lval,
                         char const * r, R const & rval,
                         char const * func, char const * file, int line)
{
  if (lval < rval)
  {
    addFailure(String::compose("%1:%2: %3: Assertion '%4 !< %5' failed. "
                               "%6 < %7",
                               file, line, func, l, r, lval, rval));
    return -1;
  }
  return 0;
}

template <typename T>
int Suite::assertNull(char const * n, T const * ptr,
                      char const * func, char const * file, int line)
{
  if (ptr != 0)
  {
    addFailure(String::compose("%1:%2: %3: Assertion '%4' null failed.",
                               file, line, func, n));
    return -1;
  }
  return 0;
}

template <typename T>
int Suite::assertNotNull(char const * n, T const * ptr,
                         char const * func, char const * file, int line)
{
  if (ptr == 0)
  {
    addFailure(String::compose("%1:%2: %3: Assertion '%4' not null failed.",
                               file, line, func, n));
    return -1;
  }
  return 0;
}

}

#define ADD_TEST(_function) { \
    Test::Test _function_test = { # _function, \
                                  std::bind(&_function, this) }; \
    this->addTest(_function_test); \
}

#define ASSERT_TRUE(_expr) { \
    if (this->assertTrue(# _expr, _expr, __PRETTY_FUNCTION__, \
                         __FILE__, __LINE__) != 0) { return; } \
}

#define ASSERT_EQUAL(_lval, _rval) { \
    if (this->assertEqual(# _lval, _lval, # _rval, _rval, __PRETTY_FUNCTION__, \
                          __FILE__, __LINE__) != 0) { return; } \
}

#define ASSERT_NOT_EQUAL(_lval, _rval) { \
    if (this->assertNotEqual(# _lval, _lval, # _rval, _rval, __PRETTY_FUNCTION__, \
                             __FILE__, __LINE__) != 0) { return; } \
}

#define ASSERT_GREATER(_lval, _rval) { \
    if (this->assertGreater(# _lval, _lval, # _rval, _rval, __PRETTY_FUNCTION__, \
                            __FILE__, __LINE__) != 0) { return; } \
}

#define ASSERT_NOT_GREATER(_lval, _rval) { \
    if (this->assertNotGreater(# _lval, _lval, # _rval, _rval, \
                               __PRETTY_FUNCTION__, __FILE__, __LINE__) \
        != 0) { return; } \
}

#define ASSERT_LESS(_lval, _rval) { \
    if (this->assertLess(# _lval, _lval, # _rval, _rval, __PRETTY_FUNCTION__, \
                         __FILE__, __LINE__) != 0) { return; } \
}

#define ASSERT_NOT_LESS(_lval, _rval) { \
    if (this->assertNotLess(# _lval, _lval, # _rval, _rval, __PRETTY_FUNCTION__, \
                            __FILE__, __LINE__) != 0) { return; } \
}

#define ASSERT_NULL(_ptr) { \
    if (this->assertNull(# _ptr, _ptr, __PRETTY_FUNCTION__, \
                         __FILE__, __LINE__) != 0) { return; } \
}

#define ASSERT_NOT_NULL(_ptr) { \
    if (this->assertNotNull(# _ptr, _ptr, __PRETTY_FUNCTION__, \
                            __FILE__, __LINE__) != 0) { return; } \
}

#endif // TESTS_TEST_H

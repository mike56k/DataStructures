#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <stackl/stackl.h>

constexpr float eps = std::numeric_limits<float>::epsilon();

TEST_CASE("Test StackL ctor, is_empty()") {
  StackL s = StackL();
  CHECK(s.is_empty());
}

TEST_CASE("Test StackL check error in top()") {
  StackL s = StackL();

  bool t = false;
  try {
    float f = s.top();
  }
  catch (std::out_of_range&) {
    t = true;
  }
  CHECK(t == true);

  t = false;
  try {
    s.top() = 0.1f;
  }
  catch (std::out_of_range&) {
    t = true;
  }
  CHECK(t == true);
}

TEST_CASE("Test StackL one push()->top()->pop()") {
  StackL s = StackL();
  float f = 15.7f;
  s.push(f);
  CHECK(s.is_empty() == false);

  CHECK(std::fabs(s.top() - f) < 2 * eps);

  s.top() = 5.8f;
  CHECK(std::fabs(s.top() - f) > 2 * eps);

  s.pop();
  CHECK(s.is_empty() == true);
}

TEST_CASE("Test StackL [push() array] -> [top()-pop() array]") {
  StackL s = StackL();
  std::ptrdiff_t n = 15;

  for (std::ptrdiff_t i = 0; i < n; i++)
    s.push(static_cast<float>(i));

  CHECK(s.is_empty() == false);

  for (std::ptrdiff_t i = (n - 1); i >= 0; i--)
  {
    CHECK(std::fabs(s.top() - static_cast<float>(i)) < 2 * eps);
    s.pop();
  }

  CHECK(s.is_empty() == true);
}

TEST_CASE("Test StackL [push() array] -> [top()-pop() array] with offset") {
  StackL s = StackL();

  for (std::ptrdiff_t i = 0; i < 12; i++)
    s.push(static_cast<float>(i));

  for (std::ptrdiff_t i = (12 - 1); i >= 2; i--)
  {
    CHECK(std::fabs(s.top() - static_cast<float>(i)) < 2 * eps);
    s.pop();
  }

  for (std::ptrdiff_t i = 0; i < 10; i++)
    s.push(static_cast<float>(i));

  for (std::ptrdiff_t i = (10 - 1); i >= 0; i--)
  {
    CHECK(std::fabs(s.top() - static_cast<float>(i)) < 2 * eps);
    s.pop();
  }

  for (std::ptrdiff_t i = 1; i >= 0; i--)
  {
    CHECK(std::fabs(s.top() - static_cast<float>(i)) < 2 * eps);
    s.pop();
  }

  CHECK(s.is_empty() == true);
}

TEST_CASE("Test StackL [push() array] -> [copy] -> [top()-pop() array]") {
  StackL s = StackL();
  std::ptrdiff_t n = 15;

  for (std::ptrdiff_t i = 0; i < n; i++)
    s.push(static_cast<float>(i));

  StackL s_copy = StackL(s);

  CHECK(s_copy.is_empty() == false);

  for (std::ptrdiff_t i = (n - 1); i >= 0; i--)
  {
    CHECK(std::fabs(s_copy.top() - static_cast<float>(i)) < 2 * eps);
    s_copy.pop();
  }

  CHECK(s_copy.is_empty() == true);
  CHECK(s.is_empty() == false);
}

TEST_CASE("Test StackL [push() array] -> [copy] -> [top()-pop() array] with offset") {
  StackL s = StackL();

  for (std::ptrdiff_t i = 0; i < 12; i++)
    s.push(static_cast<float>(i));

  for (std::ptrdiff_t i = (12 - 1); i >= 2; i--)
  {
    CHECK(std::fabs(s.top() - static_cast<float>(i)) < 2 * eps);
    s.pop();
  }

  for (std::ptrdiff_t i = 0; i < 10; i++)
    s.push(static_cast<float>(i));

  StackL s_copy = StackL(s);

  for (std::ptrdiff_t i = (10 - 1); i >= 0; i--)
  {
    CHECK(std::fabs(s_copy.top() - static_cast<float>(i)) < 2 * eps);
    s_copy.pop();
  }

  for (std::ptrdiff_t i = 1; i >= 0; i--)
  {
    CHECK(std::fabs(s_copy.top() - static_cast<float>(i)) < 2 * eps);
    s_copy.pop();
  }

  CHECK(s_copy.is_empty() == true);
  CHECK(s.is_empty() == false);
}

TEST_CASE("Test StackL [push() array] -> [=] -> [top()-pop() array]") {
  StackL s = StackL();
  std::ptrdiff_t n = 15;

  for (std::ptrdiff_t i = 0; i < n; i++)
    s.push(static_cast<float>(i));

  StackL s_new = StackL();
  CHECK(s_new.is_empty() == true);

  s_new = s;
  CHECK(s_new.is_empty() == false);

  for (std::ptrdiff_t i = (n - 1); i >= 0; i--)
  {
    CHECK(std::fabs(s_new.top() - static_cast<float>(i)) < 2 * eps);
    s_new.pop();
  }

  CHECK(s_new.is_empty() == true);
  CHECK(s.is_empty() == false);
}

TEST_CASE("Test StackL [push() array] -> [=] -> [top()-pop() array] with offset") {
  StackL s = StackL();

  for (std::ptrdiff_t i = 0; i < 12; i++)
    s.push(static_cast<float>(i));

  for (std::ptrdiff_t i = (12 - 1); i >= 2; i--)
  {
    CHECK(std::fabs(s.top() - static_cast<float>(i)) < 2 * eps);
    s.pop();
  }

  for (std::ptrdiff_t i = 0; i < 10; i++)
    s.push(static_cast<float>(i));

  StackL s_new = StackL();
  CHECK(s_new.is_empty() == true);

  s_new = s;
  CHECK(s_new.is_empty() == false);

  for (std::ptrdiff_t i = (10 - 1); i >= 0; i--)
  {
    CHECK(std::fabs(s_new.top() - static_cast<float>(i)) < 2 * eps);
    s_new.pop();
  }

  for (std::ptrdiff_t i = 1; i >= 0; i--)
  {
    CHECK(std::fabs(s_new.top() - static_cast<float>(i)) < 2 * eps);
    s_new.pop();
  }

  CHECK(s_new.is_empty() == true);
  CHECK(s.is_empty() == false);
}

TEST_CASE("Test StackL: my self") {
  StackL s;
  s.push(1.0f);
  s.push(2.0f);
  // std::cout << s.is_empty() << std::endl;

  s = s;

  CHECK(std::fabs(s.top() - static_cast<float>(2.0f)) < 2 * eps);
  s.pop();

  CHECK(std::fabs(s.top() - static_cast<float>(1.0f)) < 2 * eps);
  s.pop();

  CHECK(s.is_empty() == true);
}

TEST_CASE("Test StackL: large stack: my self") {
  ptrdiff_t count = 1024 * 1024;
  StackL s;
  for (ptrdiff_t i = 0; i < count; i++) {
    s.push(static_cast<float>(i));
  }

  s = s;

  bool is_ok = false;
  for (std::ptrdiff_t i = (count - 1); i >= 0; i--) {
    is_ok = std::fabs(s.top() - static_cast<float>(i)) < 2 * eps;
    s.pop();
    if (!is_ok)
      break;
  }

  CHECK(is_ok);
  CHECK(s.is_empty() == true);
}

TEST_CASE("Test StackL: large stack :copy ctor") {
  ptrdiff_t count = 1024 * 1024;
  StackL s;
  for (ptrdiff_t i = 0; i < count; i++) {
    s.push(static_cast<float>(i));
  }

  StackL s2 = StackL(s);

  bool is_ok = false;
  for (std::ptrdiff_t i = (count - 1); i >= 0; i--) {
    is_ok = std::fabs(s2.top() - static_cast<float>(i)) < 2 * eps;
    s2.pop();
    if (!is_ok)
      break;
  }

  CHECK(is_ok);
  CHECK(s2.is_empty() == true);
}

TEST_CASE("Test StackL: large stack: operator=; [1]") {
  ptrdiff_t count = 1024 * 1024;
  StackL s;
  for (ptrdiff_t i = 0; i < count * 2; i++) {
    s.push(static_cast<float>(i));
  }

  StackL s2;
  for (ptrdiff_t i = 0; i < count; i++) {
    s2.push(static_cast<float>(i));
  }

  s2 = s;

  bool is_ok = false;
  for (std::ptrdiff_t i = (count * 2 - 1); i >= 0; i--) {
    is_ok = std::fabs(s2.top() - static_cast<float>(i)) < 2 * eps;
    if (!is_ok)
      CHECK(std::fabs(s2.top() - static_cast<float>(i)) < 2 * eps);
    s2.pop();
    if (!is_ok)
      break;
  }

  CHECK(is_ok);
  CHECK(s2.is_empty() == true);
}

TEST_CASE("Test StackL: large stack: operator=; [2]") {
  ptrdiff_t count = 1024 * 1024;
  StackL s;
  for (ptrdiff_t i = 0; i < count; i++) {
    s.push(static_cast<float>(i));
  }

  StackL s2;
  for (ptrdiff_t i = 0; i < count * 2; i++) {
    s2.push(static_cast<float>(i));
  }

  s2 = s;

  bool is_ok = false;
  for (std::ptrdiff_t i = (count - 1); i >= 0; i--) {
    is_ok = std::fabs(s2.top() - static_cast<float>(i)) < 2 * eps;
    if (!is_ok)
      CHECK(std::fabs(s2.top() - static_cast<float>(i)) < 2 * eps);
    s2.pop();
    if (!is_ok)
      break;
  }

  CHECK(is_ok);
  CHECK(s2.is_empty() == true);
}
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <queuea/queuea.h>

constexpr float eps = std::numeric_limits<float>::epsilon();

TEST_CASE("Test QueueA ctor, is_empty()") {
  QueueA q = QueueA();
  CHECK(q.is_empty());
}

TEST_CASE("Test QueueA check error in top()") {
  QueueA q = QueueA();

  bool t = false;
  try {
    float f = q.top();
  }
  catch (std::out_of_range&) {
    t = true;
  }
  CHECK(t == true);

  t = false;
  try {
    q.top() = 0.1f;
  }
  catch (std::out_of_range&) {
    t = true;
  }
  CHECK(t == true);
}

TEST_CASE("Test QueueA one push()->top()->pop()") {
  QueueA q = QueueA();
  float f = 15.7f;
  q.push(f);
  CHECK(q.is_empty() == false);

  CHECK(std::fabs(q.top() - f) < 2 * eps);

  q.top() = 5.8f;
  CHECK(std::fabs(q.top() - f) > 2 * eps);

  q.pop();
  CHECK(q.is_empty() == true);
}

TEST_CASE("Test QueueA [push() array] -> [top()-pop() array]") {
  QueueA q = QueueA();
  std::ptrdiff_t n = 15;

  for (std::ptrdiff_t i = 0; i < n; i++)
    q.push(static_cast<float>(i));

  CHECK(q.is_empty() == false);

  for (std::ptrdiff_t i = 0; i < n; i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  CHECK(q.is_empty() == true);
}

TEST_CASE("Test QueueA [push() array] -> [top()-pop() array] with offset") {
  QueueA q = QueueA();

  for (std::ptrdiff_t i = 0; i < 12; i++)
    q.push(static_cast<float>(i));

  for (std::ptrdiff_t i = 0; i < 10; i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  for (std::ptrdiff_t i = 0; i < 10; i++)
    q.push(static_cast<float>(i));

  for (std::ptrdiff_t i = 10; i < 12; i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  for (std::ptrdiff_t i = 0; i < 10; i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  CHECK(q.is_empty() == true);

  for (std::ptrdiff_t i = 0; i < 15; i++)
    q.push(static_cast<float>(i));

  CHECK(q.is_empty() == false);

  for (std::ptrdiff_t i = 0; i < 15; i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  CHECK(q.is_empty() == true);
}

TEST_CASE("Test QueueA [push() array] -> [copy] -> [top()-pop() array]") {
  QueueA q = QueueA();
  std::ptrdiff_t n = 15;

  for (std::ptrdiff_t i = 0; i < n; i++)
    q.push(static_cast<float>(i));

  QueueA q_copy = QueueA(q);

  CHECK(q_copy.is_empty() == false);

  for (std::ptrdiff_t i = 0; i < n; i++)
  {
    CHECK(std::fabs(q_copy.top() - static_cast<float>(i)) < 2 * eps);
    q_copy.pop();
  }

  CHECK(q_copy.is_empty() == true);
  CHECK(q.is_empty() == false);
}

TEST_CASE("Test QueueA [push() array] -> [copy] -> [top()-pop() array] with offset") {
  QueueA q = QueueA();

  for (std::ptrdiff_t i = 0; i < 12; i++)
    q.push(static_cast<float>(i));

  for (std::ptrdiff_t i = 0; i < 10; i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  for (std::ptrdiff_t i = 0; i < 10; i++)
    q.push(static_cast<float>(i));

  QueueA q_copy = QueueA(q);

  for (std::ptrdiff_t i = 10; i < 12; i++)
  {
    CHECK(std::fabs(q_copy.top() - static_cast<float>(i)) < 2 * eps);
    q_copy.pop();
  }

  for (std::ptrdiff_t i = 0; i < 10; i++)
  {
    CHECK(std::fabs(q_copy.top() - static_cast<float>(i)) < 2 * eps);
    q_copy.pop();
  }

  CHECK(q_copy.is_empty() == true);
  CHECK(q.is_empty() == false);
}

TEST_CASE("Test QueueA [push() array] -> [=] -> [top()-pop() array]") {
  QueueA q = QueueA();
  std::ptrdiff_t n = 15;

  for (std::ptrdiff_t i = 0; i < n; i++)
    q.push(static_cast<float>(i));

  QueueA q_new = QueueA();
  CHECK(q_new.is_empty() == true);

  q_new = q;
  CHECK(q_new.is_empty() == false);

  for (std::ptrdiff_t i = 0; i < n; i++)
  {
    CHECK(std::fabs(q_new.top() - static_cast<float>(i)) < 2 * eps);
    q_new.pop();
  }

  CHECK(q_new.is_empty() == true);
  CHECK(q.is_empty() == false);
}

TEST_CASE("Test QueueA [push() array] -> [=] -> [top()-pop() array] with offset") {
  QueueA q = QueueA();

  for (std::ptrdiff_t i = 0; i < 12; i++)
    q.push(static_cast<float>(i));

  for (std::ptrdiff_t i = 0; i < 10; i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  for (std::ptrdiff_t i = 0; i < 10; i++)
    q.push(static_cast<float>(i));

  QueueA q_new = QueueA();
  CHECK(q_new.is_empty() == true);

  q_new = q;
  CHECK(q_new.is_empty() == false);

  for (std::ptrdiff_t i = 10; i < 12; i++)
  {
    CHECK(std::fabs(q_new.top() - static_cast<float>(i)) < 2 * eps);
    q_new.pop();
  }

  for (std::ptrdiff_t i = 0; i < 10; i++)
  {
    CHECK(std::fabs(q_new.top() - static_cast<float>(i)) < 2 * eps);
    q_new.pop();
  }

  CHECK(q_new.is_empty() == true);
  CHECK(q.is_empty() == false);
}

TEST_CASE("Test QueueA [push() array] -> [top()-pop() array] & Relocation") {
  QueueA q = QueueA();
  std::ptrdiff_t mult = 7;
  std::ptrdiff_t n = 15 * mult;

  for (std::ptrdiff_t i = 0; i < n; i++)
    q.push(static_cast<float>(i));

  CHECK(q.is_empty() == false);

  for (std::ptrdiff_t i = 0; i < n; i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  CHECK(q.is_empty() == true);
}

TEST_CASE("Test QueueA [push() array] -> [top()-pop() array] with offset & Relocation") {
  QueueA q = QueueA();
  std::ptrdiff_t mult = 7;

  for (std::ptrdiff_t i = 0; i < (12 * mult); i++)
    q.push(static_cast<float>(i));

  for (std::ptrdiff_t i = 0; i < (10 * mult); i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  for (std::ptrdiff_t i = 0; i < (10 * mult); i++)
    q.push(static_cast<float>(i));

  for (std::ptrdiff_t i = (10 * mult); i < (12 * mult); i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  for (std::ptrdiff_t i = 0; i < (10 * mult); i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  CHECK(q.is_empty() == true);

  for (std::ptrdiff_t i = 0; i < (15 * mult); i++)
    q.push(static_cast<float>(i));

  CHECK(q.is_empty() == false);

  for (std::ptrdiff_t i = 0; i < (15 * mult); i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  CHECK(q.is_empty() == true);
}

TEST_CASE("Test QueueA [push() array] -> [copy] -> [top()-pop() array] & Relocation") {
  QueueA q = QueueA();
  std::ptrdiff_t mult = 9;
  std::ptrdiff_t n = 15 * mult;

  for (std::ptrdiff_t i = 0; i < n; i++)
    q.push(static_cast<float>(i));

  QueueA q_copy = QueueA(q);

  CHECK(q_copy.is_empty() == false);

  for (std::ptrdiff_t i = 0; i < n; i++)
  {
    CHECK(std::fabs(q_copy.top() - static_cast<float>(i)) < 2 * eps);
    q_copy.pop();
  }

  CHECK(q_copy.is_empty() == true);
  CHECK(q.is_empty() == false);
}

TEST_CASE("Test QueueA [push() array] -> [copy] -> [top()-pop() array] with offset & Relocation") {
  QueueA q = QueueA();
  std::ptrdiff_t mult = 5;

  for (std::ptrdiff_t i = 0; i < (12 * mult); i++)
    q.push(static_cast<float>(i));

  for (std::ptrdiff_t i = 0; i < (10 * mult); i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  for (std::ptrdiff_t i = 0; i < (10 * mult); i++)
    q.push(static_cast<float>(i));

  QueueA q_copy = QueueA(q);

  for (std::ptrdiff_t i = (10 * mult); i < (12 * mult); i++)
  {
    CHECK(std::fabs(q_copy.top() - static_cast<float>(i)) < 2 * eps);
    q_copy.pop();
  }

  for (std::ptrdiff_t i = 0; i < (10 * mult); i++)
  {
    CHECK(std::fabs(q_copy.top() - static_cast<float>(i)) < 2 * eps);
    q_copy.pop();
  }

  CHECK(q_copy.is_empty() == true);
  CHECK(q.is_empty() == false);
}

TEST_CASE("Test QueueA [push() array] -> [=] -> [top()-pop() array] & Relocation") {
  QueueA q = QueueA();
  std::ptrdiff_t mult = 8;
  std::ptrdiff_t n = 15 * mult;

  for (std::ptrdiff_t i = 0; i < n; i++)
    q.push(static_cast<float>(i));

  QueueA q_new = QueueA();
  CHECK(q_new.is_empty() == true);

  q_new = q;
  CHECK(q_new.is_empty() == false);

  for (std::ptrdiff_t i = 0; i < n; i++)
  {
    CHECK(std::fabs(q_new.top() - static_cast<float>(i)) < 2 * eps);
    q_new.pop();
  }

  CHECK(q_new.is_empty() == true);
  CHECK(q.is_empty() == false);
}

TEST_CASE("Test QueueA [push() array] -> [=] -> [top()-pop() array] with offset & Relocation") {
  QueueA q = QueueA();
  std::ptrdiff_t mult = 11;

  for (std::ptrdiff_t i = 0; i < (12 * mult); i++)
    q.push(static_cast<float>(i));

  for (std::ptrdiff_t i = 0; i < (10 * mult); i++)
  {
    CHECK(std::fabs(q.top() - static_cast<float>(i)) < 2 * eps);
    q.pop();
  }

  for (std::ptrdiff_t i = 0; i < (10 * mult); i++)
    q.push(static_cast<float>(i));

  QueueA q_new = QueueA();
  CHECK(q_new.is_empty() == true);

  q_new = q;
  CHECK(q_new.is_empty() == false);

  for (std::ptrdiff_t i = (10 * mult); i < (12 * mult); i++)
  {
    CHECK(std::fabs(q_new.top() - static_cast<float>(i)) < 2 * eps);
    q_new.pop();
  }

  for (std::ptrdiff_t i = 0; i < (10 * mult); i++)
  {
    CHECK(std::fabs(q_new.top() - static_cast<float>(i)) < 2 * eps);
    q_new.pop();
  }

  CHECK(q_new.is_empty() == true);
  CHECK(q.is_empty() == false);
}
#include "rational/rational.h"
#include <iostream>
#include <sstream>
using namespace std;

void TestConstructor()
{
  const int arr[] = { 2, 6, -2, -6, 9, -15 };
  for (int i = 0; i < 5; i += 2)
  {
    cout << "Putting " << arr[i] << " and " << arr[i + 1] << " Rational Number: " << Rational(arr[i], arr[i + 1]) << endl;
  }
  cout << "Putting " << -7 << " Rational Number: " << Rational(-7) << endl;
  cout << "Putting nothing "
    << "Rational Number: " << Rational() << endl;
  cout << "Copying constructor: "
    << "Rational(Rational(14, -2)): " << Rational(Rational(14, -2)) << endl;
  try
  {
    cout << "Putting 0 in denominator " << Rational(1, 0) << endl;
  }
  catch (std::invalid_argument& ex)
  {
    std::cout << "Exception caught with reason '" << ex.what() << "'\n";
  }
  cout << endl;
}
void TestSum(Rational lhs, const Rational rhs)
{
  cout << lhs << " + " << rhs << " = " << lhs + rhs << endl;
 // cout << 5 << " + " << rhs << " = " << 5 + rhs << endl;
 // cout << lhs << " + " << 5 << " = " << lhs + 5 << endl;
  Rational t(lhs);
  lhs += rhs;
  cout << t << " += " << rhs << " = " << lhs << endl;
 // lhs += 5 - rhs;
  cout << t << " += " << 5 << " = " << lhs << endl;

  cout << endl;
}
void TestDiv(Rational lhs, const Rational rhs)
{
  cout << lhs << " / " << rhs << " = " << lhs / rhs << endl;
  //cout << 5 << " / " << rhs << " = " << 5 / rhs << endl;
 /* try
  {
    cout << lhs << " / " << 0 << " = " << lhs / 0 << endl;
  }
  catch (std::invalid_argument& ex)
  {
    std::cout << "Exception caught with reason '" << ex.what() << "'\n";
  }*/
 // cout << lhs << " / " << 5 << " = " << lhs / 5 << endl;
  Rational t(lhs);
  lhs /= rhs;
  cout << t << " /= " << rhs << " = " << lhs << endl;
//  lhs /= 5 / rhs;
  cout << t << " /= " << 5 << " = " << lhs << endl;
  cout << endl;
}

void TestMul(Rational lhs, const Rational rhs)
{
  cout << lhs << " * " << rhs << " = " << lhs * rhs << endl;
 // cout << lhs << " * " << 5 << " = " << lhs * 5 << endl;
  //cout << 5 << " * " << rhs << " = " << 5 * rhs << endl;
  Rational t(lhs);
  lhs *= rhs;
  cout << t << " *= " << rhs << " = " << lhs << endl;
 // lhs *= 5 / rhs;
  cout << t << " *= " << 5 << " = " << lhs << endl;

  cout << endl;
}

void TestSub(Rational lhs, const Rational rhs)
{
  cout << lhs << " - " << rhs << " = " << lhs - rhs << endl;
 // cout << 5 << " - " << rhs << " = " << 5 - rhs << endl;
 // cout << lhs << " - " << 5 << " = " << lhs - 5 << endl;

  Rational t(lhs);
  lhs -= rhs;
  cout << t << " -= " << rhs << " = " << lhs << endl;
 // lhs -= 5 - rhs;
  cout << t << " -= " << 5 << " = " << lhs << endl;
  cout << endl;
}

template <typename T, typename U>
void TestComparison(const U& lhs, const T& rhs)
{
  if (lhs < rhs)
  {
    cout << lhs << " < " << rhs << endl;
  }
  if (lhs > rhs)
  {
    cout << lhs << " > " << rhs << endl;
  }
  if (lhs == rhs)
  {
    cout << lhs << " == " << rhs << endl;
  }
  if (lhs >= rhs)
  {
    cout << lhs << " >= " << rhs << endl;
  }
  if (lhs <= rhs)
  {
    cout << lhs << " <= " << rhs << endl;
  }
  if (lhs != rhs)
  {
    cout << lhs << " != " << rhs << endl;
  }
  cout << endl;
}
bool TestParse(const string& str)
{
  istringstream istrm(str);
  Rational z;
  istrm >> z;
  if (istrm.good())
  {
    cout << "Read success: " << str << " -> " << z << std::endl;
  }
  else
  {
    cout << "Read error : " << str << " -> " << z << std::endl;
  }
  return istrm.good();
}
int main()
{
  TestConstructor();
  Rational arr[4] = {
      Rational(-1, 6),
      Rational(2, -6),
  };

  TestSum(arr[0], arr[1]);
  TestSub(arr[0], arr[1]);
  TestDiv(arr[0], arr[1]);
  TestMul(arr[0], arr[1]);

  TestComparison(arr[0], arr[1]);
  TestComparison(arr[0], 1);
  TestComparison(2, arr[1]);
  TestComparison(arr[0], arr[0]);
  TestParse("(3 / 2");
  TestParse("(3/ 2)");
  TestParse("(3/2)");
  return 0;
}
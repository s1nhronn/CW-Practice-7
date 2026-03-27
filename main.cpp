#include <iostream>
#include <stdexcept>
#include "top-it-vector.hpp"

bool testDefaultVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testVectorWithValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return !v.isEmpty();
}

bool testElementAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  return v[0] == 1 && v[1] == 2;
}

bool testElementConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  const topit::Vector< int >& rv = v;
  return rv[0] == 1 && rv[1] == 2;
}

bool testElementOutOfBoundCheckedAccess()
{
  topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range&)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementInboundCheckedAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try
  {
    int& val = v.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementOutOfBoundCheckedConstAccess()
{
  const topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch (const std::out_of_range&)
  {
    return true;
  }
  catch (...)
  {
    return false;
  }
}

bool testElementInboundCheckedConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int >& rv = v;
  try
  {
    const int& val = rv.at(0);
    return val == 1;
  }
  catch (...)
  {
    return false;
  }
}

bool testCopyConstructor()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav = v;
  bool isAllEqual = v.getSize() == yav.getSize();
  for (size_t i = 0; isAllEqual && i < v.getSize(); ++i)
  {
    isAllEqual = isAllEqual && (v[i] == yav[i]);
  }
  return isAllEqual;
}

bool testSwap()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > r;
  r.pushBack(2);
  v.swap(r);
  return r[0] == 1 && v[0] == 2;
}

bool testPushFront()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushFront(3);
  return v[0] == 3 && v[1] == 1 && v[2] == 2;
}

bool testDoublePushFront()
{
  topit::Vector< int > v;
  v.pushFront(1);
  v.pushFront(2);
  return v[0] == 2 && v[1] == 1;
}

bool testCapacityOfEmpty()
{
  topit::Vector< int > v;
  return !v.getCapacity();
}

bool testCapacityWithValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return v.getCapacity() == 1;
}

bool testCapacityWithMoreValues()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  return v.getCapacity() == 4;
}

bool testSizeOFEmpty()
{
  topit::Vector< int > v;
  return !v.getSize();
}

bool testSizeWithValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  return v.getSize() == 1;
}

bool testPopBackWithEmptyVector()
{
  topit::Vector< int > v;
  try
  {
    v.popBack();
  }
  catch (const std::out_of_range&)
  {
    return true;
  }
  return false;
}

bool testPopBackWithOneValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.popBack();
  return v.isEmpty();
}

bool testPopBackWithMoreValues()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.popBack();
  return v.getSize() == 2 && v[0] == 1 && v[1] == 2;
}

bool testPopFrontWithEmptyVector()
{
  topit::Vector< int > v;
  try
  {
    v.popFront();
    return false;
  }
  catch (const std::out_of_range&)
  {
    return true;
  }
}

bool testPopFrontWithOneValue()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.popFront();
  return v.isEmpty();
}

bool testPopFrontWithMoreValues()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.popFront();
  return v[0] == 2 && v[1] == 3;
}

bool testInsertValueInEmptyVector()
{
  topit::Vector< int > v;
  v.insert(0, 1);
  return !v.isEmpty() && v[0] == 1;
}

bool testInsertValueInVectorWithOneValue()
{
  topit::Vector< int > v;
  v.pushBack(2);
  v.insert(0, 1);
  v.insert(1, 3);
  return v[0] == 1 && v[1] == 2 && v[2] == 3;
}

bool testInsertValueInVectorWithManyValues()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  v.insert(1, 4);
  return v[0] == 1 && v[1] == 4 && v[2] == 2 && v[3] == 3;
}

bool testInsertValueOutOfRange()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.pushBack(3);
  try
  {
    v.insert(10, 1);
    return false;
  }
  catch (const std::out_of_range&)
  {
    return true;
  }
}

int main()
{
  using test_t = bool (*)();
  using pair_t = std::pair< const char*, test_t >;
  pair_t tests[] = {
      {"Default vector should be empty", testDefaultVector},
      {"Vector with any value is not empty", testVectorWithValue},
      {"Inbound access elements", testElementAccess},
      {"Sizes must be equal as elements", testCopyConstructor},
      {"The data is valid when swapping places", testSwap},
      {"The element should be added to the beginning", testPushFront},
      {"Correctly adding two elements to the beginning", testDoublePushFront},
      {"Capacity of the empty vector is 0", testCapacityOfEmpty},
      {"Capacity of a non-empty vector is correct", testCapacityWithValue},
      {"Size of the empty vector is 0", testSizeOFEmpty},
      {"Size of a non-empty vector is correct", testSizeWithValue},
      {"Deleting from an empty vector generates a certain exception (popBack)", testPopBackWithEmptyVector},
      {"Deleting a vector with one value makes it empty (popBack)", testPopBackWithOneValue},
      {"Deleting from a vector reduces its size and keeps the data correct (popBack)", testPopBackWithMoreValues},
      {"Deleting from an empty vector generates a certain exception (popFront)", testPopFrontWithEmptyVector},
      {"Deleting a vector with one value makes it empty (popFront)", testPopFrontWithOneValue},
      {"Deleting from a vector reduces its size and keeps the data correct (popFront)", testPopFrontWithMoreValues},
      {"The correct expansion of the array capacity by 2 times is expected", testCapacityWithMoreValues},
      {"If an element exists, it returns the correct answer in a const vector", testElementInboundCheckedConstAccess},
      {"at(0) will throw an exception for an empty const vector", testElementOutOfBoundCheckedConstAccess},
      {"If an element exists, it returns the correct answer", testElementInboundCheckedAccess},
      {"at(0) will throw an exception for an empty vector", testElementOutOfBoundCheckedAccess},
      {"Inbound access elements in const vector", testElementConstAccess},
      {"Inserting into an empty vector", testInsertValueInEmptyVector},
      {"Inserting at the beginning and end of a vector with a single value", testInsertValueInVectorWithOneValue},
      {"Insertion into the vector", testInsertValueInVectorWithManyValues},
      {"Inserting an element outside the border throws an exception", testInsertValueOutOfRange}};
  const size_t count = sizeof(tests) / sizeof(pair_t);
  std::cout << std::boolalpha;
  bool pass = true;
  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << res << ": ";
    std::cout << tests[i].first << '\n';
    pass = pass && res;
  }
  std::cout << pass;
  std::cout << ": RESULT\n";
}

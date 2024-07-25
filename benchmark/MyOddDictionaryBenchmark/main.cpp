// Licensed to Florent Guelfucci under one or more agreements.
// Florent Guelfucci licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.
#include <algorithm>
#include <iostream>
#include <map>
#include <unordered_map>
#include <random>
#include <vector>
#include "helper.h"

std::unordered_map<std::string, int> shuffle_data(std::unordered_map<std::string, int>& src)
{
  std::vector<std::pair<std::string, int>> elements(src.begin(), src.end());

  // Shuffle the vector
  std::shuffle(elements.begin(), elements.end(), std::mt19937{ std::random_device{}() });

  std::unordered_map<std::string, int> data;
  for (const auto& element : elements) {
    data[element.first] = element.second;
  }
  return data;
}

std::unordered_map<std::string, int> create_data(int number_of_items)
{
  Helper h;
  h.start();
  std::unordered_map<std::string, int> data;
  for (auto i = 0; i < number_of_items; ++i)
  {
    data[h.generateRandomString(10)] = h.generateRandomNumber(0, 10);
  }

  std::cout << "Create " << number_of_items << " items took " << h.end() << " seconds!\n";
  return data;
}

double test_maps(std::unordered_map<std::string, int>& data)
{
  std::cout << "Map\n";
  Helper h;

  // make a copy
  h.start();
  auto copy = std::map<std::string, int>();
  for (auto d : data)
  {
    copy[d.first] = d.second;
  }
  //std::cout << "Map copy took " << h.end() << " seconds!\n";
  
  h.start();
  for (auto d : data)
  {
    h.start_single_event();
    auto y = copy.find(d.first);
    if (y == copy.end())
    {
      std::cout << "  Key " << d.first << " does not match\n";
    }
    h.end_single_event();
  }

  auto average = h.end();
  std::cout << "  Map find took " << average << " seconds!\n";
  std::cout << "  Average " << h.events_average_nanoseconds() << " nanoseconds per events!\n";
  return h.end();
}

double test_unordered_maps(std::unordered_map<std::string, int>& src)
{
  std::cout << "Unordered ma\n";
  Helper h;

  // to be fair we have to shuffle the map
  auto data = shuffle_data(src);

  // make a copy
  h.start();
  auto copy = std::unordered_map<std::string, int>(data);

  h.start();
  for (auto d : data)
  {
    h.start_single_event();
    auto y = copy.find(d.first);
    if (y == copy.end())
    {
      std::cout << "  Key " << d.first << " does not match\n";
    }
    h.end_single_event();
  }

  auto average = h.end();
  std::cout << "  Unordered Map find took " << average << " seconds!\n";
  std::cout << "  Average " << h.events_average_nanoseconds() << " nanoseconds per events!\n";
  return h.end();
}

double test_vectors(std::unordered_map<std::string, int>& data)
{
  std::cout << "Vector\n";
  Helper h;
  struct Data
  {
    std::string key;
    int value;
  };

  // make a copy
  h.start();
  auto copy = std::vector<Data>();
  for (auto d : data)
  {
    copy.push_back(Data{ d.first, d.second });
  }

  h.start();
  for (auto d : data)
  {
    h.start_single_event();
    auto y = std::find_if(copy.begin(), copy.end(), [&](Data& elem)
      {
        return elem.key == d.first;
      });
    if (y == copy.end())
    {
      std::cout << "  Key " << d.first << " does not match\n";
    }
    h.end_single_event();
  }

  auto average = h.end();
  std::cout << "  Vector find took " << average << " seconds!\n";
  std::cout << "  Average " << h.events_average_nanoseconds() << " nanoseconds per events!\n";
  return h.end();
}

/// <summary>
/// Compare the speed of various containers.
/// </summary>
/// <returns></returns>
int main()
{
  const int number_of_items = 100000;

  auto data = create_data(number_of_items);

  // test with maps
  test_maps(data);
  test_unordered_maps(data);

  // test with vectors
  test_vectors(data);

  std::cout << "Benchmark tests complete!\n";
}

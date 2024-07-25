// Licensed to Florent Guelfucci under one or more agreements.
// Florent Guelfucci licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.
#include <iostream>
#include <map>
#include <unordered_map>
#include "helper.h"

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
      std::cout << "Key " << d.first << " does not match\n";
    }
    h.end_single_event();
  }

  auto average = h.end();
  std::cout << "Map find took " << average << " seconds!\n";
  std::cout << "Average " << h.events_average_nanoseconds() << " nanoseconds per events!\n";
  return h.end();
}

double test_unordered_maps(std::unordered_map<std::string, int>& data)
{
  Helper h;

  // make a copy
  h.start();
  auto copy = std::unordered_map<std::string, int>(data);
  //std::cout << "Unordered Map copy took " << h.end() << " seconds!\n";

  h.start();
  for (auto d : data)
  {
    h.start_single_event();
    auto y = copy.find(d.first);
    if (y == copy.end())
    {
      std::cout << "Key " << d.first << " does not match\n";
    }
    h.end_single_event();
  }

  auto average = h.end();
  std::cout << "Unordered Map find took " << average << " seconds!\n";
  std::cout << "Average " << h.events_average_nanoseconds() << " nanoseconds per events!\n";
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

  std::cout << "Benchmark tests complete!\n";
}

// Licensed to Florent Guelfucci under one or more agreements.
// Florent Guelfucci licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.
#include "helper.h"
#include <random>
#include <chrono>

void Helper::start()
{
  // Get the start time
  _start = std::chrono::high_resolution_clock::now();
}

double Helper::end() const
{
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> duration = end - _start;
  return duration.count();
}

std::string Helper::generateRandomString(size_t length) const
{
  const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::random_device rd;
  std::mt19937 generator(rd());
  std::uniform_int_distribution<> distribution(0, characters.size() - 1);

  std::string randomString;
  for (size_t i = 0; i < length; ++i) {
    randomString += characters[distribution(generator)];
  }
  return randomString;
}

int Helper::generateRandomNumber(int min, int max) const
{
  std::random_device rd; // Seed for the random number generator
  std::mt19937 generator(rd()); // Mersenne Twister random number generator
  std::uniform_int_distribution<> distribution(min, max); // Uniform distribution within [min, max]

  return distribution(generator);
}

void Helper::start_single_event()
{
  _event_start = std::chrono::high_resolution_clock::now();
}

void Helper::end_single_event()
{
  auto end = std::chrono::high_resolution_clock::now();
  
  auto duration = std::chrono::duration_cast<std::chrono::duration<long double, std::ratio<1, std::chrono::high_resolution_clock::period::den>>>(end - _start).count();

  _running_average.add(duration); // Add the duration;
}

double Helper::events_average_nanoseconds() const
{
  auto ticks = _running_average.get_average();
  return ticks * std::chrono::high_resolution_clock::period::num / std::chrono::high_resolution_clock::period::den;
}
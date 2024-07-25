// Licensed to Florent Guelfucci under one or more agreements.
// Florent Guelfucci licenses this file to you under the MIT license.
// See the LICENSE file in the project root for more information.
#pragma once
#include <chrono>
#include <string>

class RunningAverage {
public:
  RunningAverage() : _average(0.0), _count(0) {}

  void add(long double time) {
    _count++;
    _average += (time - _average) / _count;
  }

  long double get_average() const {
    return _average;
  }

private:
  long double _average;
  int _count;
};

class Helper
{
public:
  std::string generateRandomString(size_t length) const;
  int generateRandomNumber(int min, int max) const;

  void start();
  double end() const;

  void start_single_event();
  void end_single_event();

  double events_average_nanoseconds() const;

private:
  std::chrono::time_point<std::chrono::steady_clock> _start;
  std::chrono::time_point<std::chrono::steady_clock> _event_start;
  RunningAverage _running_average;
};


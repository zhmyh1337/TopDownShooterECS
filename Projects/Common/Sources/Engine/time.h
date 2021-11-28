#pragma once
#include <chrono>
#include <assert.h>
#include "common.h"

using time_point = std::chrono::high_resolution_clock::time_point;
using time_delta = std::chrono::duration<float, std::milli>;

struct Time
{
private:
  time_point startTime, milliseconds;
  time_delta millisecondDelta;
  float seconds;
  float secondDelta;
public:
  inline static Time* timer;
  Time():startTime(std::chrono::high_resolution_clock::now()), milliseconds(startTime),
  millisecondDelta(0), seconds(0), secondDelta(0)
  {
    assert(timer == nullptr);
    timer = this;
  }
  ~Time()
  {
    assert(timer != nullptr);
    timer = nullptr;
  }
  void update()
  {
    time_point millisecondsNew = std::chrono::high_resolution_clock::now();
    millisecondDelta = duration_cast<std::chrono::duration<float>>(millisecondsNew - milliseconds);
    milliseconds = millisecondsNew;
    seconds = duration_cast<std::chrono::duration<float>>(milliseconds - startTime).count() * 0.001f;
    secondDelta = millisecondDelta.count() * 0.001f;
  }
  static float time()
  { 
    return timer->seconds;
  }
  static float delta_time()
  {
    return timer->secondDelta;
  }
  static float udelta_time()
  {
    return timer->millisecondDelta.count();
  }
  static float fps()
  {
    const int N  = 60;
    static float s[N] = {};
    static float sum = 0;
    static int k = 0;
    float t = timer->millisecondDelta.count();

    sum -= s[k];
    s[k] = t;
    sum += t; 
    k = (k + 1) % N;
    return 1000.f  * N / sum;
  }
};
class TimeScope
{
private:
  time_point start;
  const char *message;
  bool stopped;
public:
  TimeScope(const char *message):
    start(std::chrono::high_resolution_clock::now()), message(message), stopped(false)
  { }
  void stop()
  {
    time_point end = std::chrono::high_resolution_clock::now();
    time_delta delta = end - start;
    debug_log("%s\nspend %f seconds", message, delta * 0.001f);
    stopped = true;
  }
  ~TimeScope()
  {
    if (!stopped)
      stop();
  }
};

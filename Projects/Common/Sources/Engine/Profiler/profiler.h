#pragma once
#include "Engine/time.h"
#include <vector>
#include <map>
class ProfilerLabel
{
private:
  time_point start; 
  const string label;
  bool stopped;
public:
  ProfilerLabel(const string &label);
  ~ProfilerLabel();
  void stop();
};

struct TimeLabel {time_point time; string label; bool open;};
class Profiler
{
private:
  struct AverangeTime 
  {
    vector<float> dtChain;
    int curIndex;
    float curSum;
    AverangeTime();
    float get_averange() const;
    void add_time(float dt);
  };

  map<string, AverangeTime> labelAveranges;
  vector<TimeLabel> prev_frame_labels, cur_frame_labels;
public:
  void start_frame();
  void end_frame();
  void open_label(time_point start, const string &label);
  void close_label(time_point start, time_point end, const string &label);
  float get_averange(const string &label);
  const vector<TimeLabel> &get_frame_history();
};

Profiler &get_profiler();
#define PROFILER(label) ProfilerLabel label(#label);
#include "profiler.h"

ProfilerLabel::ProfilerLabel(const string &label):
 start(std::chrono::high_resolution_clock::now()), label(label), stopped(false)
{
  get_profiler().open_label(start, label);
}
void ProfilerLabel::stop()
{
  get_profiler().close_label(start, std::chrono::high_resolution_clock::now(), label);
  stopped = true;
}
ProfilerLabel::~ProfilerLabel()
{
  if (!stopped)
    stop();
}

void Profiler::start_frame()
{
  prev_frame_labels = std::move(cur_frame_labels);
  cur_frame_labels.clear();
}
void Profiler::end_frame()
{

}
void Profiler::open_label(time_point start, const string &label)
{
  cur_frame_labels.push_back({start, label, true});
}
void Profiler::close_label(time_point start, time_point end, const string &label)
{
  cur_frame_labels.push_back({end, label, false});
  labelAveranges[label].add_time(time_delta(end - start).count());
}
float Profiler::get_averange(const string &label)
{
  return labelAveranges[label].get_averange();
}
const vector<TimeLabel> &Profiler::get_frame_history()
{
  return prev_frame_labels;
}

Profiler &get_profiler()
{
  static Profiler profiler;
  return profiler;
}

constexpr int framesCount = 60;

Profiler::AverangeTime::AverangeTime():dtChain(framesCount, 0.0f), curIndex(0), curSum(0){}

float Profiler::AverangeTime::get_averange() const
{
  return curSum / framesCount;
}
void Profiler::AverangeTime::add_time(float dt)
{
  curSum += -dtChain[curIndex] + dt;
  dtChain[curIndex] = dt;
  curIndex = (curIndex + 1) % framesCount;
}

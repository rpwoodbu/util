#ifndef __UTIL_CLOCK_H__
#define __UTIL_CLOCK_H__

#include "absl/time/clock.h"

namespace util::time {

class Clock {
 public:
  virtual ~Clock() = default;

  virtual absl::Time Now() = 0;

  bool IsTimeBetween(int start_hour, int end_hour);
};

class SystemClock : public Clock {
 public:
  ~SystemClock() override = default;

  // Get the singleton SystemClock.
  static Clock* Get() { return &clock; }

  absl::Time Now() override {
    return absl::Now();
  }

 private:
  SystemClock() = default;

  static class SystemClock clock;
};

}  // namespace util::time

#endif  // __UTIL_CLOCK_H__

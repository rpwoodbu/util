#ifndef __UTIL_CLOCK_H__
#define __UTIL_CLOCK_H__

#include "absl/time/clock.h"

namespace util::time {

class Clock {
 public:
  virtual absl::Time Now() const = 0;
  bool IsTimeBetween(int start_hour, int end_hour) const;
};

class SystemClock : public Clock {
 public:
  // Get the singleton SystemClock.
  static Clock& Get() { return clock; }

  absl::Time Now() const override {
    return absl::Now();
  }

 private:
  SystemClock() = default;

  static class SystemClock clock;
};

//
Clock& SystemClock();

}  // namespace util::time

#endif  // __UTIL_CLOCK_H__

#ifndef __UTIL_TIME_PERIOD_H__
#define __UTIL_TIME_PERIOD_H__

#include "absl/time/time.h"
#include "util/time/clock.h"

namespace util::time {

class Period {
 public:
  Period(absl::Duration period, Clock* clock)
      : period_(period), clock_(clock) {}
  Period(absl::Duration period)
      : Period(period, SystemClock::Get()) {}

  void WaitForNext();

 private:
  const absl::Duration period_;
  Clock* const clock_;
  absl::Time last_;
};

}  // namespce util::time

#endif  // __UTIL_TIME_PERIOD_H__

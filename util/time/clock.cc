#include "util/time/clock.h"

namespace util::time {

class SystemClock SystemClock::clock;

bool Clock::IsTimeBetween(int start_hour, int end_hour) {
  const auto now = Now();
  const auto local_time = absl::ToCivilHour(now, absl::LocalTimeZone());
  auto hour = local_time.hour();
  // In order to determine if the time is between two hours that wrap around
  // midnight, extend the number of hours past 24 so that the end hour is
  // always greater than the start hour.
  if (end_hour < start_hour) {
    end_hour += 24;
    if (hour < start_hour) {
      hour += 24;
    }
  }

  return hour >= start_hour && hour < end_hour;
}

}  // namespace util::time

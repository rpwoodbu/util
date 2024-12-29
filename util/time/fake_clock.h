#ifndef __UTIL_FAKE_CLOCK_H__
#define __UTIL_FAKE_CLOCK_H__

#include "absl/time/civil_time.h"
#include "absl/time/time.h"

#include "util/time/clock.h"

namespace util::time {

class FakeClock : public Clock {
 public:
  FakeClock() = default;
  explicit FakeClock(absl::Time now) : now_(std::move(now)) {}
  ~FakeClock() = default;

  void Set(absl::Time now) {
    now_ = std::move(now);
  }

  void Advance(absl::Duration duration) {
    now_ += duration;
  }

  absl::Time Now() const override {
    return now_;
  }

 private:
  absl::Time now_;
};

}  // namespace util::time

#endif  // __UTIL_FAKE_CLOCK_H__

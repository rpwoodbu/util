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
  ~FakeClock() override = default;

  void Set(absl::Time now) {
    now_ = std::move(now);
  }

  void Advance(absl::Duration duration) {
    now_ += duration;
  }

  // Advance by this much in each call to `Now()`.
  void AdvanceOnNow(absl::Duration duration) {
    advance_ = duration;
  }

  absl::Time Now() override {
    now_ += advance_;
    return now_;
  }

 private:
  absl::Time now_;
  absl::Duration advance_;
};

}  // namespace util::time

#endif  // __UTIL_FAKE_CLOCK_H__

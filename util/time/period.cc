#include <unistd.h>

#include "absl/time/time.h"
#include "util/time/period.h"

namespace util::time {

void Period::WaitForNext() {
  absl::Time now = clock_->Now();

  if (now - last_ > period_ * 2) {
    // We have overrun the period significantly. Drop missed iterations.
    last_ = now - period_;
  }

  // `usleep()` may return early, so loop until `period_` has truly elapsed.
  while (now - last_ < period_) {
    usleep((last_ + period_ - now) / absl::Microseconds(1));
    now = clock_->Now();
  }
  last_ += period_;
}

}  // namespce util::time

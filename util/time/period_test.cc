#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "absl/time/time.h"
#include "util/time/fake_clock.h"
#include "util/time/period.h"

namespace util::time {
namespace {

TEST(Period, Basic) {
  FakeClock clock;
  Period period(absl::Milliseconds(10), &clock);

  const auto then = clock.Now();
  clock.AdvanceOnNow(absl::Milliseconds(10));
  period.WaitForNext();
  clock.AdvanceOnNow(absl::ZeroDuration());
  EXPECT_EQ(clock.Now() - then, absl::Milliseconds(10));
}

TEST(Period, IncompleteSleeps) {
  FakeClock clock;
  Period period(absl::Milliseconds(10), &clock);
  const auto then = clock.Now();

  // Only advance the clock a fraction of the desired interval to simulate a
  // `usleep()` which returns early (perhaps due to a signal).
  clock.AdvanceOnNow(absl::Milliseconds(1));
  period.WaitForNext();
  clock.AdvanceOnNow(absl::ZeroDuration());
  const auto now = clock.Now();
  EXPECT_EQ(now - then, absl::Milliseconds(10));
}

TEST(Period, AccountForWork) {
  FakeClock clock;
  Period period(absl::Milliseconds(10), &clock);
  const auto then = clock.Now();

  clock.AdvanceOnNow(absl::Milliseconds(1));
  period.WaitForNext();
  clock.AdvanceOnNow(absl::ZeroDuration());
  {
    const auto now = clock.Now();
    EXPECT_EQ(now - then, absl::Milliseconds(10));
  }

  // Advance the clock a bit to account for "work" being done between
  // intervals.
  clock.Advance(absl::Milliseconds(5));

  clock.AdvanceOnNow(absl::Milliseconds(1));
  period.WaitForNext();
  clock.AdvanceOnNow(absl::ZeroDuration());
  {
    const auto now = clock.Now();
    EXPECT_EQ(now - then, absl::Milliseconds(20));
  }
}

TEST(Period, Overrun) {
  FakeClock clock;
  Period period(absl::Milliseconds(10), &clock);

  // Prime the pump.
  {
    const auto then = clock.Now();
    clock.AdvanceOnNow(absl::Milliseconds(10));
    period.WaitForNext();
    clock.AdvanceOnNow(absl::ZeroDuration());
    const auto now = clock.Now();
    EXPECT_EQ(now - then, absl::Milliseconds(10));
  }

  // Simulate significant overrun.
  clock.Advance(absl::Seconds(1));

  {
    const auto then = clock.Now();
    clock.AdvanceOnNow(absl::Milliseconds(1));
    period.WaitForNext();
    clock.AdvanceOnNow(absl::ZeroDuration());
    const auto now = clock.Now();
    // Only expect a single access to `Clock::Now()` as we need to execute
    // immediately.
    EXPECT_EQ(now - then, absl::Milliseconds(1));
  }
}

// Exercises the code with the system clock. This ensures that the `usleep()`
// call is working. Use of timing-based testing is limited to this one test,
// and flakiness is avoided by not asserting on an upper time bound.
TEST(Period, RealTime) {
  Clock& clock = *SystemClock::Get();
  Period period(absl::Milliseconds(10));
  const auto then = clock.Now();

  // The first one will fire immediately.
  period.WaitForNext();
  // This one should wait for the period to elapse.
  period.WaitForNext();
  // All we can really assert is that the time passed is more than the desired
  // interval. It could be arbitrarily more depending on interfering system
  // behaviors.
  EXPECT_GT(clock.Now() - then, absl::Milliseconds(10));
}

}  // anonymous namespace
}  // namespace util::time

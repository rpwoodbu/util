#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "absl/time/time.h"
#include "util/time/fake_clock.h"

namespace util {
namespace {

using testing::IsFalse;
using testing::IsTrue;

TEST(IsTimeBetween, Basic) {
  util::FakeClock clock;

  clock.Set(absl::FromCivil(absl::CivilHour(1955, 11, 5, 0), absl::LocalTimeZone()));
  EXPECT_THAT(clock.IsTimeBetween(1, 2), IsFalse());

  clock.Advance(absl::Hours(1));
  EXPECT_THAT(clock.IsTimeBetween(1, 2), IsTrue());

  clock.Advance(absl::Hours(1));
  EXPECT_THAT(clock.IsTimeBetween(1, 2), IsFalse());
}

TEST(IsTimeBetween, Wrapped) {
  util::FakeClock clock;
  clock.Set(absl::FromCivil(absl::CivilHour(1955, 11, 5, 0), absl::LocalTimeZone()));
  EXPECT_THAT(clock.IsTimeBetween(23, 1), IsTrue());

  clock.Advance(absl::Hours(1));
  EXPECT_THAT(clock.IsTimeBetween(23, 1), IsFalse());
}

}  // anonymous namespace
}  // namespace util

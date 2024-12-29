cc_library(
    name = "clock",
    srcs = ["clock.cc"],
    hdrs = ["clock.h"],
    deps = ["@absl//absl/time"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "fake_clock",
    hdrs = ["fake_clock.h"],
    deps = [
        ":clock",
        "@absl//absl/time",
    ],
    testonly = True,
    visibility = ["//visibility:public"],
)

cc_test(
    name = "clock_test",
    srcs = ["clock_test.cc"],
    deps = [
        ":clock",
        ":fake_clock",
        "@absl//absl/time",
        "@googletest//:gtest_main",
    ],
)

cc_library(
    name = "period",
    srcs = ["period.cc"],
    hdrs = ["period.h"],
    deps = [
        ":clock",
        "@absl//absl/time",
    ],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "period_test",
    srcs = ["period_test.cc"],
    deps = [
        ":period",
        ":fake_clock",
        "@absl//absl/time",
        "@googletest//:gtest_main",
    ],
)

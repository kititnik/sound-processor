#include <catch2/catch_all.hpp>
#include "waveform.hpp"
#include "filters/ampl_filter.hpp"
#include "filters/normalize_filter.hpp"
#include "filters/silence_filter.hpp"
#include "filters/lowpass_filter.hpp"
#include "filters/timestretch_filter.hpp"

TEST_CASE("AmplFilter factor 1.0 no change", "AmplFilter") {
    Waveform w({1, 3});
    AmplFilter f(1.0);
    f.apply(&w);
    REQUIRE(w.getSample(0) == 1);
    REQUIRE(w.getSample(1) == 3);
}

TEST_CASE("AmplFilter factor 0.0 zeroes samples", "AmplFilter") {
    Waveform w({1, 3});
    AmplFilter f(0.0);
    f.apply(&w);
    REQUIRE(w.getSample(0) == 0);
    REQUIRE(w.getSample(1) == 0);
}

TEST_CASE("NormalizeFilter on zeros don't change", "NormalizeFilter") {
    Waveform w({0, 0, 0});
    NormalizeFilter f(1.0);
    f.apply(&w);
    REQUIRE(w.getSample(0) == 0);
}

TEST_CASE("SilenceFilter inserts zeros", "SilenceFilter") {
    Waveform w({1000, 1000, 1000});
    SilenceFilter f("ms", 0.0, 100.0);
    f.apply(&w);
    REQUIRE(w.size() == 3 + Waveform::msToSamples(100.0));
    REQUIRE(w.getSample(0) == 0);
    REQUIRE(w.getSample(Waveform::msToSamples(100.0) - 1) == 0);
}

TEST_CASE("SilenceFilter unknown unit throws error", "SilenceFilter") {
    Waveform w({1000});
    SilenceFilter f("non-unit", 0.0, 1.0);
    REQUIRE_THROWS(f.apply(&w));
}

TEST_CASE("LowpassFilter with window size 1 don't change", "LowpassFilter") {
    Waveform w({100, 200, 300});
    LowpassFilter f(1);
    f.apply(&w);
    REQUIRE(w.getSample(0) == 100);
    REQUIRE(w.getSample(1) == 200);
    REQUIRE(w.getSample(2) == 300);
}

TEST_CASE("TimestretchFilter factor 1.0 don't change", "TimestretchFilter") {
    Waveform w({100, 200, 300});
    TimestretchFilter f(1.0);
    f.apply(&w);
    REQUIRE(w.size() == 3);
    REQUIRE(w.getSample(0) == 100);
    REQUIRE(w.getSample(1) == 200);
    REQUIRE(w.getSample(2) == 300);
}

TEST_CASE("TimestretchFilter factor 2.0 doubles size", "TimestretchFilter") {
    Waveform w({100, 200});
    TimestretchFilter f(2.0);
    f.apply(&w);
    REQUIRE(w.size() == 4);
}

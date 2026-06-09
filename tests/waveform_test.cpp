#include <catch2/catch_all.hpp>
#include "waveform.hpp"

TEST_CASE("Waveform size", "Waveform") {
    Waveform w({1, 2, 3});
    REQUIRE(w.size() == 3);
}

TEST_CASE("Waveform getSample", "Waveform") {
    Waveform w({10, 20, 30});
    REQUIRE(w.getSample(0) == 10);
    REQUIRE(w.getSample(1) == 20);
    REQUIRE(w.getSample(2) == 30);
}

TEST_CASE("Waveform insert", "Waveform") {
    Waveform w({1, 2, 3});
    w.insert(1, 2, 0);
    REQUIRE(w.size() == 5);
    REQUIRE(w.getSample(0) == 1);
    REQUIRE(w.getSample(1) == 0);
    REQUIRE(w.getSample(2) == 0);
    REQUIRE(w.getSample(3) == 2);
}

TEST_CASE("Waveform secToSamples", "Waveform") {
    REQUIRE(Waveform::secToSamples(1.0) == 44100);
}

TEST_CASE("Waveform samplesToMs", "Waveform") {
    REQUIRE(Waveform::samplesToMs(44100) == Catch::Approx(1000.0));
}

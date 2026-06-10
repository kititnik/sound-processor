#include "filters/ampl_filter.hpp"
#include "pipeline.hpp"
#include "waveform.hpp"
#include <catch2/catch_all.hpp>
#include <memory>

TEST_CASE("Pipeline applies filter", "Pipeline") {
    Waveform w({1, 2});
    Pipeline pipeline;
    pipeline.addFilter(std::make_unique<AmplFilter>(0.0));
    pipeline.apply(&w);
    REQUIRE(w.getSample(0) == 0);
    REQUIRE(w.getSample(1) == 0);
}

#include "wav_reader.hpp"
#include "wav_writer.hpp"
#include "waveform.hpp"
#include <catch2/catch_all.hpp>
#include <sstream>

TEST_CASE("WavWriter/WavReader round-trip", "WavReader") {
    Waveform original({1, 2, 3, 4});

    std::ostringstream oss;
    WavWriter writer;
    writer.write(oss, original);

    std::istringstream iss(oss.str());
    WavReader reader;
    Waveform result = reader.read(iss);

    REQUIRE(result.size() == original.size());
    for(size_t i = 0; i < original.size(); i++) {
        REQUIRE(result.getSample(i) == original.getSample(i));
    }
}

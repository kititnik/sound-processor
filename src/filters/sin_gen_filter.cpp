#include "filters/sin_gen_filter.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>

SinGenFilter::SinGenFilter(double frequencyHz, double durationMs)
    : AbstractGeneratorFilter(durationMs), _frequencyHz(frequencyHz) {}

int16_t SinGenFilter::computeSample(double sampleSec) const {
    double value =
        32767.0 * std::sin(2.0 * std::numbers::pi * _frequencyHz * sampleSec);
    return static_cast<int16_t>(std::clamp(
        value, static_cast<double>(std::numeric_limits<int16_t>::min()),
        static_cast<double>(std::numeric_limits<int16_t>::max())));
}

#include "filters/am_sin_gen_filter.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>

AmSinGenFilter::AmSinGenFilter(double amplitude, double carrierHz,
                               double modulationHz, double depth,
                               double durationMs)
    : AbstractGeneratorFilter<AmSinGenFilter>(durationMs), _amplitude(amplitude),
      _carrierHz(carrierHz), _modulationHz(modulationHz), _depth(depth) {}

int16_t AmSinGenFilter::computeSample(double sampleSec) const {
    double envelope = 1.0 + _depth * std::sin(2.0 * std::numbers::pi *
                                              _modulationHz * sampleSec);
    double carrier = std::sin(2.0 * std::numbers::pi * _carrierHz * sampleSec);
    double value = _amplitude * 32767.0 * envelope * carrier;
    return static_cast<int16_t>(std::clamp(
        value, static_cast<double>(std::numeric_limits<int16_t>::min()),
        static_cast<double>(std::numeric_limits<int16_t>::max())));
}

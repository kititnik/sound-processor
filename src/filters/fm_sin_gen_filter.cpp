#include "filters/fm_sin_gen_filter.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>

FmSinGenFilter::FmSinGenFilter(double amplitude, double carrierHz,
                               double modulationHz, double deviationHz,
                               double durationMs)
    : AbstractGeneratorFilter(durationMs), _amplitude(amplitude),
      _carrierHz(carrierHz), _modulationHz(modulationHz),
      _deviationHz(deviationHz) {}

int16_t FmSinGenFilter::computeSample(double sampleSec) const {
    double phase =
        2.0 * std::numbers::pi * _carrierHz * sampleSec +
        (_deviationHz / _modulationHz) *
            std::sin(2.0 * std::numbers::pi * _modulationHz * sampleSec);
    double value = _amplitude * 32767.0 * std::sin(phase);
    return static_cast<int16_t>(std::clamp(
        value, static_cast<double>(std::numeric_limits<int16_t>::min()),
        static_cast<double>(std::numeric_limits<int16_t>::max())));
}

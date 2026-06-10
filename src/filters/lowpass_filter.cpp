#include "filters/lowpass_filter.hpp"
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

LowpassFilter::LowpassFilter(size_t windowSize): _windowSize(windowSize) {}

void LowpassFilter::apply(Waveform* sound) {
    if(sound == nullptr) {
        throw std::runtime_error("Waveform* sound is nullptr");
    }
    if(sound->size() == 0) {
        return;
    }

    std::vector<int16_t> newSamples(sound->size());

    size_t sideLen = (_windowSize - 1) / 2;
    size_t rightOutBoundLen = sideLen >= sound->size() ? sideLen - sound->size() + 1 : 0;

    double currentSum = sound->getSample(0) * (sideLen + 1);

    for(size_t i = 1; i <= std::min(sideLen, sound->size() - 1); i++) {
        currentSum += sound->getSample(i);
    }
    currentSum += sound->getSample(sound->size() - 1) * rightOutBoundLen;

    newSamples[0] = static_cast<int16_t>(currentSum / _windowSize);

    for(size_t i = 1; i < sound->size(); i++) {
        if(i <= sideLen) {
            currentSum -= sound->getSample(0);
        }
        else {
            currentSum -= sound->getSample(i - sideLen - 1);
        }
        if(i + sideLen >= sound->size()) {
            currentSum += sound->getSample(sound->size() - 1);
        }
        else {
            currentSum += sound->getSample(i + sideLen);
        }
        newSamples[i] = static_cast<int16_t>(currentSum / _windowSize);
    }
    for(size_t i = 0; i < sound->size(); i++) {
        sound->setSample(i, newSamples[i]);
    }
}

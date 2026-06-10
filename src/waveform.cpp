#include "waveform.hpp"
#include "wav_constants.hpp"
#include <stdexcept>

Waveform::Waveform(std::vector<int16_t> samples): _samples(std::move(samples)) {}

size_t Waveform::size() const {
    return _samples.size();
}

const int16_t* Waveform::data() const {
    return _samples.data();
}

double Waveform::durationMs() const {
    return samplesToMs(_samples.size());
}

int16_t Waveform::getSample(size_t idx) const {
    return _samples.at(idx);
}

void Waveform::setSample(size_t idx, int16_t value) {
    _samples.at(idx) = value;
}

void Waveform::insert(size_t pos, size_t count, int16_t value) {
    if(pos > _samples.size()) {
        throw std::out_of_range("pos is out of samples range");
    }
    _samples.insert(_samples.begin() + pos, count, value);
}

void Waveform::resize(size_t newSize) {
    _samples.resize(newSize);
}

double Waveform::samplesToMs(size_t samplesCount) {
    return samplesCount * 1000.0 / static_cast<double>(SAMPLE_RATE);
}

size_t Waveform::msToSamples(double ms) {
    return ms / 1000.0 * static_cast<double>(SAMPLE_RATE);
}

size_t Waveform::secToSamples(double sec) {
    return sec * static_cast<double>(SAMPLE_RATE);
}

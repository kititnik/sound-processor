#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

class Waveform {
    public:
        size_t size() const;
        double durationMs() const;
        int16_t getSample(size_t idx) const;
        
        void setSample(size_t idx, int16_t value);
        void insert(size_t pos, size_t count, int16_t value);
        void resize(size_t newSize);

        static double samplesToMs(size_t samplesCount);
        static size_t msToSamples(double ms);
        static size_t secToSamples(double sec);
        
    private:
        std::vector<int16_t> _samples;
};
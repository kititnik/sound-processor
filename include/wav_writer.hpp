#pragma once

#include <ostream>
#include "waveform.hpp"

class WavWriter {
public:
    void write(std::ostream& ostr, const Waveform& waveform);
};
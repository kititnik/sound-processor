#pragma once

#include "waveform.hpp"
#include <cstddef>
#include <ostream>

class WavWriter {
public:
    void write(std::ostream& ostr, const Waveform& waveform) const;

private:
    void writeRiffHeader(std::ostream& ostr, size_t fileSize) const;
    void writeFmtHeader(std::ostream& ostr) const;
    void writeDataChunkHeader(std::ostream& ostr, size_t samplesSize) const;
};

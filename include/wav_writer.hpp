#pragma once

#include "waveform.hpp"
#include <cstddef>
#include <ostream>

class WavWriter {
public:
    void write(std::ostream& ostr, const Waveform& waveform);

private:
    void writeRiffHeader(std::ostream& ostr, size_t fileSize);
    void writeFmtHeader(std::ostream& ostr);
    void writeDataChunkHeader(std::ostream& ostr, size_t samplesSize);
};

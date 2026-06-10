#pragma once

#include "wav_chunks.hpp"
#include "waveform.hpp"
#include <istream>

class WavReader {
public:
    Waveform read(std::istream& istr) const;

private:
    static void validateRiffHeader(const RiffHeader& header);
    static void validateFmtHeader(const FmtHeader& header);
};

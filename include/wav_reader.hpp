#pragma once

#include <istream>
#include "waveform.hpp"
#include "wav_chunks.hpp"

class WavReader {
public:
    Waveform read(std::istream& istr);
private:
    static void validateRiffHeader(const RiffHeader& header);
    static void validateFmtHeader(const FmtHeader& header);
};
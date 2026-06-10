#include "wav_writer.hpp"
#include "wav_chunks.hpp"
#include "wav_constants.hpp"
#include <cstddef>
#include <cstdint>
#include <cstring>

void WavWriter::write(std::ostream& ostr, const Waveform& waveform) const {
    size_t samplesSize = waveform.size() * sizeof(int16_t);
    size_t fileSize = sizeof(RiffHeader) + sizeof(FmtHeader) + sizeof(DataChunkHeader) + samplesSize;
    writeRiffHeader(ostr, fileSize);
    writeFmtHeader(ostr);
    writeDataChunkHeader(ostr, samplesSize);
    ostr.write(reinterpret_cast<const char*>(waveform.data()), samplesSize);
    if(ostr.fail()) {
        throw std::runtime_error("Output stream failed writing samples");
    }
}

void WavWriter::writeRiffHeader(std::ostream& ostr, size_t fileSize) const {
    RiffHeader riffHeader{};
    memcpy(&riffHeader.chunkId, "RIFF", 4);
    // -8 for RIFF header
    riffHeader.chunkSize = fileSize - 8;
    memcpy(&riffHeader.waveId, "WAVE", 4);
    ostr.write(reinterpret_cast<char*>(&riffHeader), sizeof(riffHeader));
    if(ostr.fail()) {
        throw std::runtime_error("Output stream failed writing RIFF HEADER");
    }
}

void WavWriter::writeFmtHeader(std::ostream& ostr) const {
    FmtHeader fmtHeader{};
    memcpy(&fmtHeader.chunkId, "fmt ", 4);
    fmtHeader.chunkSize = 16;
    fmtHeader.wFormatTag = AUDIO_FORMAT;
    fmtHeader.wChannels = CHANNELS_COUNT;
    fmtHeader.dwSamplesPerSec = SAMPLE_RATE;
    fmtHeader.dwAvgBytesPerSec = BYTES_PER_SEC;
    fmtHeader.wBlockAlign = BLOCK_ALIGN;
    fmtHeader.wBitsPerSample = BITS_PER_SAMPLE;
    ostr.write(reinterpret_cast<char*>(&fmtHeader), sizeof(fmtHeader));
    if(ostr.fail()) {
        throw std::runtime_error("Output stream failed writing FMT HEADER");
    }
}

void WavWriter::writeDataChunkHeader(std::ostream& ostr, size_t samplesSize) const {
    DataChunkHeader dataChunkHeader{};
    memcpy(&dataChunkHeader.chunkId, "data", 4);
    dataChunkHeader.chunkSize = samplesSize;
    ostr.write(reinterpret_cast<char*>(&dataChunkHeader), sizeof(dataChunkHeader));
    if(ostr.fail()) {
        throw std::runtime_error("Output stream failed writing DATA CHUNK HEADER");
    }
}

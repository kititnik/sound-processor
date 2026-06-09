#include "wav_reader.hpp"
#include "wav_chunks.hpp"
#include "wav_constants.hpp"
#include "waveform.hpp"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <format>
#include <stdexcept>
#include <string_view>

constexpr std::string_view FILE_FORMAT_ERROR =
    "Wrong file format! {} mismatch. Expected: {}. Got {}";

Waveform WavReader::read(std::istream& istr) {
    RiffHeader riffHeader;
    istr.read(reinterpret_cast<char*>(&riffHeader), sizeof(riffHeader));
    if(istr.fail()) {
        throw std::runtime_error("Input stream failed reading RIFF HEADER");
    }
    validateRiffHeader(riffHeader);

    FmtHeader fmtHeader;
    istr.read(reinterpret_cast<char*>(&fmtHeader), sizeof(fmtHeader));
    if(istr.fail()) {
        throw std::runtime_error("Input stream failed reading FMT HEADER");
    }
    validateFmtHeader(fmtHeader);

    DataChunkHeader dataChunkHeader;
    istr.read(reinterpret_cast<char*>(&dataChunkHeader),
              sizeof(dataChunkHeader));
    if(istr.fail()) {
        throw std::runtime_error(
            "Input stream failed reading DATA CHUNK HEADER");
    }
    if(memcmp(&dataChunkHeader.chunkId, "data", 4) != 0) {
        throw std::runtime_error(
            std::format(FILE_FORMAT_ERROR, "Data Chunk Header chunk Id", "data",
                        std::string_view(dataChunkHeader.chunkId, 4)));
    }

    size_t count = dataChunkHeader.chunkSize / sizeof(int16_t);
    std::vector<int16_t> samples(count);
    istr.read(reinterpret_cast<char*>(samples.data()), count * sizeof(int16_t));
    if(istr.fail()) {
        throw std::runtime_error("Input stream failed reading samples");
    }
    Waveform waveform(std::move(samples));
    return waveform;
}

void WavReader::validateRiffHeader(const RiffHeader& header) {
    if(memcmp(&header.chunkId, "RIFF", 4) != 0) {
        throw std::runtime_error(
            std::format(FILE_FORMAT_ERROR, "RIFF header chunk Id", "RIFF",
                        std::string_view(header.chunkId, 4)));
    }
    if(memcmp(&header.waveId, "WAVE", 4) != 0) {
        throw std::runtime_error(
            std::format(FILE_FORMAT_ERROR, "RIFF header wave Id", "WAVE",
                        std::string_view(header.waveId, 4)));
    }
}

void WavReader::validateFmtHeader(const FmtHeader& header) {
    if(memcmp(&header.chunkId, "fmt ", 4) != 0) {
        throw std::runtime_error(
            std::format(FILE_FORMAT_ERROR, "FMT header chunk Id", "fmt ",
                        std::string_view(header.chunkId, 4)));
    }
    if(header.wFormatTag != AUDIO_FORMAT) {
        throw std::runtime_error(std::format(FILE_FORMAT_ERROR,
                                             "FMT header compression code",
                                             AUDIO_FORMAT, header.wFormatTag));
    }
    if(header.wChannels != CHANNELS_COUNT) {
        throw std::runtime_error(std::format(FILE_FORMAT_ERROR,
                                             "FMT header number of channels",
                                             CHANNELS_COUNT, header.wChannels));
    }
    if(header.dwSamplesPerSec != SAMPLE_RATE) {
        throw std::runtime_error(
            std::format(FILE_FORMAT_ERROR, "FMT header sample rate",
                        SAMPLE_RATE, header.dwSamplesPerSec));
    }
    if(header.dwAvgBytesPerSec != BYTES_PER_SEC) {
        throw std::runtime_error(std::format(
            FILE_FORMAT_ERROR, "FMT header average bytes per second",
            BYTES_PER_SEC, header.dwAvgBytesPerSec));
    }
    if(header.wBlockAlign != BLOCK_ALIGN) {
        throw std::runtime_error(std::format(FILE_FORMAT_ERROR,
                                             "FMT header block align",
                                             BLOCK_ALIGN, header.wBlockAlign));
    }
    if(header.wBitsPerSample != BITS_PER_SAMPLE) {
        throw std::runtime_error(
            std::format(FILE_FORMAT_ERROR, "FMT header bits per sample",
                        BITS_PER_SAMPLE, header.wBitsPerSample));
    }
}

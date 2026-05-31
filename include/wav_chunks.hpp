#pragma once

#include <cstdint>

struct __attribute__((packed)) RiffHeader
{
    uint32_t chunkId;
    uint32_t chunkSize;
    uint32_t waveId;
};

struct __attribute__((packed)) FmtHeader
{
    uint32_t chunkId;
    uint32_t chunkSize;
    uint16_t wFormatTag;
    uint16_t wChannels;
    uint32_t dwSamplesPerSec;
    uint32_t dwAvgBytesPerSec;
    uint16_t wBlockAlign;
    uint16_t wBitsPerSample;
};

struct __attribute__((packed)) DataChunkHeader
{
    uint32_t chunkId;
    uint32_t chunkSize;
};
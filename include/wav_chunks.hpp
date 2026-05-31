#pragma once

#include <cstdint>

struct __attribute__((packed)) RiffHeader
{
    char chunkId[4];
    uint32_t chunkSize;
    char waveId[4];
};

struct __attribute__((packed)) FmtHeader
{
    char chunkId[4];
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
    char chunkId[4];
    uint32_t chunkSize;
};
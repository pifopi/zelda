#pragma once

#include <cstdint>

namespace Zelda
{
    enum class TileType
    {
        Empty,
        Full,
        NPC,
        Object
    };

    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    using U8 = uint8_t;
    using U16 = uint16_t;
    using U32 = uint32_t;
    using U64 = uint64_t;

    using S8 = int8_t;
    using S16 = int16_t;
    using S32 = int32_t;
    using S64 = int64_t;

    using TileNumber = U16;

    class NonCopyable
    {
    protected:
        NonCopyable() = default;
        ~NonCopyable() = default;
        NonCopyable(const NonCopyable&) = delete;
        NonCopyable& operator=(const NonCopyable&) = delete;
    };
}

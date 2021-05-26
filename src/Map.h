#pragma once

#include "Utils.h"
#include "Tileset.h"

#include <vector>

namespace sf
{
    class Sprite;
}

namespace Zelda
{
    class Map
        : public NonCopyable
    {
    public:
        void LoadXML(const std::string& path);
        const sf::Sprite& GetSprite(S32 x, const S32 y);
        TileType GetTileType(S32 x, const S32 y) const;

        static constexpr TileNumber k_defaultTileNumber = 88;

    private:
        S32 GetSizeX() const;
        S32 GetSizeY() const;

        Tileset m_tileset;
        std::vector<std::vector<TileNumber>> m_tilesNumber;
    };
}

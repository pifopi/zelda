#pragma once

#include "Utils.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

namespace Zelda
{
    class Tileset
        : public NonCopyable
    {
    public:
        static Tileset& Instance();
        void LoadXML(const std::string& path);
        const sf::Sprite& GetView(const U32& x, const U32& y);
        const TileType& GetTileType(const TileNumber& tileNumber) const;

    private:
        sf::Sprite m_tiles;
        sf::Texture m_tilesTexture;
        std::vector<TileType> m_typeTile;
    };
}

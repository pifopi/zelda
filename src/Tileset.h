#pragma once

#include "Utils.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <vector>

namespace rapidxml
{
    template<typename T>
    class xml_node;
}

namespace Zelda
{
    class Tileset
        : public NonCopyable
    {
    public:
        void LoadXML(const rapidxml::xml_node<char>* tilesetNode);
        const sf::Sprite& GetSprite(TileNumber tileNumber);
        TileType GetTileType(TileNumber tileNumber) const;

        static constexpr U32 k_tileWidth = 32;
        static constexpr U32 k_tileHeight = 32;

    private:
        sf::Sprite m_tiles;
        sf::Texture m_tilesTexture;
        std::vector<TileType> m_tilesType;
    };
}

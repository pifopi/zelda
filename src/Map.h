#pragma once

#include "Utils.h"

#include <rapidXML/rapidxml.hpp>

#include <vector>

namespace Zelda
{
    class Map
        : public NonCopyable
    {
    public:
        static Map& Instance();
        void LoadXML(rapidxml::xml_node<>* layerNode);
        TileNumber GetTileNumber(const S32& x, const S32& y) const;

        static const U32 k_tileWidth = 32;
        static const U32 k_tileHeight = 32;
        static const TileNumber k_defaultTileNumber = 88;

    private:
        S32 GetSizeX() const;
        S32 GetSizeY() const;

        std::vector<std::vector<TileNumber>> m_tilesNumber;
    };
}

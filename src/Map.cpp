#include "Map.h"

#include <fstream>
#include <sstream>

namespace Zelda
{
    Map& Map::Instance()
    {
        static Map instance;
        return instance;
    }

    void Map::LoadXML(rapidxml::xml_node<>* layerNode)
    {
        m_tilesNumber.clear();

        const auto& dataNode = layerNode->first_node("data");

        auto ssFile = std::stringstream(dataNode->value());
        auto line = std::string();
        while (std::getline(ssFile, line))
        {
            auto value = std::string();
            auto ssLine = std::stringstream(line);
            auto tempMap = std::vector<TileNumber>();
            while (std::getline(ssLine, value, ','))
            {
                tempMap.push_back(static_cast<TileNumber>(std::stoi(value) - 1));
            }
            if (tempMap.size() != 0)
            {
                m_tilesNumber.push_back(tempMap);
            }
        }
    }

    TileNumber Map::GetTileNumber(const S32& x, const S32& y) const
    {
        if (x < 0 || y < 0 || x >= GetSizeX() || y >= GetSizeY())
        {
            return k_defaultTileNumber;
        }
        return m_tilesNumber[y][x];
    }

    S32 Map::GetSizeX() const
    {
        return static_cast<S32>(m_tilesNumber[0].size());
    }

    S32 Map::GetSizeY() const
    {
        return static_cast<S32>(m_tilesNumber.size());
    }
}

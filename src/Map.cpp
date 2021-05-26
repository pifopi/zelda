#include "Map.h"

#include <rapidXML/rapidxml.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <fstream>
#include <sstream>

namespace Zelda
{
    void Map::LoadXML(const std::string& path)
    {
        m_tilesNumber.clear();

        /*Read the xml file into a vector*/
        auto file = std::ifstream(path);
        auto buffer = std::vector<char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        buffer.push_back('\0');

        /*Parse the buffer using the xml file parsing library into doc*/
        rapidxml::xml_document<> doc;
        doc.parse<0>(&buffer[0]);

        /*Find our root node*/
        const auto& rootNode = doc.first_node("map");

        m_tileset.LoadXML(rootNode->first_node("tileset"));

        const auto& layerNode = rootNode->first_node("layer");

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

    const sf::Sprite& Map::GetSprite(S32 x, const S32 y)
    {
        if (x < 0 || y < 0 || x >= GetSizeX() || y >= GetSizeY())
        {
            return m_tileset.GetSprite(k_defaultTileNumber);
        }
        return m_tileset.GetSprite(m_tilesNumber[y][x]);
    }

    TileType Map::GetTileType(const S32 x, const S32 y) const
    {
        if (x < 0 || y < 0 || x >= GetSizeX() || y >= GetSizeY())
        {
            return TileType::Full;
        }
        return m_tileset.GetTileType(m_tilesNumber[y][x]);
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

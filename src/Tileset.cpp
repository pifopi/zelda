#include "Map.h"
#include "Tileset.h"

#include <rapidXML/rapidxml.hpp>

#include <fstream>
#include <sstream>

namespace Zelda
{
    void Tileset::LoadXML(const rapidxml::xml_node<char>* tilesetNode)
    {
        m_tilesType.clear();

        /*Load the image*/
        const auto& imageNode = tilesetNode->first_node("image");
        m_tilesTexture.loadFromFile(imageNode->first_attribute("source")->value());
        m_tiles.setTexture(m_tilesTexture);

        /*Load the tileset information*/
        for (auto tileNode = tilesetNode->first_node("tile"); tileNode != nullptr; tileNode = tileNode->next_sibling())
        {
            const auto& propertiesNode = tileNode->first_node("properties");
            const auto& propertyNode = propertiesNode->first_node("property");
            const auto& value = std::string(propertyNode->first_attribute("value")->value());

            if (value.compare("Empty") == 0)
            {
                m_tilesType.push_back(TileType::Empty);
            }
            else if (value.compare("Full") == 0)
            {
                m_tilesType.push_back(TileType::Full);
            }
            else if (value.compare("NPC") == 0)
            {
                m_tilesType.push_back(TileType::NPC);
            }
            else if (value.compare("Object") == 0)
            {
                m_tilesType.push_back(TileType::Object);
            }
        }
    }

    const sf::Sprite& Tileset::GetSprite(const TileNumber tileNumber)
    {
        m_tiles.setTextureRect(sf::IntRect((tileNumber % 8) * k_tileWidth, (tileNumber / 8) * k_tileHeight, k_tileWidth, k_tileHeight));
        return m_tiles;
    }

    TileType Tileset::GetTileType(const TileNumber tileNumber) const
    {
        return m_tilesType[tileNumber];
    }
}

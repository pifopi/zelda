#include "Map.h"
#include "Tileset.h"

#include <rapidXML/rapidxml.hpp>

#include <fstream>
#include <sstream>

namespace Zelda
{
    Tileset& Tileset::Instance()
    {
        static Tileset instance;
        return instance;
    }

    void Tileset::LoadXML(const std::string& path)
    {
        m_typeTile.clear();

        /*Read the xml file into a vector*/
        auto file = std::ifstream(path);
        auto buffer = std::vector<char>(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        buffer.push_back('\0');

        /*Parse the buffer using the xml file parsing library into doc*/
        rapidxml::xml_document<> doc;
        doc.parse<0>(&buffer[0]);

        /*Find our root node*/
        const auto& rootNode = doc.first_node("map");

        /*Load the tileset*/
        const auto& tilesetNode = rootNode->first_node("tileset");

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
                m_typeTile.push_back(TileType::Empty);
            }
            else if (value.compare("Full") == 0)
            {
                m_typeTile.push_back(TileType::Full);
            }
            else if (value.compare("NPC") == 0)
            {
                m_typeTile.push_back(TileType::NPC);
            }
            else if (value.compare("Object") == 0)
            {
                m_typeTile.push_back(TileType::Object);
            }
        }

        Map::Instance().LoadXML(rootNode->first_node("layer"));
    }

    const sf::Sprite& Tileset::GetView(const U32& x, const U32& y)
    {
        const auto& tileNumber = Map::Instance().GetTileNumber(x, y);
        m_tiles.setTextureRect(sf::IntRect((tileNumber % 8) * Map::k_tileWidth, (tileNumber / 8) * Map::k_tileHeight, Map::k_tileWidth, Map::k_tileHeight));
        return m_tiles;
    }

    const TileType& Tileset::GetTileType(const TileNumber& tileNumber) const
    {
        return m_typeTile[tileNumber];
    }
}

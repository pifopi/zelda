#pragma once

#include "Utils.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <array>

namespace Zelda
{
    class Player
        : public NonCopyable
    {
    public:
        Player(const sf::Vector2f& position, const sf::Vector2f& size);
        const sf::RectangleShape& GetShape() const;
        void Update(const Map& map);

    private:
        void UpdateWithJoystick(const Map& map);
        void UpdateWithKeyboard(const Map& map);
        void MoveTo(Direction direction, float wantedX, float wantedY, const Map& map);
        void SetTexture(Direction direction);

        sf::RectangleShape m_shape;
        std::array<sf::Texture, 4> m_textures;
    };
}

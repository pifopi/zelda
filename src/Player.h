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
        void Update();

    private:
        void UpdateWithJoystick();
        void UpdateWithKeyboard();
        void MoveTo(const Direction& direction, const float& wantedX, const float& wantedY);
        void SetTexture(const Direction& direction);

        sf::RectangleShape m_shape;
        std::array<sf::Texture, 4> m_textures;
    };
}

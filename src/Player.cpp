#include "Map.h"
#include "Player.h"
#include "Tileset.h"

#include <imgui/imgui.h>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Keyboard.hpp>

#include <unordered_set>

namespace
{
    static constexpr float k_step = 4.f;
}

namespace Zelda
{
    Player::Player(const sf::Vector2f& position, const sf::Vector2f& size)
        : m_shape(size)
    {
        m_shape.setPosition(position);
        m_textures[static_cast<U32>(Direction::Up)].loadFromFile("UpTexture.png");
        m_textures[static_cast<U32>(Direction::Down)].loadFromFile("DownTexture.png");
        m_textures[static_cast<U32>(Direction::Left)].loadFromFile("LeftTexture.png");
        m_textures[static_cast<U32>(Direction::Right)].loadFromFile("RightTexture.png");
        SetTexture(Direction::Down);
    }

    const sf::RectangleShape& Player::GetShape() const
    {
        return m_shape;
    }

    void Player::Update(const Map& map)
    {
        if (sf::Joystick::isConnected(0))
        {
            UpdateWithJoystick(map);
        }
        else
        {
            UpdateWithKeyboard(map);
        }
    }

    void Player::UpdateWithJoystick(const Map& map)
    {
        const float stepX = k_step * sf::Joystick::getAxisPosition(0, sf::Joystick::X) / 100;
        const float stepY = k_step * sf::Joystick::getAxisPosition(0, sf::Joystick::Y) / 100;

        const float absStepX = std::abs(stepX);
        const float absStepY = std::abs(stepY);

        const float currentPositionX = m_shape.getPosition().x;
        const float currentPositionY = m_shape.getPosition().y;

        if (stepY < 0)
        {
            if (absStepY > absStepX)
            {
                SetTexture(Direction::Up);
            }
            MoveTo(Direction::Up, m_shape.getPosition().x, m_shape.getPosition().y + stepY, map);
        }
        else
        {
            if (absStepY > absStepX)
            {
                SetTexture(Direction::Down);
            }
            MoveTo(Direction::Down, m_shape.getPosition().x, m_shape.getPosition().y + stepY, map);
        }

        if (stepX > 0)
        {
            if (absStepX > absStepY)
            {
                SetTexture(Direction::Right);
            }
            MoveTo(Direction::Right, m_shape.getPosition().x + stepX, m_shape.getPosition().y, map);
        }
        else
        {
            if (absStepX > absStepY)
            {
                SetTexture(Direction::Left);
            }
            MoveTo(Direction::Left, m_shape.getPosition().x + stepX, m_shape.getPosition().y, map);
        }
    }

    void Player::UpdateWithKeyboard(const Map& map)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
        {
            SetTexture(Direction::Up);
            MoveTo(Direction::Up, m_shape.getPosition().x, m_shape.getPosition().y - k_step, map);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            SetTexture(Direction::Down);
            MoveTo(Direction::Down, m_shape.getPosition().x, m_shape.getPosition().y + k_step, map);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            SetTexture(Direction::Right);
            MoveTo(Direction::Right, m_shape.getPosition().x + k_step, m_shape.getPosition().y, map);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        {
            SetTexture(Direction::Left);
            MoveTo(Direction::Left, m_shape.getPosition().x - k_step, m_shape.getPosition().y, map);
        }
    }

    void Player::MoveTo(const Direction direction, const float wantedX, const float wantedY, const Map& map)
    {
        float realX = wantedX;
        float realY = wantedY;

        const U32 yPlayerSize = static_cast<U32>(m_shape.getSize().y);
        const U32 xPlayerSize = static_cast<U32>(m_shape.getSize().x);

        const float topPlayer = wantedY;
        const float bottomPlayer = wantedY + yPlayerSize;
        const float leftPlayer = wantedX;
        const float rightPlayer = wantedX + xPlayerSize;

        const S32 yMin = static_cast<S32>(wantedY / Tileset::k_tileHeight - 1);
        const S32 yMax = static_cast<S32>((wantedY + yPlayerSize) / Tileset::k_tileHeight + 1);
        const S32 xMin = static_cast<S32>(wantedX / Tileset::k_tileWidth - 1);
        const S32 xMax = static_cast<S32>((wantedX + xPlayerSize) / Tileset::k_tileWidth + 1);

        auto collisions = std::unordered_set<TileType>();
        for (S32 y = yMin; y < yMax; ++y)
        {
            for (S32 x = xMin; x < xMax; ++x)
            {
                const S32 topTile = y * Tileset::k_tileHeight;
                const S32 bottomTile = (y + 1) * Tileset::k_tileHeight;
                const S32 leftTile = x * Tileset::k_tileWidth;
                const S32 rightTile = (x + 1) * Tileset::k_tileWidth;

                const auto& tileType = map.GetTileType(x, y);

                if (tileType == TileType::Empty ||
                    topPlayer >= bottomTile ||
                    bottomPlayer <= topTile ||
                    rightPlayer <= leftTile ||
                    leftPlayer >= rightTile)
                {
                    continue;
                }
                switch (direction)
                {
                case Direction::Up:
                    if (std::abs(topPlayer - bottomTile) <= k_step)
                    {
                        collisions.insert(tileType);
                        realY = m_shape.getPosition().y;
                    }
                    break;
                case Direction::Down:
                    if (std::abs(bottomPlayer - topTile) <= k_step)
                    {
                        collisions.insert(tileType);
                        realY = m_shape.getPosition().y;
                    }
                    break;
                case Direction::Right:
                    if (std::abs(rightPlayer - leftTile) <= k_step)
                    {
                        collisions.insert(tileType);
                        realX = m_shape.getPosition().x;
                    }
                    break;
                case Direction::Left:
                    if (std::abs(leftPlayer - rightTile) <= k_step)
                    {
                        collisions.insert(tileType);
                        realX = m_shape.getPosition().x;
                    }
                    break;
                default:
                    assert(false);
                    exit(EXIT_FAILURE);
                }
            }
        }

        m_shape.setPosition(sf::Vector2f(realX, realY));

        for (const auto& elem : collisions)
        {
            switch (elem)
            {
            case TileType::Empty:
                assert(false);
                exit(EXIT_FAILURE);
            case TileType::Full:
                break;
            case TileType::NPC:
                ImGui::OpenPopup("NPC");
                ImGui::BeginPopupModal("NPC");
                ImGui::Text("Hello, do you know what I'm doing there ?");
                ImGui::EndPopup();
                break;
            case TileType::Object:
                ImGui::OpenPopup("Object");
                ImGui::BeginPopupModal("Object");
                ImGui::Text("You found a new object !! What is that ?");
                ImGui::EndPopup();
                break;
            }
        }
    }

    void Player::SetTexture(const Direction direction)
    {
        m_shape.setTexture(&m_textures[static_cast<U32>(direction)]);
    }
}

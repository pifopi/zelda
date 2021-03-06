#include "Map.h"
#include "Player.h"
#include "Tileset.h"

#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>
#include <rapidXML/rapidxml.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include <sstream>

namespace
{
    static const Zelda::U32 k_numberTilesPerRow = 32;
    static const Zelda::U32 k_numberTilesPerColumn = 28;
    static const Zelda::U32 k_windowWidth = Zelda::Tileset::k_tileWidth * k_numberTilesPerRow;
    static const Zelda::U32 k_windowsHeight = Zelda::Tileset::k_tileHeight * k_numberTilesPerColumn;
}

sf::Int64 GetCurrentFPS(const sf::Clock& clock)
{
    return 1'000'000 / clock.getElapsedTime().asMicroseconds();
}

int main()
{
    Zelda::Map map;
    map.LoadXML("Map.tmx");

    sf::RenderWindow window(sf::VideoMode(k_windowWidth, k_windowsHeight, 32), "Zelda 2D");
    window.setVerticalSyncEnabled(true);
    ImGui::SFML::Init(window);

    auto&& player = Zelda::Player(sf::Vector2f(1280, 1280), sf::Vector2f(19, 25));

    auto clock = sf::Clock();
    auto event = sf::Event();
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::L)
                {
                    map.LoadXML("Map.tmx");
                }
                break;
            default:
                break;
            }
        }

        window.clear();
        ImGui::SFML::Update(window, clock.getElapsedTime());
        player.Update(map);

        auto playerShape = player.GetShape();
        const auto& playerPosition = playerShape.getPosition();
        const float xPosition = playerPosition.x;
        const float yPosition = playerPosition.y;
        const float ymin = (yPosition - k_windowsHeight / 2) / Zelda::Tileset::k_tileHeight;
        const float ymax = (yPosition + k_windowsHeight / 2) / Zelda::Tileset::k_tileHeight;
        const float xmin = (xPosition - k_windowWidth / 2) / Zelda::Tileset::k_tileWidth;
        const float xmax = (xPosition + k_windowWidth / 2) / Zelda::Tileset::k_tileWidth;

        for (int y = static_cast<int> (ymin - 1); y < ymax; ++y)
        {
            for (int x = static_cast<int> (xmin - 1); x < xmax; ++x)
            {
                auto tile = map.GetSprite(x, y);
                tile.setPosition((x - xmin) * Zelda::Tileset::k_tileWidth, (y - ymin) * Zelda::Tileset::k_tileHeight);
                window.draw(tile);
            }
        }
        playerShape.setPosition(k_windowWidth / 2, k_windowsHeight / 2);
        window.draw(playerShape);

        ImGui::Begin("Infos");
        ImGui::Text("Current FPS : %lld", GetCurrentFPS(clock));

        if (ImGui::TreeNode("Position"))
        {
            ImGui::Text("Position X : %f, (tile : %f)", xPosition, xPosition / Zelda::Tileset::k_tileWidth);
            ImGui::Text("Position Y : %f, (tile : %f)", yPosition, yPosition / Zelda::Tileset::k_tileHeight);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Inputs"))
        {
            ImGui::Text("Joystick X : %f", sf::Joystick::getAxisPosition(0, sf::Joystick::X));
            ImGui::Text("Joystick Y : %f", sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
            ImGui::Text("Up key : %d", sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Z));
            ImGui::Text("Down key : %d", sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S));
            ImGui::Text("Right key : %d", sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D));
            ImGui::Text("Left key : %d", sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q));
            ImGui::TreePop();
        }
        ImGui::End();

        ImGui::SFML::Render(window);
        window.display();

        clock.restart();
    }

    ImGui::SFML::Shutdown();

    return EXIT_SUCCESS;
}

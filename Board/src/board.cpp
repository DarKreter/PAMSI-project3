#include "board.hpp"
#include "pawn.hpp"
#include <iostream>

namespace pamsi {
void Board_t::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& a : tiles)
        for(auto& tile : a)
            target.draw(tile, states);

    for(auto& figure : whiteFigures)

        target.draw(*figure, states);

    for(auto& figure : blackFigures)
        target.draw(*figure, states);
}

bool Board_t::CheckLoseConditions(Team_e player)
{
    return (player == Team_e::white ? whiteFigures : blackFigures).empty();
}

bool Board_t::CheckDrawConditions(Team_e player)
{
    auto figures = (player == Team_e::white ? whiteFigures : blackFigures);

    for(std::shared_ptr<Figure_t> figure : figures) {
        auto movesList = figure->GetPossibleMoves();
        if(!movesList.empty())
            return false;
    }
    return true;
}

Board_t::Board_t(float windowsSize, float borderWidth)
{
    SetUpTiles(windowsSize, borderWidth);
    SetUpTextures();
    SetUpFigures(windowsSize, borderWidth);
}

void Board_t::SetUpFigures(float windowsSize, float borderWidth)
{
    float tileLength = (windowsSize / 8.f);
    float figureRadius = (tileLength - borderWidth) * 0.45f;

    auto calcPos = [tileLength, borderWidth](auto x, auto y) -> sf::Vector2f {
        return sf::Vector2f(x * tileLength + borderWidth / 2.f +
                                (tileLength - borderWidth) * 0.05f,
                            y * tileLength + borderWidth / 2.f +
                                (tileLength - borderWidth) * 0.05f);
    };

    for(size_t x = 0; x < 8; x++) {
        for(size_t y = 5; y < 8; y++) {

            if(x % 2 != y % 2) {
                auto temp = std::make_shared<Pawn_t>(figureRadius);
                temp->SetTexture(whitePawn);
                temp->SetPosition(calcPos(x, y));
                temp->SetCoordinates(sf::Vector2u(x, y));
                temp->SetTeam(Team_e::white);
                whiteFigures.emplace_back(temp);
            }
        }
    }

    for(size_t x = 0; x < 8; x++) {
        for(size_t y = 0; y < 3; y++) {
            auto temp = std::make_shared<Pawn_t>(figureRadius);

            if(x % 2 != y % 2) {
                temp->SetTexture(blackPawn);
                temp->SetPosition(calcPos(x, y));
                temp->SetCoordinates(sf::Vector2u(x, y));
                temp->SetTeam(Team_e::black);
                blackFigures.emplace_back(temp);
            }
        }
    }
}
void Board_t::SetUpTiles(float windowsSize, float borderWidth)
{
    float tileLength = (windowsSize / 8.f);
    // Setup tiles
    for(size_t x = 0; x < 8; x++) {
        std::vector<pamsi::Tile_t> tempVector;
        for(size_t y = 0; y < 8; y++) {

            pamsi::Tile_t temp(sf::Vector2f(tileLength, tileLength));

            if(x % 2 != y % 2)
                temp.SetColor(fillColor_1);
            else
                temp.SetColor(fillColor_2);

            temp.SetBorderWidth(borderWidth);
            temp.SetOutlineColor(outlineColor);
            temp.SetPosition(sf::Vector2f(x * tileLength, y * tileLength));

            tempVector.emplace_back(temp);
        }
        tiles.emplace_back(tempVector);
    }
}

void Board_t::SetUpTextures()
{
    if(!whitePawn.loadFromFile("whitePawn.jpg"))
        throw std::runtime_error("\"whitePawn.jpg not found!\"");

    if(!blackPawn.loadFromFile("blackPawn.jpg"))
        throw std::runtime_error("\"blackPawn.jpg not found!\"");

    whitePawn.setSmooth(true);
    blackPawn.setSmooth(true);
}

} // namespace pamsi

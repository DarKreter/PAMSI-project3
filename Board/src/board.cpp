#include "board.hpp"
#include "pawn.hpp"
#include <iostream>

namespace pamsi {

pamsi::Tile_t Board_t::operator()(uint8_t x, uint8_t y) { return _tiles.at(x).at(y); }

void Board_t::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(auto& a : _tiles)
        for(auto& tile : a)
            target.draw(tile, states);

    for(auto& figure : _whiteFigures)

        target.draw(*figure, states);

    for(auto& figure : _blackFigures)
        target.draw(*figure, states);
}

bool Board_t::CheckLoseConditions(Team_e player)
{
    return (player == Team_e::white ? _whiteFigures : _blackFigures).empty();
}

bool Board_t::CheckDrawConditions(Team_e player)
{
    auto figures = (player == Team_e::white ? _whiteFigures : _blackFigures);

    // std::List<>
    // Create list of all moves

    for(std::shared_ptr<Figure_t> figure : figures) {
        auto movesList = figure->GetPossibleMoves();
        std::cout << figure->GetCoordinates().x << " " << figure->GetCoordinates().y << "\t";

        for(auto& move : movesList)
            std::cout << move.x << " " << move.y << ", ";
        std::cout << std::endl;
        // if(!movesList.empty())
        //     return false;
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
        return sf::Vector2f(x * tileLength + borderWidth / 2.f + (tileLength - borderWidth) * 0.05f,
                            y * tileLength + borderWidth / 2.f +
                                (tileLength - borderWidth) * 0.05f);
    };

    for(size_t x = 0; x < 8; x++) {
        for(size_t y = 5; y < 8; y++) {

            if(x % 2 != y % 2) {
                auto temp = std::make_shared<Pawn_t>(figureRadius);
                temp->SetTexture(_whitePawn);
                temp->SetPosition(calcPos(x, y));
                temp->SetCoordinates(sf::Vector2u(x, y));
                temp->SetTeam(Team_e::white);
                temp->SetBoard(this);
                _whiteFigures.emplace_back(temp);
            }
        }
    }

    for(size_t x = 0; x < 8; x++) {
        for(size_t y = 0; y < 3; y++) {
            auto temp = std::make_shared<Pawn_t>(figureRadius);

            if(x % 2 != y % 2) {
                temp->SetTexture(_blackPawn);
                temp->SetPosition(calcPos(x, y));
                temp->SetCoordinates(sf::Vector2u(x, y));
                temp->SetTeam(Team_e::black);
                temp->SetBoard(this);
                _blackFigures.emplace_back(temp);
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
        _tiles.emplace_back(tempVector);
    }
}

void Board_t::SetUpTextures()
{
    if(!_whitePawn.loadFromFile("whitePawn.jpg"))
        throw std::runtime_error("\"whitePawn.jpg not found!\"");

    if(!_blackPawn.loadFromFile("blackPawn.jpg"))
        throw std::runtime_error("\"blackPawn.jpg not found!\"");

    _whitePawn.setSmooth(true);
    _blackPawn.setSmooth(true);
}

} // namespace pamsi

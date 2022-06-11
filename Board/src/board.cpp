#include "board.hpp"
#include "pawn.hpp"
#include <algorithm>
#include <iostream>


namespace pamsi {

pamsi::Tile_t& Board_t::operator()(uint8_t x, uint8_t y) { return _tiles.at(x).at(y); }

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

void Board_t::MoveFigure(pamsi::Move_t move)
{
    auto f = _tiles[move.GetSource().x][move.GetSource().y].GetFigure();
    f->SetCoordinates(move.GetDestination());

    _tiles[move.GetSource().x][move.GetSource().y].SetFigure(nullptr);
    _tiles[move.GetDestination().x][move.GetDestination().y].SetFigure(f);

    if(auto destroyedFigure = move.GetAttacked()) {
        _whiteFigures.erase(
            std::remove(_whiteFigures.begin(), _whiteFigures.end(), destroyedFigure),
            _whiteFigures.end());
        _blackFigures.erase(
            std::remove(_blackFigures.begin(), _blackFigures.end(), destroyedFigure),
            _blackFigures.end());
        _tiles[destroyedFigure->GetCoordinates().x][destroyedFigure->GetCoordinates().y].SetFigure(
            nullptr);
    }
}

bool Board_t::CheckLoseConditions(Team_e player)
{
    return (player == Team_e::white ? _whiteFigures : _blackFigures).empty();
}

std::vector<Move_t> Board_t::GetAllPossibleMoves(Team_e player)
{
    auto figures = (player == Team_e::white ? _whiteFigures : _blackFigures);

    // Create list of all moves
    std::vector<Move_t> allMoves;
    for(std::shared_ptr<Figure_t> figure : figures)
        for(auto attackMove : figure->GetAttackMoves())
            allMoves.emplace_back(attackMove);

    if(allMoves.empty())
        for(std::shared_ptr<Figure_t> figure : figures)
            for(auto normalMove : figure->GetNormalMoves())
                allMoves.emplace_back(normalMove);

    return allMoves;
}

Board_t::Board_t(float windowsSize, float borderWidth)
    : _borderWidth{borderWidth}, _tileLength{(windowsSize / 8.f)},
      _figureRadius{(_tileLength - borderWidth) * 0.45f}
{
    SetUpTiles();
    SetUpTextures();
    SetUpFigures();
}

void Board_t::SetUpFigures()
{
    for(size_t x = 0; x < 8; x++) {
        for(size_t y = 5; y < 8; y++) {
            if(x % 2 != y % 2) {
                // if(x == 3 && y == 6)
                //     x = 2, y = 3;
                // if(x == 4 && y == 5)
                //     continue;
                auto temp = std::make_shared<Pawn_t>(_figureRadius);
                temp->SetBoard(this);
                temp->SetTexture(_whitePawn);
                temp->SetCoordinates(sf::Vector2u(x, y));
                temp->SetTeam(Team_e::white);
                _whiteFigures.emplace_back(temp);

                _tiles[x][y].SetFigure(temp);

                // if(x == 2 && y == 3)
                //     x = 3, y = 6;
            }
        }
    }

    for(size_t x = 0; x < 8; x++) {
        for(size_t y = 0; y < 3; y++) {
            auto temp = std::make_shared<Pawn_t>(_figureRadius);

            if(x % 2 != y % 2) {
                // if(x == 0 && y == 1)
                //     x = 1, y = 4;
                // if(x == 2 && y == 1)
                //     x = 0, y = 3;
                // if(x == 1 && y == 2)
                //     x = 3, y = 4;
                // if(x == 4 && y == 1)
                //     continue;
                temp->SetBoard(this);
                temp->SetTexture(_blackPawn);
                temp->SetCoordinates(sf::Vector2u(x, y));
                temp->SetTeam(Team_e::black);
                _blackFigures.emplace_back(temp);

                _tiles[x][y].SetFigure(temp);

                // if(x == 1 && y == 4)
                //     x = 0, y = 1;
                // if(x == 0 && y == 3)
                //     x = 2, y = 1;
                // if(x == 3 && y == 4)
                //     x = 1, y = 2;
            }
        }
    }
}
void Board_t::SetUpTiles()
{
    // Setup tiles
    for(size_t x = 0; x < 8; x++) {
        std::vector<pamsi::Tile_t> tempVector;
        for(size_t y = 0; y < 8; y++) {

            pamsi::Tile_t temp(sf::Vector2f(_tileLength, _tileLength));

            if(x % 2 != y % 2)
                temp.SetColor(fillColor_1);
            else
                temp.SetColor(fillColor_2);

            temp.SetBorderWidth(_borderWidth);
            temp.SetOutlineColor(outlineColor);
            temp.SetPosition(sf::Vector2f(x * _tileLength, y * _tileLength));

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

#include "board.hpp"
#include "king.hpp"
#include "piece.hpp"
#include <algorithm>
#include <iostream>

namespace pamsi {

pamsi::Tile_t& Board_t::operator()(uint8_t x, uint8_t y) { return _tiles.at(x).at(y); }

void Board_t::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // draw all tiles
    for(auto& a : _tiles)
        for(auto& tile : a)
            target.draw(tile, states);

    // all white figures
    for(auto& figure : _whiteFigures)
        target.draw(*figure, states);

    // and all black figures
    for(auto& figure : _blackFigures)
        target.draw(*figure, states);
}

void Board_t::ChangePieceToKing(std::shared_ptr<Figure_t> figure)
{
    std::shared_ptr<Figure_t> temp = std::make_shared<King_t>(_figureRadius);
    temp->SetBoard(this);
    temp->SetCoordinates(figure->GetCoordinates());
    temp->SetTeam(figure->GetTeam());
    if(figure->GetTeam() == Team_e::white) {
        temp->SetTexture(_whiteKing);
        std::replace(std::begin(_whiteFigures), std::end(_whiteFigures), figure, temp);
    }
    else if(figure->GetTeam() == Team_e::black) {
        temp->SetTexture(_blackKing);
        std::replace(_blackFigures.begin(), _blackFigures.end(), figure, temp);
    }

    // Move it on tiles array
    _tiles[figure->GetCoordinates().x][figure->GetCoordinates().y].SetFigure(nullptr);
    _tiles[figure->GetCoordinates().x][figure->GetCoordinates().y].SetFigure(temp);
}

void Board_t::MoveFigure(pamsi::Move_t move)
{
    // Get figure that wants to move
    auto f = _tiles[move.GetSource().x][move.GetSource().y].GetFigure();
    // Change its coordinates
    f->SetCoordinates(move.GetDestination());

    // Move it on tiles array
    _tiles[move.GetSource().x][move.GetSource().y].SetFigure(nullptr);
    _tiles[move.GetDestination().x][move.GetDestination().y].SetFigure(f);

    // If it was attack, remove taken guy
    if(auto destroyedFigure = move.GetTaken()) {
        // remove from proper container
        if(f->GetTeam() == Team_e::white)
            _blackFigures.erase(
                std::remove(_blackFigures.begin(), _blackFigures.end(), destroyedFigure),
                _blackFigures.end());
        if(f->GetTeam() == Team_e::black)
            _whiteFigures.erase(
                std::remove(_whiteFigures.begin(), _whiteFigures.end(), destroyedFigure),
                _whiteFigures.end());
        // remove this guy from tiles array (he's ded now)
        _tiles[destroyedFigure->GetCoordinates().x][destroyedFigure->GetCoordinates().y].SetFigure(
            nullptr);
    }
}

bool Board_t::CheckLoseConditions(Team_e player)
{
    // Player lose if he has no figures
    return (player == Team_e::white ? _whiteFigures : _blackFigures).empty();
}

std::vector<Move_t> Board_t::GetAllPossibleMoves(Team_e player, bool figureAlreadyTaken)
{
    // Get proper container
    auto figures = (player == Team_e::white ? _whiteFigures : _blackFigures);

    // Create list of all moves
    std::vector<Move_t> allMoves;
    // First check if there is any attack moves
    for(std::shared_ptr<Figure_t> figure : figures)
        for(auto attackMove : figure->GetAttackMoves())
            allMoves.emplace_back(attackMove);

    // If not, get all normal moves
    if(allMoves.empty() && !figureAlreadyTaken)
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
            // Configure piece
            auto temp = std::make_shared<Piece_t>(_figureRadius);
            temp->SetBoard(this);
            temp->SetTexture(_whitePiece);
            temp->SetCoordinates(sf::Vector2u(x, y));
            temp->SetTeam(Team_e::white);
            _whiteFigures.emplace_back(temp);
            // add piece into tile array
            _tiles[x][y].SetFigure(temp);
        }
    }
}
for(size_t x = 0; x < 8; x++) {
    for(size_t y = 0; y < 3; y++) {

        if(x % 2 != y % 2) {
            auto temp = std::make_shared<Piece_t>(_figureRadius);
            // configure piece
            temp->SetBoard(this);
            temp->SetTexture(_blackPiece);
            temp->SetCoordinates(sf::Vector2u(x, y));
            temp->SetTeam(Team_e::black);
            _blackFigures.emplace_back(temp);
            // add piece into tile array
            _tiles[x][y].SetFigure(temp);
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

            // Get them proper color
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
    // Setup textures for everything
    if(!_whitePiece.loadFromFile("../textures/whitePiece.jpg"))
        throw std::runtime_error("\"whitePiece.jpg not found!\"");

    if(!_blackPiece.loadFromFile("../textures/blackPiece.jpg"))
        throw std::runtime_error("\"blackPiece.jpg not found!\"");

    if(!_blackKing.loadFromFile("../textures/blackKing.jpg"))
        throw std::runtime_error("\"blackKing.jpg not found!\"");

    if(!_whiteKing.loadFromFile("../textures/whiteKing.jpg"))
        throw std::runtime_error("\"_whiteKing.jpg not found!\"");

    _whitePiece.setSmooth(true);
    _blackPiece.setSmooth(true);
    _whiteKing.setSmooth(true);
    _blackKing.setSmooth(true);
}

} // namespace pamsi

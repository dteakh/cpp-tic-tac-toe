#ifndef GAME_HPP_
#define GAME_HPP_

#include <boost/config.hpp>
#include <vector>

namespace tictactoe {

struct Game {
    enum class Player { CROSSES, ZEROES };
    enum class Status { RUNNING, VICTORY, DRAW, ENDGAME };

    Game() = default;
    void makeMove(int row, int col);
    void setStatus(Status status);
    void updateStatus(int row, int col);
    std::vector<std::vector<char>> &getField();
    char getPlayer();
    void switchPlayer();
    [[nodiscard]] Game::Status getStatus() const;

private:
    std::vector<std::vector<char>> field =
        std::vector<std::vector<char>>(10, std::vector<char>(10, '.'));
    Player activePlayer = Player::ZEROES;
    Status status = Status::RUNNING;
    int cntTurns = 0;
};
}  // namespace tictactoe

#endif

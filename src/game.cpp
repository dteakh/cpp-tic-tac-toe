#include "game.hpp"

namespace tictactoe {
void Game::makeMove(int row, int col) {
    Game::field[row][col] = Game::getPlayer();
}

void Game::updateStatus(int row, int col) {
    Game::cntTurns++;
    char trg = Game::getPlayer();
    int cntRow = 0;
    int cntCol = 0;
    for (int i = 0; i < 10; ++i) {
        cntRow = Game::field[row][i] == trg ? cntRow + 1 : 0;
        cntCol = Game::field[i][col] == trg ? cntCol + 1 : 0;
        if (cntRow == 5 || cntCol == 5) {
            Game::status = Game::Status::VICTORY;
            return;
        }
    }
    int shift = std::min(row, col);
    int firstRow = row - shift;
    int firstCol = col - shift;
    int cnt = 0;
    for (int i = 0; firstRow + i < 9 && firstCol + i < 9; ++i) {
        cnt = Game::field[firstRow + i][firstCol + i] == trg ? cnt + 1 : 0;
        if (cnt == 5) {
            Game::status = Game::Status::VICTORY;
            return;
        }
    }
    shift = std::min(row, 9 - col);
    int secondRow = row - shift;
    int secondCol = col + shift;
    cnt = 0;
    for (int i = 0; secondRow + i < 9 && secondCol - i >= 0; ++i) {
        cnt = Game::field[secondRow + i][secondCol - i] == trg ? cnt + 1 : 0;
        if (cnt == 5) {
            Game::status = Game::Status::VICTORY;
            return;
        }
    }
    if (Game::cntTurns == 100) {
        Game::status = Game::Status::DRAW;
        return;
    }
}

std::vector<std::vector<char>> &Game::getField() {
    return Game::field;
}

char Game::getPlayer() {
    return Game::activePlayer == Game::Player::CROSSES ? 'X' : 'O';
}

void Game::switchPlayer() {
    Game::activePlayer = Game::activePlayer == Game::Player::CROSSES
                             ? Game::Player::ZEROES
                             : Game::Player::CROSSES;
}

void Game::setStatus(tictactoe::Game::Status newStatus) {
    Game::status = newStatus;
}

Game::Status Game::getStatus() const {
    return Game::status;
}
}  // namespace tictactoe

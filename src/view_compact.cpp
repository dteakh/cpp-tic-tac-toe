#include <algorithm>
#include <boost/config.hpp>
#include <iostream>
#include "view.hpp"

namespace tictactoe {
struct BOOST_SYMBOL_VISIBLE Compact : View {
    Compact() = default;

    std::pair<int, int> getPosition(std::string &str, Game &game) final {
        std::istringstream stream(str);
        int row = 0;
        int col = 0;
        stream >> row;
        if (stream.eof()) {
            return std::make_pair(-2, -2);
        }
        stream >> col;
        if (!stream.eof()) {
            std::string buffer;
            stream >> buffer;
            if (std::any_of(buffer.begin(), buffer.end(), [](char c) {
                    return c != ' ';
                })) {
                return std::make_pair(-2, -2);
            }
        }
        if (row == -1 && col == -1) {
            return std::make_pair(-1, -1);
        }
        if (row >= 0 && col >= 0 && row <= 9 && col <= 9 &&
            game.getField()[row][col] == '.') {
            return std::make_pair(row, col);
        }
        return std::make_pair(-2, -2);
    }

    void printField(std::vector<std::vector<char>> &field) const final {
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                std::cout << field[i][j];
            }
            std::cout << std::endl;
        }
    }
};

extern "C" BOOST_SYMBOL_EXPORT const Compact view;
const Compact view;
}  // namespace tictactoe

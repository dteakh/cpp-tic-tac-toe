#include <algorithm>
#include <boost/config.hpp>
#include <iostream>
#include "view.hpp"

namespace tictactoe {

struct BOOST_SYMBOL_VISIBLE Pretty : View {
    Pretty() = default;

    std::pair<int, int> getPosition(std::string &str, Game &game) final {
        std::istringstream stream(str);
        std::string position;
        stream >> position;
        if (position.size() != 2) {
            return std::make_pair(-2, -2);
        }
        if (!stream.eof()) {
            std::string buffer;
            stream >> buffer;
            if (std::any_of(buffer.begin(), buffer.end(), [](char c) {
                    return c != ' ';
                })) {
                return std::make_pair(-2, -2);
            }
        }
        int row = 9 - static_cast<int>(position[1] - '0');
        int col = static_cast<int>(position[0] - 'a');
        if (row >= 0 && col >= 0 && row <= 9 && col <= 9 &&
            game.getField()[row][col] == '.') {
            return std::make_pair(row, col);
        }
        return std::make_pair(-2, -2);
    }

    static void printBoarderLine() {
        std::cout << "  ";
        for (int i = 0; i < 10; ++i) {
            std::cout << "+----";
        }
        std::cout << "+" << std::endl;
    }

    static void printCell(bool top, char c) {
        std::cout << "| ";
        if (c == '.') {
            std::cout << "   ";
        } else if (c == 'X') {
            if (top) {
                std::cout << "\\/ ";
            } else {
                std::cout << "/\\ ";
            }
        } else if (c == 'O') {
            std::cout << "@@ ";
        }
    }

    static void printLine(int row, const std::vector<char> &line) {
        printBoarderLine();
        std::cout << row << " ";
        for (int i = 0; i < 10; ++i) {
            printCell(true, line[i]);
        }
        std::cout << "|" << std::endl;
        std::cout << "  ";
        for (int i = 0; i < 10; ++i) {
            printCell(false, line[i]);
        }
        std::cout << "|" << std::endl;
    }

    void printField(std::vector<std::vector<char>> &field) const final {
        for (int row = 9; row >= 0; --row) {
            printLine(row, field[9 - row]);
        }
        printBoarderLine();
        for (int i = 0; i < 10; ++i) {
            std::cout << "    " << static_cast<char>(i + 97);
        }
        std::cout << "   " << std::endl;
    }
};

extern "C" BOOST_SYMBOL_EXPORT const Pretty view;
const Pretty view;
}  // namespace tictactoe

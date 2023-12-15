#ifndef VIEW_HPP_
#define VIEW_HPP_

#include <boost/config.hpp>
#include <sstream>
#include <vector>
#include "game.hpp"

namespace tictactoe {
struct BOOST_SYMBOL_VISIBLE View {
    View(const View &) = delete;
    View(View &&) = delete;
    View &operator=(const View &) = delete;
    View &operator=(View &&) = delete;
    virtual ~View() = default;
    virtual std::pair<int, int> getPosition(
        std::string &str,
        Game &game
    ) = 0;  // if bad move return [-2, -2], if quitting game [-1, -1], [row,
            // col] othw
    virtual void printField(std::vector<std::vector<char>> &field) const = 0;

protected:
    View() = default;
};
}  // namespace tictactoe

#endif

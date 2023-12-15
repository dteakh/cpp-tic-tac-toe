#include <boost/dll/import.hpp>
#include <boost/version.hpp>
#include <iostream>
#include "game.hpp"
#include "handler.hpp"
#include "view.hpp"

#if BOOST_VERSION >= 107600
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import_symbol
#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import
#endif

// NOLINTNEXTLINE(bugprone-exception-escape)
int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 0;
    }
    namespace ttt = tictactoe;
    ttt::Game game;
    boost::shared_ptr<ttt::View> defaultView =
        boost_dll_import_symbol<ttt::View>(
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
            argv[1], "view", boost::dll::load_mode::append_decorations
        );
    ttt::Handler handler(game, defaultView);
    std::cout << '\n';
    defaultView->printField(game.getField());
    std::cout << game.getPlayer() << " move: ";
    handler.execute();
    return 0;
}

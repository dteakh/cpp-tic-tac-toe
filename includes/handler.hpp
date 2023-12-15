#ifndef HANDLER_HPP_
#define HANDLER_HPP_

#include <boost/config.hpp>
#include <boost/dll/import.hpp>
#include <boost/version.hpp>
#include "game.hpp"
#include "view.hpp"

#if BOOST_VERSION >= 107600
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import_symbol
#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import
#endif

namespace tictactoe {
struct BOOST_SYMBOL_VISIBLE Handler {
    Handler(Game &game, boost::shared_ptr<View> defaultView);
    void switchView(std::string &newView);
    void execute();

private:
    Game &game;
    boost::shared_ptr<View> activeView;
};
}  // namespace tictactoe

#endif

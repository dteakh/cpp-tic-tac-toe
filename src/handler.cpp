#include "handler.hpp"
#include <iostream>

namespace tictactoe {
Handler::Handler(tictactoe::Game &game, boost::shared_ptr<View> defaultView)
    : game(game), activeView(std::move(defaultView)) {
}

void Handler::switchView(std::string &newView) {
    activeView = boost_dll_import_symbol<View>(
        newView, "view", boost::dll::load_mode::append_decorations
    );
}

void Handler::execute() {
    std::string command;
    while (std::getline(std::cin, command)) {
        if (command == "view-compact" || command == "view-pretty") {
            switchView(command);
            activeView->printField(game.getField());
            std::cout << game.getPlayer() << " move: ";
            continue;
        }
        auto [row, col] = activeView->getPosition(command, game);
        if (row == -1 && col == -1) {
            game.setStatus(Game::Status::ENDGAME);
            return;
        }
        if (row == -2 && col == -2) {
            std::cout << "Bad move!\n" << game.getPlayer() << " move: ";
            continue;
        }
        std::cout << '\n';
        game.makeMove(row, col);
        game.updateStatus(row, col);
        Game::Status status = game.getStatus();
        if (status == Game::Status::VICTORY) {
            activeView->printField(game.getField());
            std::cout << game.getPlayer() << " wins!" << std::endl;
            return;
        } else if (status == Game::Status::DRAW) {
            std::cout << "Draw." << std::endl;
            return;
        }
        game.switchPlayer();
        activeView->printField(game.getField());
        std::cout << game.getPlayer() << " move: ";
    }
}
}  // namespace tictactoe

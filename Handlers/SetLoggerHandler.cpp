#include "SetLoggerHandler.h"
#include "../Facade/GameFacade.h"
#include <sstream>
#include <iostream>

SetLoggerHandler::SetLoggerHandler(std::shared_ptr<GameFacade> facade)
    : Handler(std::move(facade)) {
}

bool SetLoggerHandler::handle(const std::string& cmd) {
    std::istringstream iss(cmd);
    std::string keyword;
    std::string type;
    iss >> keyword >> type;

    if (keyword != "set_logger" || type.empty()) {
        return passToNext(cmd);
    }

    std::string filename = "game_log.txt";
    if (type == "file") {
        std::string maybeName;
        if (iss >> maybeName) {
            filename = maybeName;
        }
    }

    if (!facade_->setLoggerType(type, filename)) {
        std::cout << "[SetLoggerHandler] Не удалось установить логгер: " << type << "\n";
        return true;
    }

    std::cout << "[SetLoggerHandler] Логгер установлен: " << type;
    if (type == "file") {
        std::cout << " (" << filename << ")";
    }
    std::cout << "\n";
    return true;
}

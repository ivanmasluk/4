#include "SetFormatHandler.h"
#include "../Facade/GameFacade.h"
#include <sstream>
#include <iostream>

SetFormatHandler::SetFormatHandler(std::shared_ptr<GameFacade> facade)
    : Handler(std::move(facade)) {
}

bool SetFormatHandler::handle(const std::string& cmd) {
    std::istringstream iss(cmd);
    std::string keyword;
    std::string type;
    iss >> keyword >> type;

    if (keyword != "set_format" || type.empty()) {
        return passToNext(cmd);
    }

    if (!facade_->setFormatType(type)) {
        std::cout << "[SetFormatHandler] Не удалось установить формат: " << type << "\n";
        return true;
    }

    std::cout << "[SetFormatHandler] Формат установлен: " << type << "\n";
    return true;
}

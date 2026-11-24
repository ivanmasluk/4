#include "CreateHandler.h"
#include "../Facade/GameFacade.h"
#include <sstream>

CreateHandler::CreateHandler(std::shared_ptr<GameFacade> facade)
    : Handler(std::move(facade)) {
}

bool CreateHandler::handle(const std::string& cmd) {
    std::istringstream in(cmd);
    std::string a, b, c, type, at;
    char comma = 0;
    int x = 0;
    int y = 0;

    if (!(in >> a >> b >> type >> at >> x >> comma >> y)) {
        return passToNext(cmd);
    }

    if (a == "create" && b == "unit" && at == "at" && comma == ',') {
        return facade_->createUnit(type, x, y);
    }

    return passToNext(cmd);
}

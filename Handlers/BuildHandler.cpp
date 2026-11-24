#include "BuildHandler.h"
#include "../Facade/GameFacade.h"
#include <sstream>

BuildHandler::BuildHandler(std::shared_ptr<GameFacade> facade)
    : Handler(std::move(facade)) {
}

bool BuildHandler::handle(const std::string& cmd) {
    std::istringstream in(cmd);
    std::string a, type, at;
    char comma = 0;
    int x = 0;
    int y = 0;

    if (!(in >> a >> type >> at >> x >> comma >> y)) {
        return passToNext(cmd);
    }

    if (a == "build" && at == "at" && comma == ',') {
        return facade_->buildBuilding(type, x, y);
    }

    return passToNext(cmd);
}

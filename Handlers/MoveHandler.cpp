#include "MoveHandler.h"
#include "../Facade/GameFacade.h"
#include <sstream>

MoveHandler::MoveHandler(std::shared_ptr<GameFacade> facade)
    : Handler(std::move(facade)) {
}

bool MoveHandler::handle(const std::string& cmd) {
    std::istringstream in(cmd);
    std::string a, b, to;
    char comma = 0;
    int id = 0;
    int x = 0;
    int y = 0;

    if (!(in >> a >> b >> id >> to >> x >> comma >> y)) {
        return passToNext(cmd);
    }

    if (a == "move" && b == "unit" && to == "to" && comma == ',') {
        return facade_->moveUnit(id, x, y);
    }

    return passToNext(cmd);
}

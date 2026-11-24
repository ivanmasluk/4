#include "ProduceHandler.h"
#include "../Facade/GameFacade.h"
#include <sstream>

ProduceHandler::ProduceHandler(std::shared_ptr<GameFacade> facade)
    : Handler(std::move(facade)) {
}

bool ProduceHandler::handle(const std::string& cmd) {
    std::istringstream in(cmd);
    std::string a, unitType, inWord;
    int buildingId = 0;

    if (!(in >> a >> unitType >> inWord >> buildingId)) {
        return passToNext(cmd);
    }

    if (a == "produce" && inWord == "in") {
        return facade_->produceUnit(unitType, buildingId);
    }

    return passToNext(cmd);
}

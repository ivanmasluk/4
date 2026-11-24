#include "HealHandler.h"
#include "../Facade/GameFacade.h"
#include <sstream>

HealHandler::HealHandler(std::shared_ptr<GameFacade> facade)
    : Handler(std::move(facade)) {
}

bool HealHandler::handle(const std::string& cmd) {
    std::istringstream in(cmd);
    std::string a, b, targetWord;
    int unitId = 0;
    int buildingId = 0;

    if (!(in >> a >> b >> unitId >> targetWord >> buildingId)) {
        return passToNext(cmd);
    }

    if (a == "heal" && b == "unit" && targetWord == "target") {
        return facade_->heal(unitId, buildingId);
    }

    return passToNext(cmd);
}

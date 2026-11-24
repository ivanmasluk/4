#include "StatsHandler.h"
#include "../Facade/GameFacade.h"
#include <sstream>

StatsHandler::StatsHandler(std::shared_ptr<GameFacade> facade)
    : Handler(std::move(facade)) {
}

bool StatsHandler::handle(const std::string& cmd) {
    std::istringstream in(cmd);
    std::string a, mode;

    if (!(in >> a)) {
        return passToNext(cmd);
    }

    if (a != "stats") {
        return passToNext(cmd);
    }

    if (in >> mode) {
        facade_->getStats(mode);
    } else {
        facade_->getStats("all");
    }
    return true;
}

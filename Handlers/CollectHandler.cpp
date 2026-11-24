#include "CollectHandler.h"
#include "../Facade/GameFacade.h"
#include <sstream>

CollectHandler::CollectHandler(std::shared_ptr<GameFacade> facade)
    : Handler(std::move(facade)) {
}

bool CollectHandler::handle(const std::string& cmd) {
    std::istringstream in(cmd);
    std::string a, b, fromWord;
    int unitId = 0;
    int resourceId = 0;

    if (!(in >> a >> b >> unitId >> fromWord >> resourceId)) {
        return passToNext(cmd);
    }

    if (a == "collect" && b == "unit" && fromWord == "from") {
        return facade_->collectResource(unitId, resourceId);
    }

    return passToNext(cmd);
}

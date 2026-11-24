#include "AttackHandler.h"
#include "../Facade/GameFacade.h"
#include <sstream>

AttackHandler::AttackHandler(std::shared_ptr<GameFacade> facade)
    : Handler(std::move(facade)) {
}

bool AttackHandler::handle(const std::string& cmd) {
    std::istringstream in(cmd);
    std::string a, b, targetWord;
    int attackerId = 0;
    int targetId = 0;

    if (!(in >> a >> b >> attackerId >> targetWord >> targetId)) {
        return passToNext(cmd);
    }

    if (a == "attack" && b == "unit" && targetWord == "target") {
        return facade_->attack(attackerId, targetId);
    }

    return passToNext(cmd);
}

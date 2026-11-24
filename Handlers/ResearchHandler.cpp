#include "ResearchHandler.h"
#include "../Facade/GameFacade.h"
#include <sstream>

ResearchHandler::ResearchHandler(std::shared_ptr<GameFacade> facade)
    : Handler(std::move(facade)) {
}

bool ResearchHandler::handle(const std::string& cmd) {
    std::istringstream in(cmd);
    std::string a, tech;

    if (!(in >> a >> tech)) {
        return passToNext(cmd);
    }

    if (a == "research") {
        return facade_->research(tech);
    }

    return passToNext(cmd);
}

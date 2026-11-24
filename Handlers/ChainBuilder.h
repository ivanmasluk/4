#pragma once

#include "CreateHandler.h"
#include "MoveHandler.h"
#include "AttackHandler.h"
#include "CollectHandler.h"
#include "HealHandler.h"
#include "BuildHandler.h"
#include "ResearchHandler.h"
#include "ProduceHandler.h"
#include "StatsHandler.h"
#include "SetLoggerHandler.h"
#include "SetFormatHandler.h"
#include <memory>

inline std::shared_ptr<Handler> buildHandlerChain(std::shared_ptr<GameFacade> facade) {
    auto createH     = std::make_shared<CreateHandler>(facade);
    auto moveH       = std::make_shared<MoveHandler>(facade);
    auto attackH     = std::make_shared<AttackHandler>(facade);
    auto collectH    = std::make_shared<CollectHandler>(facade);
    auto healH       = std::make_shared<HealHandler>(facade);
    auto buildH      = std::make_shared<BuildHandler>(facade);
    auto researchH   = std::make_shared<ResearchHandler>(facade);
    auto produceH    = std::make_shared<ProduceHandler>(facade);
    auto statsH      = std::make_shared<StatsHandler>(facade);
    auto setLoggerH  = std::make_shared<SetLoggerHandler>(facade);
    auto setFormatH  = std::make_shared<SetFormatHandler>(facade);

    setLoggerH->setNext(setFormatH);
    setFormatH->setNext(createH);

    createH->setNext(moveH);
    moveH->setNext(attackH);
    attackH->setNext(collectH);
    collectH->setNext(healH);
    healH->setNext(buildH);
    buildH->setNext(researchH);
    researchH->setNext(produceH);
    produceH->setNext(statsH);

    return setLoggerH;
}

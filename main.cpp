#include <iostream>
#include <memory>
#include <string>
#include <clocale>

#ifdef _WIN32
#include <windows.h>
#endif

#include "GameField.h"
#include "Terrain/TerrainMap.h"
#include "Terrain/TerrainType.h"
#include "Base/Base.h"
#include "Factories/InfantryFactory.h"
#include "Factories/ArcherFactory.h"
#include "Factories/CavalryFactory.h"
#include "Units/Unit.h"

#include "Systems/ResourceSystem.h"
#include "Systems/CombatSystem.h"
#include "Systems/UnitManager.h"
#include "Systems/BuildingManager.h"
#include "Mediator/GameMediator.h"
#include "Facade/GameFacade.h"
#include "Handlers/ChainBuilder.h"
#include "NeutralObjects/NeutralOperators.h"
#include "NeutralObjects/Trap.h"
#include "Strategies/DamageStrategy.h"

static const int MAP_WIDTH = 22;
static const int MAP_HEIGHT = 14;

static const char* ANSI_RESET = "\033[0m";
static const char* ANSI_GREEN = "\033[92m";
static const char* ANSI_DARK_GREEN = "\033[32m";
static const char* ANSI_GRAY = "\033[90m";
static const char* ANSI_SWAMP = "\033[36m";
static const char* ANSI_YELLOW = "\033[93m";
static const char* ANSI_WHITE = "\033[97m";
static const char* ANSI_RED = "\033[91m";

static void enableConsoleColors() {
#ifdef _WIN32
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (handle == INVALID_HANDLE_VALUE) {
        return;
    }
    DWORD mode = 0;
    if (GetConsoleMode(handle, &mode)) {
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(handle, mode);
    }
#endif
}

static std::string mapUnitAlias(const std::string& type) {
    if (type == "infantry") {
        return "Swordsman";
    }
    if (type == "spearman") {
        return "Spearman";
    }
    if (type == "archer") {
        return "LightArcher";
    }
    if (type == "heavy_archer") {
        return "HeavyArcher";
    }
    if (type == "cavalry") {
        return "HorseArcher";
    }
    if (type == "cataphract") {
        return "Cataphract";
    }
    return type;
}

static bool isBaseMarker(int x, int y) {
    if (x == 0 && y == MAP_HEIGHT / 2) {
        return true;
    }
    if (x == MAP_WIDTH - 1 && y == MAP_HEIGHT / 2) {
        return true;
    }
    return false;
}

static void fillFixedTerrain(TerrainMap& map) {
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            map.setTerrain(x, y, TerrainType::Plains);
        }
    }

    for (int y = 1; y <= 4; ++y) {
        for (int x = 8; x <= 13; ++x) {
            map.setTerrain(x, y, TerrainType::Mountains);
        }
    }

    for (int y = 9; y <= 12; ++y) {
        for (int x = 4; x <= 9; ++x) {
            map.setTerrain(x, y, TerrainType::Swamp);
        }
    }

    for (int y = 3; y <= 8; ++y) {
        for (int x = 15; x <= 18; ++x) {
            if (!(x >= MAP_WIDTH - 2)) {
                map.setTerrain(x, y, TerrainType::Forest);
            }
        }
    }

    for (int y = 0; y < MAP_HEIGHT; ++y) {
        map.setTerrain(0, y, TerrainType::Plains);
        map.setTerrain(1, y, TerrainType::Plains);
        map.setTerrain(MAP_WIDTH - 2, y, TerrainType::Plains);
        map.setTerrain(MAP_WIDTH - 1, y, TerrainType::Plains);
    }
}

static void printColoredSymbol(char symbol) {
    if (symbol == '.') {
        std::cout << ANSI_GREEN << ". " << ANSI_RESET;
    } else if (symbol == '*') {
        std::cout << ANSI_DARK_GREEN << "* " << ANSI_RESET;
    } else if (symbol == '~') {
        std::cout << ANSI_SWAMP << "~ " << ANSI_RESET;
    } else if (symbol == '^') {
        std::cout << ANSI_GRAY << "^ " << ANSI_RESET;
    } else if (symbol == 'B') {
        std::cout << ANSI_YELLOW << "B " << ANSI_RESET;
    } else {
        std::cout << ANSI_WHITE << symbol << ' ' << ANSI_RESET;
    }
}

static void printMap(const GameField& field, const TerrainMap& terrainMap) {
    const int width = field.getWidth();
    const int height = field.getHeight();

    std::cout << "Карта: "
              << ANSI_GREEN << ". равнина " << ANSI_RESET
              << ANSI_DARK_GREEN << "* лес " << ANSI_RESET
              << ANSI_SWAMP << "~ болото " << ANSI_RESET
              << ANSI_GRAY << "^ горы " << ANSI_RESET
              << ANSI_YELLOW << "B база " << ANSI_RESET
              << "буква = юнит\n";

    for (int i = 0; i < width + 2; ++i) {
        std::cout << ANSI_RED << "X " << ANSI_RESET;
    }
    std::cout << '\n';

    for (int y = 0; y < height; ++y) {
        std::cout << ANSI_RED << "X " << ANSI_RESET;
        for (int x = 0; x < width; ++x) {
            const Unit* unit = field.getUnit(x, y);
            if (unit != nullptr) {
                std::cout << ANSI_WHITE << unit->getType()[0] << ' ' << ANSI_RESET;
            } else if (isBaseMarker(x, y)) {
                printColoredSymbol('B');
            } else {
                printColoredSymbol(terrainMap.getSymbol(x, y));
            }
        }
        std::cout << ANSI_RED << "X\n" << ANSI_RESET;
    }

    for (int i = 0; i < width + 2; ++i) {
        std::cout << ANSI_RED << "X " << ANSI_RESET;
    }
    std::cout << '\n';
}

static bool shouldRefreshMap(const std::string& line) {
    return line.rfind("create ", 0) == 0
        || line.rfind("move ", 0) == 0
        || line.rfind("produce ", 0) == 0
        || line.rfind("attack ", 0) == 0
        || line == "undo";
}

static void printHelp() {
    std::cout << "Команды:\n"
              << "  create unit <type> at <x>,<y>\n"
              << "  move unit <id> to <x>,<y>\n"
              << "  attack unit <id> target <id>\n"
              << "  collect unit <id> from <resourceId>\n"
              << "  heal unit <id> target <buildingId>\n"
              << "  build <barracks|hospital|laboratory|warehouse> at <x>,<y>\n"
              << "  research <tech>\n"
              << "  distribute <wood|metal|energy> to <buildingType> <amount>\n"
              << "  produce <type> in <buildingId>\n"
              << "  stats [units|buildings|resources]\n"
              << "  set_logger <console|file [name]|null>\n"
              << "  set_format <text|json|csv>\n"
              << "  map\n"
              << "  undo\n"
              << "  help\n"
              << "  exit\n"
              << "Типы юнитов: Swordsman Spearman LightArcher HeavyArcher Cataphract HorseArcher\n"
              << "  (алиасы: infantry spearman archer heavy_archer cavalry cataphract)\n"
              << "Карта всегда одна и та же: слева/справа зоны баз (B),\n"
              << "в центре сверху горы (^), снизу слева болото (~), справа лес (*).\n";
}

int main() {
    setlocale(LC_ALL, ".utf8");
    enableConsoleColors();

    auto field = std::make_shared<GameField>(MAP_WIDTH, MAP_HEIGHT, 40);
    auto terrainMap = std::make_shared<TerrainMap>(MAP_WIDTH, MAP_HEIGHT);
    fillFixedTerrain(*terrainMap);

    auto base = std::make_shared<Base>(0, MAP_HEIGHT / 2, 500, 20, 5, 100);
    auto resources = std::make_shared<ResourceSystem>(200, 200, 200);
    auto combat = std::make_shared<CombatSystem>();
    auto unitManager = std::make_shared<UnitManager>(field, base);
    auto buildingManager = std::make_shared<BuildingManager>();

    InfantryFactory infantryFactory;
    ArcherFactory archerFactory;
    CavalryFactory cavalryFactory;

    unitManager->setCreateUnitFunction(
        [&](const std::string& type, int x, int y) {
            const std::string mapped = mapUnitAlias(type);

            if (mapped == "Swordsman" || mapped == "Spearman") {
                return base->createUnit(infantryFactory, mapped, *field, x, y);
            }
            if (mapped == "LightArcher" || mapped == "HeavyArcher") {
                return base->createUnit(archerFactory, mapped, *field, x, y);
            }
            if (mapped == "Cataphract" || mapped == "HorseArcher") {
                return base->createUnit(cavalryFactory, mapped, *field, x, y);
            }

            std::cout << "[main] Неизвестный тип юнита: " << type << "\n";
            return false;
        }
    );

    auto mediator = std::make_shared<GameMediator>(
        base, field, terrainMap, unitManager, buildingManager, resources, combat
    );

    auto facade = std::make_shared<GameFacade>(mediator);
    facade->setHandlerChain(buildHandlerChain(facade));
    mediator->setLogger(facade->getLogger());
    setNeutralLogger(facade->getLogger());

    std::cout << "ЛР3: Facade + Mediator + Command + Chain + Logging\n";
    printHelp();

    if (mediator->createUnit("Swordsman", 1, MAP_HEIGHT / 2)) {
        std::cout << "Демо: создан Swordsman у левой базы\n";
    }

    printMap(*field, *terrainMap);
    std::cout << "Введите команду:\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) {
            break;
        }

        if (line.empty()) {
            continue;
        }
        if (line == "exit" || line == "quit") {
            break;
        }
        if (line == "help") {
            printHelp();
            continue;
        }
        if (line == "map") {
            printMap(*field, *terrainMap);
            continue;
        }

        facade->processInput(line);

        if (shouldRefreshMap(line)) {
            printMap(*field, *terrainMap);
        }
    }

    return 0;
}

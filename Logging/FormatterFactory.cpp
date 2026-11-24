#include "FormatterFactory.h"
#include "TextFormatter.h"
#include "JsonFormatter.h"
#include "CsvFormatter.h"

std::shared_ptr<ILogFormatter> createFormatter(const std::string& type) {
    if (type == "text") {
        return std::make_shared<TextFormatter>();
    }
    if (type == "json") {
        return std::make_shared<JsonFormatter>();
    }
    if (type == "csv") {
        return std::make_shared<CsvFormatter>();
    }
    return nullptr;
}

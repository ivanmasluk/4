#pragma once

#include "ILogger.h"

#include <fstream>
#include <memory>
#include <string>

class FileLogger : public ILogger {
public:
    explicit FileLogger(const std::string& filename,
                        std::shared_ptr<ILogFormatter> formatter = nullptr);

    ~FileLogger() override;

    FileLogger(const FileLogger&) = delete;
    FileLogger& operator=(const FileLogger&) = delete;

    FileLogger(FileLogger&&) noexcept;
    FileLogger& operator=(FileLogger&&) noexcept;

    void log(const LogEvent& event) override;
    void setFormatter(std::shared_ptr<ILogFormatter> formatter) override;

    bool isOpen() const;

private:
    std::ofstream file_;
    std::shared_ptr<ILogFormatter> formatter_;
    std::string filename_;
};

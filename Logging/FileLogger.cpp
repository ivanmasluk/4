#include "FileLogger.h"
#include "TextFormatter.h"

#include <iostream>
#include <utility>

FileLogger::FileLogger(const std::string& filename,
                       std::shared_ptr<ILogFormatter> formatter)
    : filename_(filename)
{
    if (formatter) {
        formatter_ = std::move(formatter);
    } else {
        formatter_ = std::make_shared<TextFormatter>();
    }

    file_.open(filename_, std::ios::out | std::ios::app);
    if (!file_.is_open()) {
        std::cerr << "[FileLogger] Не удалось открыть файл: " << filename_ << std::endl;
    }
}

FileLogger::~FileLogger() {
    if (file_.is_open()) {
        file_.flush();
        file_.close();
    }
}

FileLogger::FileLogger(FileLogger&& other) noexcept
    : file_(std::move(other.file_))
    , formatter_(std::move(other.formatter_))
    , filename_(std::move(other.filename_))
{
}

FileLogger& FileLogger::operator=(FileLogger&& other) noexcept {
    if (this != &other) {
        if (file_.is_open()) {
            file_.close();
        }
        file_ = std::move(other.file_);
        formatter_ = std::move(other.formatter_);
        filename_ = std::move(other.filename_);
    }
    return *this;
}

void FileLogger::log(const LogEvent& event) {
    if (!file_.is_open() || !formatter_) {
        return;
    }
    file_ << formatter_->format(event) << '\n';
    file_.flush();
}

void FileLogger::setFormatter(std::shared_ptr<ILogFormatter> formatter) {
    formatter_ = std::move(formatter);
}

bool FileLogger::isOpen() const {
    return file_.is_open();
}

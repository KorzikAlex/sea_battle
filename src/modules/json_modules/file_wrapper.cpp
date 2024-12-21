#include "json_modules/file_wrapper.hpp"

FileWrapper::FileWrapper(const std::string& file_name): file_(file_name) {
}

FileWrapper::~FileWrapper() {
    if (this->file_.is_open()) this->file_.close();
}

void FileWrapper::read(nlohmann::json& json_file) {
    if (!this->file_.is_open() || !this->file_.good())
        throw UnableToOpenFileException();
    this->file_ >> json_file;
}

void FileWrapper::write(const nlohmann::json& json_file) {
    if (!this->file_.is_open() || !this->file_.good())
        throw UnableToOpenFileException();
    this->file_ << json_file.dump(4);
}

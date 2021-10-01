#include <improc/infrastructure/file.hpp>

/**
 * @brief Construct a new improc::File object
 * 
 */
improc::File::File() {}

/**
 * @brief Construct a new improc::File object
 * 
 * @param filepath 
 */
improc::File::File(const std::string& filepath) 
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Creating File object..." );
    this->set_filepath(std::move(filepath));
}

/**
 * @brief Set the filepath object
 * 
 * @param filepath 
 */
void improc::File::set_filepath(const std::string& filepath)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Setting filepath {}...",filepath );
    if (improc::File::IsFile(filepath) == false)
    {
        SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_03: Invalid filepath {}.",filepath );
        throw improc::invalid_filepath();
    }
    this->filepath_ = std::filesystem::path(std::move(filepath));
}

/**
 * @brief Get the filepath object
 * 
 * @return std::string
 */
std::string improc::File::get_filepath() const
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtaining filepath..." );
    return this->filepath_.string();
}

/**
 * @brief Get the filename object
 * 
 * @return std::string
 */
std::string improc::File::get_filename() const
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtaining filename..." );
    return this->filepath_.filename().string();
}

/**
 * @brief Get the extension object
 * 
 * @return std::string
 */
std::string improc::File::get_extension() const
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Obtaining extension..." );
    return this->filepath_.extension().string();
}

/**
 * @brief Read the content of a file
 * 
 * @return std::string 
 */
std::string improc::File::Read() const
{
    return improc::File::Read(this->filepath_.string());
}

/**
 * @brief Remove a file
 * 
 */
void improc::File::Remove() const
{
    std::filesystem::remove(this->filepath_);
}

/**
 * @brief Check if file exists on the system
 * 
 * @return true 
 * @return false 
 */
bool improc::File::Exists() const
{
    return std::filesystem::exists(this->filepath_);
}

/**
 * @brief Read the content of a filepath
 * 
 * @param filepath 
 * @return std::string 
 */
std::string improc::File::Read(const std::string& filepath)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Reading content from filepath {}...",filepath );
    if (improc::File::IsFile(filepath) == false) {
        SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_01: Filepath {} does not exist.",filepath );
        throw improc::invalid_filepath();
    }
 
    std::ifstream file_stream(filepath,std::ifstream::binary);
    if (file_stream.is_open() == false) {
        SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_02: Error opening filepath {}.",filepath );
        throw improc::invalid_filepath();
    }

    std::string file_content ( (std::istreambuf_iterator<char>(file_stream))
                             , std::istreambuf_iterator<char>() );
    file_stream.close();
    return file_content;
}

/**
 * @brief Remove a filepath
 * 
 * @param filepath 
 */
void improc::File::Remove(const std::string& filepath)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Removing filepath {}...",filepath );
    std::filesystem::remove(std::move(filepath));
}

/**
 * @brief Check if filepath exists on the system
 * 
 * @param filepath 
 * @return true 
 * @return false 
 */
bool improc::File::Exists(const std::string& filepath)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Checking if filepath {} exists...",filepath );
    return std::filesystem::exists(std::move(filepath));
}

/**
 * @brief Check if filepath exists and is a file
 * 
 * @param filepath 
 * @return true 
 * @return false 
 */
bool improc::File::IsFile(const std::string& filepath)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Checking if filepath {} exists and is a file...",filepath );
    return std::filesystem::is_regular_file(std::move(filepath));
}

/**
 * @brief Construct a new improc::JsonFile object
 * 
 */
improc::JsonFile::JsonFile() : improc::File() {}

/**
 * @brief Construct a new improc::JsonFile object
 * 
 * @param filepath 
 */
improc::JsonFile::JsonFile(const std::string& filepath)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Creating JsonFile object..." );
    this->set_filepath(std::move(filepath));
}

/**
 * @brief Set the filepath object
 * 
 * @param filepath 
 */
void improc::JsonFile::set_filepath(const std::string& filepath)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Setting json filepath {}...",filepath );
    improc::File json_file {std::move(filepath)};
    if (improc::JsonFile::IsExtensionValid(json_file) == false)
    {
        SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_01: Invalid json extension {}.",json_file.get_extension() );
        throw improc::invalid_filepath();
    }
    this->File::operator=(std::move(json_file));
}

/**
 * @brief Read the content of a json file
 * 
 * @return Json::Value 
 */
Json::Value improc::JsonFile::Read() const
{
    return improc::JsonFile::Read(this->get_filepath());
}

/**
 * @brief Read the content of a json filepath
 * 
 * @param filepath 
 * @return Json::Value 
 */
Json::Value improc::JsonFile::Read(const std::string& filepath)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Reading content from json filepath {}...",filepath );
    improc::File json_file {std::move(filepath)};
    if (improc::JsonFile::IsExtensionValid(json_file) == false)
    {
        SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_02: Invalid json extension {}.",json_file.get_extension() );
        throw improc::invalid_filepath();
    }

    std::string json_content = json_file.Read();
    
    Json::Value             json_root;
    Json::CharReaderBuilder json_char_builder;
 
    std::unique_ptr<Json::CharReader> json_reader(json_char_builder.newCharReader());
    std::string error;
    bool is_parse_successful = json_reader->parse( json_content.c_str()
                                                 , json_content.c_str() + json_content.length()
                                                 , &json_root
                                                 , &error );
 
    if (is_parse_successful == false) {
        SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                          , spdlog::level::err
                          , "ERROR_03: Error parsing json file {}: {}.",json_file.get_filepath(),error );
        throw improc::file_processing_error();
    }
    return json_root;
}

/**
 * @brief Check if the filepath's extension is a valid json extension
 * 
 * @param filepath 
 * @return true 
 * @return false 
 */
inline bool improc::JsonFile::IsExtensionValid(const improc::File& json_file)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Checking if json file {} has valid extension...",json_file.get_filepath());
    const std::string kJsonExtension = ".json";
    return json_file.get_extension() == kJsonExtension;
}

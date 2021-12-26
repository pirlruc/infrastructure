#include <improc/infrastructure/filesystem/file.hpp>

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
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating File object...");
    this->set_filepath(std::move(filepath));
}

/**
 * @brief Set the filepath object
 * 
 * @param filepath 
 */
improc::File& improc::File::set_filepath(const std::string& filepath)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Setting filepath {}...",filepath);
    if (improc::File::IsFile(filepath) == false)
    {
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_01: Invalid filepath {}.",filepath);
        throw improc::invalid_filepath();
    }
    this->filepath_ = std::filesystem::path(std::move(filepath));
    return (*this);
}

/**
 * @brief Get the filepath object
 * 
 * @return std::string
 */
std::string improc::File::get_filepath() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Obtaining filepath...");
    return this->filepath_.string();
}

/**
 * @brief Get the filename object
 * 
 * @return std::string
 */
std::string improc::File::get_filename() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Obtaining filename...");
    return this->filepath_.filename().string();
}

/**
 * @brief Get the extension object
 * 
 * @return std::string
 */
std::string improc::File::get_extension() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Obtaining extension...");
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
 * @return true if the file was deleted
 * @return false if the file did not exist
 */
bool improc::File::Remove() const
{
    return std::filesystem::remove(this->filepath_);
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
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Reading content from filepath {}...",filepath);
    if (improc::File::IsFile(filepath) == false) {
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_02: Filepath {} does not exist.",filepath);
        throw improc::invalid_filepath();
    }
 
    std::ifstream file_stream(filepath,std::ifstream::binary);
    if (file_stream.is_open() == false) {
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_03: Error opening filepath {}.",filepath);
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
bool improc::File::Remove(const std::string& filepath)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Removing filepath {}...",filepath);
    return std::filesystem::remove(std::move(filepath));
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
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Checking if filepath {} exists...",filepath);
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
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Checking if filepath {} exists and is a file...",filepath);
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
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating JsonFile object...");
    this->set_filepath(std::move(filepath));
}

/**
 * @brief Set the filepath object
 * 
 * @param filepath 
 */
improc::JsonFile& improc::JsonFile::set_filepath(const std::string& filepath)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Setting json filepath {}...",filepath);
    improc::File json_file {std::move(filepath)};
    if (improc::JsonFile::IsExtensionValid(json_file) == false)
    {
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_01: Invalid json extension {}.",json_file.get_extension());
        throw improc::invalid_filepath();
    }
    this->File::operator=(std::move(json_file));
    return (*this);
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
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Reading content from json filepath {}...",filepath);
    improc::File json_file {std::move(filepath)};
    if (improc::JsonFile::IsExtensionValid(json_file) == false)
    {
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR  ( "ERROR_02: Invalid json extension {}."
                                            , json_file.get_extension() );
        throw improc::invalid_filepath();
    }

    std::string json_content_str = json_file.Read();
    Json::Value json_content     = improc::JsonString::Parse(json_content_str);
    return json_content;
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
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE  ( "Checking if json file {} has valid extension..."
                                        , json_file.get_filepath() );
    static const std::string kJsonExtension = ".json";
    return json_file.get_extension() == kJsonExtension;
}

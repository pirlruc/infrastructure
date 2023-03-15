#include <improc/infrastructure/filesystem/file.hpp>

/**
 * @brief Construct a new improc::BaseFile object
 * 
 */
improc::BaseFile::BaseFile() {}

/**
 * @brief Construct a new improc::BaseFile object
 * 
 * @param filepath 
 */
improc::BaseFile::BaseFile(const std::string& filepath) 
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating BaseFile object using string...");
    this->set_filepath(std::move(filepath));
}

/**
 * @brief Construct a new improc::BaseFile object
 * 
 * @param filepath 
 */
improc::BaseFile::BaseFile(const std::filesystem::path& filepath) 
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating BaseFile object using path...");
    this->set_filepath(std::move(filepath));
}

/**
 * @brief Construct a new improc::BaseFile object
 * 
 * @param filepath_json - json structure with filepath
 * @param application_folder
 */
improc::BaseFile::BaseFile(const Json::Value& filepath_json,const std::optional<std::string>& application_folder) 
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating BaseFile object using json...");
    std::filesystem::path    filepath     = std::move(application_folder.value_or(""));
    std::vector<std::string> folders_json = improc::json::ReadVector<std::string>(std::move(filepath_json));
    std::for_each(folders_json.begin(),folders_json.end(), [&filepath] (const std::string& folder) {filepath /= std::move(folder);});
    this->set_filepath(std::move(filepath));
}

/**
 * @brief Get the filepath object
 * 
 * @return std::string
 */
std::string improc::BaseFile::get_filepath() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Obtaining filepath...");
    return this->filepath_.string();
}

/**
 * @brief Get the filename object
 * 
 * @return std::string
 */
std::string improc::BaseFile::get_filename() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Obtaining filename...");
    return this->filepath_.filename().string();
}

/**
 * @brief Get the extension object
 * 
 * @return std::string
 */
std::string improc::BaseFile::get_extension() const
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Obtaining extension...");
    return this->filepath_.extension().string();
}

/**
 * @brief Read the content of a file
 * 
 * @return std::string 
 */
std::string improc::BaseFile::Read() const
{
    return improc::BaseFile::Read(this->filepath_);
}

/**
 * @brief Remove a file
 * 
 * @return true if the file was deleted
 * @return false if the file did not exist
 */
bool improc::BaseFile::Remove() const
{
    return improc::BaseFile::Remove(this->filepath_);
}

/**
 * @brief Check if file exists on the system
 * 
 * @return true 
 * @return false 
 */
bool improc::BaseFile::Exists() const
{
    return improc::BaseFile::Exists(this->filepath_);
}

/**
 * @brief Construct a new improc::File object
 * 
 */
improc::File::File() : improc::BaseFile() {}

/**
 * @brief Construct a new improc::File object
 * 
 * @param filepath 
 */
improc::File::File(const std::string& filepath) : improc::BaseFile(std::move(filepath)) {}

/**
 * @brief Construct a new improc::File object
 * 
 * @param filepath 
 */
improc::File::File(const std::filesystem::path& filepath) : improc::BaseFile(std::move(filepath)) {}

/**
 * @brief Construct a new improc::File object
 * 
 * @param filepath_json - json structure with filepath
 * @param application_folder
 */
improc::File::File(const Json::Value& filepath_json,const std::optional<std::string>& application_folder) 
: improc::BaseFile(std::move(filepath_json),std::move(application_folder)) {}

/**
 * @brief Construct a new improc::JsonFile object
 * 
 */
improc::JsonFile::JsonFile() : improc::BaseFile() {}

/**
 * @brief Construct a new improc::JsonFile object
 * 
 * @param filepath 
 */
improc::JsonFile::JsonFile(const std::string& filepath) : improc::JsonFile()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating JsonFile object using string...");
    this->set_filepath(std::move(filepath));
}

/**
 * @brief Construct a new improc::JsonFile object
 * 
 * @param filepath 
 */
improc::JsonFile::JsonFile(const std::filesystem::path& filepath) : improc::JsonFile()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating JsonFile object using path...");
    this->set_filepath(std::move(filepath));
}

/**
 * @brief Construct a new improc::JsonFile object
 * 
 * @param filepath_json - json structure with filepath
 * @param application_folder
 */
improc::JsonFile::JsonFile(const Json::Value& filepath_json, const std::optional<std::string>& application_folder) : improc::JsonFile()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating JsonFile object using json...");
    this->set_filepath(improc::BaseFile(std::move(filepath_json),std::move(application_folder)).get_filepath());
}

/**
 * @brief Read the content of a json file
 * 
 * @return Json::Value 
 */
Json::Value improc::JsonFile::Read() const
{
    return improc::JsonFile::Read(this->filepath_);
}

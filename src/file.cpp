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
 * @brief Set the filepath object
 * 
 * @param filepath 
 */
improc::BaseFile& improc::BaseFile::set_filepath(const std::string& filepath)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Setting filepath {}...",filepath);
    if (improc::BaseFile::IsFile(filepath) == false)
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
 * @brief Read the content of a filepath
 * 
 * @param filepath 
 * @return std::string 
 */
std::string improc::BaseFile::Read(const std::string& filepath)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Reading content from filepath {}...",filepath);
    if (improc::BaseFile::IsFile(filepath) == false) {
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
bool improc::BaseFile::Remove(const std::string& filepath)
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
bool improc::BaseFile::Exists(const std::string& filepath)
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
bool improc::BaseFile::IsFile(const std::string& filepath)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Checking if filepath {} exists and is a file...",filepath);
    return std::filesystem::is_regular_file(std::move(filepath));
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
 * @param filepath_json - json structure with filepath
 * @param application_folder
 */
improc::File::File(const Json::Value& filepath_json,const std::optional<std::string>& application_folder) 
: improc::BaseFile(std::move(filepath_json),std::move(application_folder)) {}

/**
 * @brief Set the filepath object
 * 
 * @param filepath 
 */
improc::File& improc::File::set_filepath(const std::string& filepath)
{
    this->BaseFile::set_filepath(std::move(filepath));
    return (*this);
}

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
 * @param filepath_json - json structure with filepath
 * @param application_folder
 */
improc::JsonFile::JsonFile(const Json::Value& filepath_json, const std::optional<std::string>& application_folder) : improc::JsonFile()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating JsonFile object using json...");
    this->set_filepath(improc::BaseFile(std::move(filepath_json),std::move(application_folder)).get_filepath());
}

/**
 * @brief Set the filepath object
 * 
 * @param filepath 
 */
improc::JsonFile& improc::JsonFile::set_filepath(const std::string& filepath)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Setting json filepath {}...",filepath);
    improc::BaseFile json_file {std::move(filepath)};
    if (improc::JsonFile::IsExtensionValid(json_file) == false)
    {
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_01: Invalid json extension {}.",json_file.get_extension());
        throw improc::invalid_filepath();
    }
    this->BaseFile::operator=(std::move(json_file));
    return (*this);
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

/**
 * @brief Read the content of a json filepath
 * 
 * @param filepath 
 * @return Json::Value 
 */
Json::Value improc::JsonFile::Read(const std::string& filepath)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Reading content from json filepath {}...",filepath);
    improc::JsonFile {filepath};     // Validate if filepath extension is valid
    improc::BaseFile json_file {std::move(filepath)};
    std::string json_content_str = json_file.Read();
    return improc::JsonString().Parse(std::move(json_content_str));
}

/**
 * @brief Check if file extension is a valid json extension
 * 
 * @param json_file - file object
 * @return true if file extension is a valid json extension (i.e. .json)
 * @return false 
 */
inline bool improc::JsonFile::IsExtensionValid(const improc::BaseFile& json_file)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE  ( "Checking if json file {} has valid extension..."
                                        , json_file.get_filepath() );
    static const std::string kJsonExtension = ".json";
    return json_file.get_extension() == kJsonExtension;
}

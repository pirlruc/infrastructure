/**
 * @brief Set the filepath object
 * 
 * @tparam FilepathType - std::filesystem::path or std::string data types 
 * @param filepath 
 */
template<typename FilepathType>
improc::BaseFile& improc::BaseFile::set_filepath(const FilepathType& filepath)
{
    static_assert(improc::is_path_v<FilepathType>,"Filepath data type not valid for path");
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Setting filepath {}...",filepath);
    if (improc::BaseFile::IsFile(filepath) == false)
    {
        std::string error_message = "Invalid path for file: ";
        if constexpr (std::is_same_v<FilepathType,std::filesystem::path>)
        {
            error_message += filepath.string();
        }
        else
        {
            error_message += filepath;
        }
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_01: " + error_message);
        throw improc::value_error(std::move(error_message));
    }

    if constexpr (std::is_same_v<FilepathType,std::filesystem::path>)
    {
        this->filepath_ = std::move(filepath);
    }
    else
    {
        this->filepath_ = std::filesystem::path(std::move(filepath));
    }
    return (*this);
}

/**
 * @brief Read the content of a filepath
 * 
 * @tparam FilepathType - std::filesystem::path or std::string data types 
 * @param filepath 
 * @return std::string 
 */
template<typename FilepathType>
std::string improc::BaseFile::Read(const FilepathType& filepath)
{
    static_assert(improc::is_path_v<FilepathType>,"Filepath data type not valid for path");
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Reading content from filepath {}...",filepath);
    if (improc::BaseFile::IsFile(filepath) == false) 
    {
        std::string error_message {};
        if constexpr (std::is_same_v<FilepathType,std::filesystem::path>)
        {
            error_message = fmt::format("Filepath {} does not exist", filepath.string());
        }
        else
        {
            error_message = fmt::format("Filepath {} does not exist", filepath);
        }
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_02: " + error_message);
        throw improc::value_error(std::move(error_message));
    }
 
    std::ifstream file_stream(filepath,std::ifstream::binary);
    if (file_stream.is_open() == false) 
    {
        std::string error_message = "Error opening filepath ";
        if constexpr (std::is_same_v<FilepathType,std::filesystem::path>)
        {
            error_message += filepath.string();
        }
        else
        {
            error_message += filepath;
        }
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_03: " + error_message);
        throw improc::operating_system_error(std::move(error_message));
    }

    std::string file_content ( (std::istreambuf_iterator<char>(file_stream))
                             , std::istreambuf_iterator<char>() );
    file_stream.close();
    return file_content;
}

/**
 * @brief Remove a filepath
 * 
 * @tparam FilepathType - std::filesystem::path or std::string data types 
 * @param filepath 
 */
template<typename FilepathType>
bool improc::BaseFile::Remove(const FilepathType& filepath)
{
    static_assert(improc::is_path_v<FilepathType>,"Filepath data type not valid for path");
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Removing filepath {}...",filepath);
    return std::filesystem::remove(std::move(filepath));
}

/**
 * @brief Check if filepath exists on the system
 * 
 * @tparam FilepathType - std::filesystem::path or std::string data types 
 * @param filepath 
 * @return true 
 * @return false 
 */
template<typename FilepathType>
bool improc::BaseFile::Exists(const FilepathType& filepath)
{
    static_assert(improc::is_path_v<FilepathType>,"Filepath data type not valid for path");
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Checking if filepath {} exists...",filepath);
    return std::filesystem::exists(std::move(filepath));
}

/**
 * @brief Check if filepath exists and is a file
 * 
 * @tparam FilepathType - std::filesystem::path or std::string data types 
 * @param filepath 
 * @return true 
 * @return false 
 */
template<typename FilepathType>
bool improc::BaseFile::IsFile(const FilepathType& filepath)
{
    static_assert(improc::is_path_v<FilepathType>,"Filepath data type not valid for path");
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Checking if filepath {} exists and is a file...",filepath);
    return std::filesystem::is_regular_file(std::move(filepath));
}

/**
 * @brief Set the filepath object
 * 
 * @tparam FilepathType - std::filesystem::path or std::string data types 
 * @param filepath 
 */
template<typename FilepathType>
improc::File& improc::File::set_filepath(const FilepathType& filepath)
{
    static_assert(improc::is_path_v<FilepathType>,"Filepath data type not valid for path");
    this->BaseFile::set_filepath(std::move(filepath));
    return (*this);
}

/**
 * @brief Set the filepath object
 * 
 * @tparam FilepathType - std::filesystem::path or std::string data types 
 * @param filepath 
 */
template<typename FilepathType>
improc::JsonFile& improc::JsonFile::set_filepath(const FilepathType& filepath)
{
    static_assert(improc::is_path_v<FilepathType>,"Filepath data type not valid for path");
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Setting json filepath {}...",filepath);
    improc::BaseFile json_file {};
    json_file.set_filepath(std::move(filepath));
    if (improc::JsonFile::IsExtensionValid(json_file) == false)
    {
        std::string error_message = "Invalid json extension " + json_file.get_extension();
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR("ERROR_01: " + error_message);
        throw improc::value_error(std::move(error_message));
    }
    this->BaseFile::operator=(std::move(json_file));
    return (*this);
}

/**
 * @brief Read the content of a json filepath
 * 
 * @tparam FilepathType - std::filesystem::path or std::string data types 
 * @param filepath 
 * @return Json::Value 
 */
template<typename FilepathType>
Json::Value improc::JsonFile::Read(const FilepathType& filepath)
{
    static_assert(improc::is_path_v<FilepathType>,"Filepath data type not valid for path");
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Reading content from json filepath {}...",filepath);
    improc::JsonFile {filepath};     // Validate if filepath extension is valid
    improc::BaseFile json_file {std::move(filepath)};
    std::string json_content_str = json_file.Read();
    return improc::JsonString().Parse(std::move(json_content_str));
}

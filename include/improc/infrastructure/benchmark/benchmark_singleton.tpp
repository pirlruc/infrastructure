/**
 * @brief Construct a new improc::BenchmarkSingleton<BenchmarkType> object
 * 
 * @tparam BenchmarkType - Data type of the benchmark being created
 * @param benchmark_logger 
 */
template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>::BenchmarkSingleton(std::shared_ptr<spdlog::logger>&& benchmark_logger) 
: LoggerSingleton<BenchmarkType>(std::move(benchmark_logger)) 
, is_created_(false)
, keys_(std::unordered_set<std::string>())
, line_content_(std::unordered_map<std::string,std::string>())
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Creating benchmark logger...");
    this->data()->set_level(spdlog::level::critical);
    this->data()->set_pattern("%n;%v");
}

/**
 * @brief Construct a new improc::BenchmarkSingleton<BenchmarkType> object
 * 
 * @tparam BenchmarkType - Data type of the benchmark being created
 * @param keys - Benchmark keys. Must be defined before writing information to the benchmark
 */
template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::AddKeys(const std::unordered_set<std::string>& keys) 
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Adding keys to benchmark...");
    if (this->is_created_ == true)
    {
        IMPROC_INFRASTRUCTURE_LOGGER_ERROR ("ERROR_01: Cannot change keys after benchmark has been created.");
        throw improc::benchmark_keys_cannot_change();
    }
    this->keys_.insert(keys.begin(),keys.end());
    this->InitializeLineContent(std::move(keys));
    return (*this);
}

/**
 * @brief Initialize benchmark line content
 * 
 * @tparam BenchmarkType - Data type of the benchmark being created
 * @param keys - Benchmark keys
 */
template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::InitializeLineContent(const std::unordered_set<std::string>& keys) 
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Initializing keys for line content...");
    for (const std::string& key : keys)
    {
        this->line_content_[std::move(key)] = "";
    }
    return (*this);
}

/**
 * @brief Sets the content for a specific benchmark key
 * 
 * @tparam BenchmarkType - Data type of the benchmark being created
 * @param key - Benchmark key
 * @param content - Benchmark key content
 */
template <typename BenchmarkType>
template <typename ContentType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::SetKeyContent(const std::string& key, const ContentType& content)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Setting content to key {}...", key);
    this->line_content_[std::move(key)] = fmt::format("{}",std::move(content));
    return (*this);
}

/**
 * @brief Write benchmark line
 * 
 * @tparam BenchmarkType - Data type of the benchmark being created
 */
template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::WriteLine()
{
    if (this->is_created_ == false)
    {
        this->WriteHeader();
        this->is_created_ = true;
    }
    this->WriteContent();
    return (*this);
}

/**
 * @brief Write benchmark header line
 * 
 * @tparam BenchmarkType - Data type of the benchmark being created
 */
template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::WriteHeader()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Writing header on benchmark...");
    std::string header_line {};
    for (auto& content_iter : this->line_content_)
    {
        header_line += ";" + content_iter.first;
    }
    this->WriteLineOnBenchmark(std::move(header_line));
    return (*this);
}

/**
 * @brief Write benchmark line content
 * 
 * @tparam BenchmarkType - Data type of the benchmark being created
 */
template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::WriteContent()
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Writing content on benchmark...");
    std::string line_msg {};
    for (auto& content_iter : this->line_content_)
    {
        line_msg += ";" + content_iter.second;
    }
    this->WriteLineOnBenchmark(std::move(line_msg));
    this->InitializeLineContent(this->keys_);
    return (*this);
}

/**
 * @brief Write benchmark line using logger
 * 
 * @tparam BenchmarkType - Data type of the benchmark being created
 * @param line - Benchmark line content
 */
template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::WriteLineOnBenchmark(const std::string& line)
{
    IMPROC_INFRASTRUCTURE_LOGGER_TRACE("Writing line on benchmark...");
    if (line.size() > 0)
    {
        // Remove first character since there is an additional ";" at the beginning
        this->data()->critical(std::move(line.substr(1,std::string::npos)));
    }
    else
    {
        this->data()->critical(std::move(line));
    }
    return (*this);
}

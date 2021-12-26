/**
 * @brief Construct a new improc::BenchmarkSingleton<BenchmarkType> object
 * 
 * @tparam BenchmarkType 
 * @param benchmark_logger 
 */
template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>::BenchmarkSingleton(std::shared_ptr<spdlog::logger>&& benchmark_logger) 
: LoggerSingleton<BenchmarkType>(std::move(benchmark_logger)) 
, is_created_(false)
, keys_(std::unordered_set<std::string>())
, line_content_(std::unordered_map<std::string,std::string>())
{
    SPDLOG_LOGGER_TRACE ( improc::InfrastructureLogger::get()->data()
                        , "Creating benchmark logger..." );
    this->data()->set_level(spdlog::level::critical);
    this->data()->set_pattern("%n;%v");
}

/**
 * @brief Construct a new improc::BenchmarkSingleton<BenchmarkType> object
 * 
 * @tparam BenchmarkType 
 * @param benchmark_logger 
 */
template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>::BenchmarkSingleton(const std::shared_ptr<spdlog::logger>& benchmark_logger) 
: LoggerSingleton<BenchmarkType>(std::move(benchmark_logger)) 
, is_created_(false)
, keys_(std::unordered_set<std::string>())
, line_content_(std::unordered_map<std::string,std::string>())
{
    SPDLOG_LOGGER_TRACE ( improc::InfrastructureLogger::get()->data()
                        , "Creating benchmark logger..." );
    this->data()->set_level(spdlog::level::critical);
    this->data()->set_pattern("%n;%v");
}

template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::AddKeys(const std::unordered_set<std::string>& keys) 
{
    SPDLOG_LOGGER_TRACE ( improc::InfrastructureLogger::get()->data()
                        , "Adding keys to benchmark..." );
    if (this->is_created_ == true)
    {
        SPDLOG_LOGGER_ERROR ( improc::InfrastructureLogger::get()->data()
                            , "Cannot change keys after benchmark has been created..." );
        throw improc::benchmark_keys_cannot_change();
    }
    this->keys_.insert(keys.begin(),keys.end());
    this->InitializeLineContent(std::move(keys));
    return (*this);
}

template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::InitializeLineContent(const std::unordered_set<std::string>& keys) 
{
    SPDLOG_LOGGER_TRACE ( improc::InfrastructureLogger::get()->data()
                        , "Initializing keys for line content..." );
    for (const std::string& key : keys)
    {
        this->line_content_[key] = "";
    }
    return (*this);
}

template <typename BenchmarkType>
template <typename ContentType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::SetKeyContent(const std::string& key, const ContentType& content)
{
    SPDLOG_LOGGER_TRACE ( improc::InfrastructureLogger::get()->data()
                        , "Setting content to key {}...", key );
    this->line_content_[key] = fmt::format("{}",std::move(content));
    return (*this);
}

/**
 * @brief Write benchmark line in the benchmark.
 * 
 * @tparam BenchmarkType 
 */
template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::WriteLine()
{
    SPDLOG_LOGGER_TRACE ( improc::InfrastructureLogger::get()->data()
                        , "Writing line on benchmark..." );
    if (this->is_created_ == false)
    {
        this->WriteHeader();
        this->is_created_ = true;
    }
    this->WriteContent();
    return (*this);
}

template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::WriteHeader()
{
    SPDLOG_LOGGER_TRACE ( improc::InfrastructureLogger::get()->data()
                        , "Writing header on benchmark..." );
    std::string header_line {};
    for (auto& content_iter : this->line_content_)
    {
        header_line += ";" + content_iter.first;
    }
    this->WriteLineOnBenchmark(header_line);
    return (*this);
}

template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::WriteContent()
{
    SPDLOG_LOGGER_TRACE ( improc::InfrastructureLogger::get()->data()
                        , "Writing content on benchmark..." );
    std::string line_msg {};
    for (auto& content_iter : this->line_content_)
    {
        line_msg += ";" + content_iter.second;
    }
    this->WriteLineOnBenchmark(line_msg);
    this->InitializeLineContent(this->keys_);
    return (*this);
}

template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::WriteLineOnBenchmark(const std::string& line)
{
    SPDLOG_LOGGER_TRACE ( improc::InfrastructureLogger::get()->data()
                        , "Writing line on benchmark..." );
    if (line.size() > 0)
    {
        // Remove first character since there is an additional ";" at the beginning
        this->data()->critical(line.substr(1,std::string::npos));
    }
    else
    {
        this->data()->critical(line);
    }
    return (*this);
}

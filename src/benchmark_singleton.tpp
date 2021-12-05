/**
 * @brief Construct a new improc::BenchmarkSingleton<BenchmarkType> object
 * 
 * @tparam BenchmarkType 
 * @param benchmark_logger 
 */
template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>::BenchmarkSingleton(std::shared_ptr<spdlog::logger>&& benchmark_logger) 
: LoggerSingleton<BenchmarkType>(std::move(benchmark_logger)) 
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
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
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Creating benchmark logger..." );
    this->data()->set_level(spdlog::level::critical);
    this->data()->set_pattern("%n;%v");
}

template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::AddFieldsToLine() 
{
    return (*this);
}

/**
 * @brief Add fields to benchmark line. The line is not written in the benchmark.
 * If you want to write on the benchmark use the method WriteFields or use the
 * method WriteLine after defining the line to write in the benchmark.
 * 
 * @tparam BenchmarkType 
 * @tparam Arg 
 * @tparam Args 
 * @param field_1 
 * @param field_n 
 */
template <typename BenchmarkType>
template<typename Arg, typename ... Args>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::AddFieldsToLine(Arg field_1, Args ... field_n)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Adding field to line..." );
    this->line_msg_ += fmt::format(";{}",std::move(field_1));
    this->AddFieldsToLine(field_n ...);
    return (*this);
}

template <typename BenchmarkType>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::WriteFields() 
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Writing fields on benchmark..." );
    this->WriteLine();
    return (*this);
}

/**
 * @brief Add fields to benchmark line. The line is written in the benchmark.
 * 
 * @tparam BenchmarkType 
 * @tparam Arg 
 * @tparam Args 
 * @param field_1 
 * @param field_n 
 */
template <typename BenchmarkType>
template<typename Arg, typename ... Args>
improc::BenchmarkSingleton<BenchmarkType>& improc::BenchmarkSingleton<BenchmarkType>::WriteFields(Arg field_1, Args ... field_n)
{
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Formatting fields to write on benchmark..." );
    this->line_msg_ += fmt::format(";{}",std::move(field_1));
    this->WriteFields(field_n ...);
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
    SPDLOG_LOGGER_CALL( improc::InfrastructureLogger::get()->data()
                      , spdlog::level::trace
                      , "Writing line on benchmark..." );
    if (this->line_msg_.size() > 0)
    {
        // Remove first character since there is an additional ";" at the beginning
        this->data()->critical(this->line_msg_.substr(1,std::string::npos));
    }
    else
    {
        this->data()->critical(this->line_msg_);
    }
    this->line_msg_.clear();
    return (*this);
}

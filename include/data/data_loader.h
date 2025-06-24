#ifndef DATA_LOADER_H
#define DATA_LOADER_H

#include "data/market_data.h"
#include "data/option_data.h"
#include <string>
#include <vector>
#include <optional> // C++17 feature for optional return values

namespace data_loader {

    // Loads market data from a specified CSV file.
    // Expected format: spot_price,risk_free_rate,dividend_yield
    // Returns std::nullopt if file cannot be opened or data is invalid.
    std::optional<MarketData> load_market_data_from_csv(const std::string& filepath);

    // Loads historical prices from a specified CSV file.
    // Expected format: price (one price per line, with a header)
    // Returns an empty vector if file cannot be opened or no prices found.
    std::vector<double> load_historical_prices_from_csv(const std::string& filepath);

    // Loads option data from a specified CSV file.
    // Expected format: strike_price,time_to_expiration,type,market_price
    // Returns an empty vector if file cannot be opened or no valid options found.
    std::vector<OptionData> load_option_data_from_csv(const std::string& filepath);

} // namespace data_loader

#endif // DATA_LOADER_H

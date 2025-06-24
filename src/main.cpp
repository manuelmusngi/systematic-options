#include <iostream> // For std::cout, std::endl
#include <vector>   // For std::vector
#include <span>     // For std::span (C++20)

#include "data/market_data.h"
#include "data/option_data.h"
#include "data/data_loader.h" // Include our new data loader
#include "strategy/implied_vol_strategy.h"

int main() {
    std::cout << "--- Implied Volatility Trading Strategy Simulation ---" << std::endl;

    // --- Load Market Data ---
    // Ensure market_data.csv is in a 'data' folder relative to your executable
    std::optional<MarketData> current_market_opt = data_loader::load_market_data_from_csv("../data/market_data.csv");
    if (!current_market_opt.has_value()) {
        std::cerr << "Failed to load market data. Exiting." << std::endl;
        return 1; // Indicate error
    }
    MarketData current_market = current_market_opt.value();

    std::cout << "Market Data: Spot=" << current_market.spot_price
              << ", RFR=" << current_market.risk_free_rate * 100 << "%"
              << ", DivYld=" << current_market.dividend_yield * 100 << "%" << std::endl;

    // --- Load Historical Prices (for RV forecasting) ---
    // Ensure historical_prices.csv is in a 'data' folder relative to your executable
    std::vector<double> historical_prices_vec = data_loader::load_historical_prices_from_csv("../data/historical_prices.csv");
    if (historical_prices_vec.empty()) {
        std::cerr << "Failed to load historical prices or file was empty. Exiting." << std::endl;
        return 1; // Indicate error
    }
    // Create a std::span from the vector for functions that accept spans
    std::span<const double> historical_prices_span = historical_prices_vec;

    std::cout << "Loaded " << historical_prices_vec.size() << " historical prices for RV calculation." << std::endl;

    // --- Load Option Contracts ---
    // Ensure options_data.csv is in a 'data' folder relative to your executable
    std::vector<OptionData> options_to_analyze = data_loader::load_option_data_from_csv("../data/options_data.csv");
    if (options_to_analyze.empty()) {
        std::cerr << "Failed to load option data or file was empty. Exiting." << std::endl;
        return 1; // Indicate error
    }

    std::cout << "\nAnalyzing " << options_to_analyze.size() << " option contracts:" << std::endl;

    // --- Instantiate and Run Strategy ---
    ImpliedVolStrategy strategy;

    for (const auto& opt : options_to_analyze) {
        std::cout << "\nAnalyzing Option: Strike=" << opt.strike_price
                  << ", TTM=" << opt.time_to_expiration
                  << "y, Type=" << opt.type
                  << ", Market Price=" << opt.market_price << std::endl;
        // Pass the span to the strategy's analyze method
        strategy.analyze(opt, current_market, historical_prices_span);
    }

    std::cout << "\n--- Simulation Complete ---" << std::endl;

    return 0;
}


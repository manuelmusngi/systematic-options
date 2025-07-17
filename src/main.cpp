#include <iostream> // For std::cout, std::endl
#include <vector>   // For std::vector
#include <span>     // For std::span (C++20)

#include "data/market_data.h"
#include "data/option_data.h"
#include "data/data_loader.h"
#include "strategy/implied_vol_strategy.h"
#include "utils/date_utils.h" // Include our new date utilities

int main() {
    std::cout << "--- Implied Volatility Trading Strategy Simulation ---" << std::endl;

    // --- Load Market Data ---
    std::optional<MarketData> current_market_opt = data_loader::load_market_data_from_csv("../data/market_data.csv");
    if (!current_market_opt.has_value()) {
        std::cerr << "Failed to load market data. Exiting." << std::endl;
        return 1;
    }
    MarketData current_market = current_market_opt.value();

    std::cout << "Market Data: Spot=" << current_market.spot_price
              << ", RFR=" << current_market.risk_free_rate * 100 << "%"
              << ", DivYld=" << current_market.dividend_yield * 100 << "%" << std::endl;

    // --- Load Historical Prices (for RV forecasting) ---
    std::vector<double> historical_prices_vec = data_loader::load_historical_prices_from_csv("../data/historical_prices.csv");
    if (historical_prices_vec.empty()) {
        std::cerr << "Failed to load historical prices or file was empty. Exiting." << std::endl;
        return 1;
    }
    std::span<const double> historical_prices_span = historical_prices_vec;

    std::cout << "Loaded " << historical_prices_vec.size() << " historical prices for RV calculation." << std::endl;

    // --- Demonstrate Date Utilities and Option TTM Calculation ---
    std::cout << "\n--- Date Utility Demonstration ---" << std::endl;
    date_utils::Date current_date(2025, 7, 16); // Example: Today's date
    date_utils::Date expiration_date_option1(2025, 10, 17); // Example: October 3rd Friday (approx)
    date_utils::Date expiration_date_option2(2026, 1, 16); // Example: January 3rd Friday (approx)

    long long days_to_exp1 = date_utils::days_between(current_date, expiration_date_option1);
    double ttm1 = date_utils::days_to_years(days_to_exp1);
    std::cout << "Current Date: " << current_date.to_string() << std::endl;
    std::cout << "Option 1 Expiration: " << expiration_date_option1.to_string()
              << " -> Days to Expiration: " << days_to_exp1
              << ", TTM (Years): " << std::fixed << std::setprecision(4) << ttm1 << std::endl;

    long long days_to_exp2 = date_utils::days_between(current_date, expiration_date_option2);
    double ttm2 = date_utils::days_to_years(days_to_exp2);
    std::cout << "Option 2 Expiration: " << expiration_date_option2.to_string()
              << " -> Days to Expiration: " << days_to_exp2
              << ", TTM (Years): " << std::fixed << std::setprecision(4) << ttm2 << std::endl;
    std::cout << "------------------------------------" << std::endl;


    // --- Load Option Contracts ---
    // For a real system, you'd calculate TTM here and update the OptionData.
    // For this example, we'll keep the TTM from the CSV for simplicity,
    // but the date_utils can be used to derive it.
    std::vector<OptionData> options_to_analyze = data_loader::load_option_data_from_csv("../data/options_data.csv");
    if (options_to_analyze.empty()) {
        std::cerr << "Failed to load option data or file was empty. Exiting." << std::endl;
        return 1;
    }

    std::cout << "\nAnalyzing " << options_to_analyze.size() << " option contracts:" << std::endl;

    // --- Instantiate and Run Strategy ---
    ImpliedVolStrategy strategy;

    for (const auto& opt : options_to_analyze) {
        std::cout << "\nAnalyzing Option: Strike=" << opt.strike_price
                  << ", TTM=" << opt.time_to_expiration
                  << "y, Type=" << opt.type
                  << ", Market Price=" << opt.market_price << std::endl;
        strategy.analyze(opt, current_market, historical_prices_span);
    }

    std::cout << "\n--- Simulation Complete ---" << std::endl;

    return 0;
}

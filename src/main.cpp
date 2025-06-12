#include <iostream> // For std::cout, std::endl
#include <vector>   // For std::vector

#include "data/market_data.h"
#include "data/option_data.h"
#include "strategy/implied_vol_strategy.h"

int main() {
    std::cout << "--- Implied Volatility Trading Strategy Simulation ---" << std::endl;

    // --- Sample Market Data ---
    MarketData current_market = {
        .spot_price = 100.0,        // Underlying asset price
        .risk_free_rate = 0.01,     // 1% annual risk-free rate
        .dividend_yield = 0.00      // 0% annual dividend yield
    };
    std::cout << "Market Data: Spot=" << current_market.spot_price
              << ", RFR=" << current_market.risk_free_rate * 100 << "%"
              << ", DivYld=" << current_market.dividend_yield * 100 << "%" << std::endl;

    // --- Sample Historical Prices (for RV forecasting) ---
    // In a real system, this would come from a data feed/database.
    // These prices are designed to have some volatility.
    std::vector<double> historical_prices = {
        98.0, 99.5, 97.0, 100.0, 101.5, 103.0, 100.5, 99.0, 97.5, 96.0,
        98.5, 101.0, 102.5, 100.0, 99.0, 97.0, 98.0, 99.0, 100.0, 101.0,
        102.0, 103.0, 104.0, 105.0, 103.5, 102.0, 100.5, 99.0, 97.5, 96.0,
        97.0, 98.0, 99.0, 100.0, 101.0, 102.0, 103.0, 104.0, 105.0, 106.0,
        105.0, 104.0, 103.0, 102.0, 101.0, 100.0, 99.0, 98.0, 97.0, 96.0
    };
    std::cout << "Loaded " << historical_prices.size() << " historical prices for RV calculation." << std::endl;

    // --- Sample Option Contracts ---
    std::vector<OptionData> options_to_analyze = {
        // Option 1: Slightly overvalued IV (market price higher than BS price for RV)
        { .strike_price = 100.0, .time_to_expiration = 0.25, .type = 'C', .market_price = 3.50 },
        // Option 2: Slightly undervalued IV (market price lower than BS price for RV)
        { .strike_price = 100.0, .time_to_expiration = 0.25, .type = 'P', .market_price = 2.00 },
        // Option 3: IV close to RV
        { .strike_price = 105.0, .time_to_expiration = 0.50, .type = 'C', .market_price = 2.80 }
    };
    std::cout << "\nAnalyzing " << options_to_analyze.size() << " option contracts:" << std::endl;

    // --- Instantiate and Run Strategy ---
    ImpliedVolStrategy strategy;

    for (const auto& opt : options_to_analyze) {
        std::cout << "\nAnalyzing Option: Strike=" << opt.strike_price
                  << ", TTM=" << opt.time_to_expiration
                  << "y, Type=" << opt.type
                  << ", Market Price=" << opt.market_price << std::endl;
        strategy.analyze(opt, current_market, historical_prices);
    }

    std::cout << "\n--- Simulation Complete ---" << std::endl;

    return 0;
}

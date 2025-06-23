#include <iostream> // For std::cout, std::endl
#include <vector>   // For std::vector

#include "data/market_data.h"
#include "data/option_data.h"
#include "strategy/strategy.h"           // <-- 1. Include the new Strategy interface
#include "strategy/implied_vol_strategy.h"

int main() {
    std::cout << "--- Implied Volatility Trading Strategy Simulation ---" << std::endl;

    // --- Sample Market Data ---
    MarketData current_market = {
        .spot_price = 100.0,
        .risk_free_rate = 0.01,
        .dividend_yield = 0.00
    };
    std::cout << "Market Data: Spot=" << current_market.spot_price
              << ", RFR=" << current_market.risk_free_rate * 100 << "%"
              << ", DivYld=" << current_market.dividend_yield * 100 << "%" << std::endl;

    // --- Sample Historical Prices (for RV forecasting) ---
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
        { .strike_price = 100.0, .time_to_expiration = 0.25, .type = 'C', .market_price = 3.50 },
        { .strike_price = 100.0, .time_to_expiration = 0.25, .type = 'P', .market_price = 2.00 },
        { .strike_price = 105.0, .time_to_expiration = 0.50, .type = 'C', .market_price = 2.80 }
    };
    std::cout << "\nAnalyzing " << options_to_analyze.size() << " option contracts:" << std::endl;

    // --- Strategy Pattern: Use base pointer for strategies ---
    Strategy* strategy = new ImpliedVolStrategy(); // Could swap with other strategies later

    for (const auto& opt : options_to_analyze) {
        std::cout << "\nAnalyzing Option: Strike=" << opt.strike_price
                  << ", TTM=" << opt.time_to_expiration
                  << "y, Type=" << opt.type
                  << ", Market Price=" << opt.market_price << std::endl;
        strategy->analyze(opt, current_market, historical_prices);
    }

    delete strategy; // Clean up

    std::cout << "\n--- Simulation Complete ---" << std::endl;

    return 0;
}

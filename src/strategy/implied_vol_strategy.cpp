#include "strategy/implied_vol_strategy.h"
#include "models/black_scholes.h"
#include "models/volatility_forecast.h"

#include <iostream> // For std::cout, std::endl
#include <iomanip>  // For std::fixed, std::setprecision

void ImpliedVolStrategy::analyze(const OptionData& option, const MarketData& market,
                                 const std::vector<double>& historical_prices) {

    // 1. Calculate Implied Volatility (IV)
    double implied_vol = implied_volatility_bisection(option, market);
    std::cout << "  Calculated Implied Volatility (IV): " << std::fixed << std::setprecision(4) << implied_vol * 100 << "%" << std::endl;

    // 2. Forecast Realized Volatility (RV) using historical data
    double forecasted_realized_vol = calculate_historical_volatility(historical_prices);
    std::cout << "  Forecasted Realized Volatility (RV): " << std::fixed << std::setprecision(4) << forecasted_realized_vol * 100 << "%" << std::endl;

    // 3. Identify Discrepancies and Generate Signal
    double discrepancy = implied_vol - forecasted_realized_vol;
    std::cout << "  IV - RV Discrepancy: " << std::fixed << std::setprecision(4) << discrepancy * 100 << "%" << std::endl;

    // Define thresholds for trading signals (these would be optimized in practice)
    // A negative discrepancy means IV < RV (undervalued IV, potential long vol)
    // A positive discrepancy means IV > RV (overvalued IV, potential short vol)
    const double LONG_VOL_THRESHOLD = -0.05; // If IV is 5% points below RV
    const double SHORT_VOL_THRESHOLD = 0.05; // If IV is 5% points above RV

    if (discrepancy < LONG_VOL_THRESHOLD) {
        std::cout << "  SIGNAL: BUY VOLATILITY (e.g., Long Straddle/Strangle) - IV is significantly undervalued." << std::endl;
    } else if (discrepancy > SHORT_VOL_THRESHOLD) {
        std::cout << "  SIGNAL: SELL VOLATILITY (e.g., Short Straddle/Strangle) - IV is significantly overvalued." << std::endl;
    } else {
        std::cout << "  SIGNAL: NEUTRAL - IV is generally in line with forecasted RV." << std::endl;
    }
    std::cout << "----------------------------------------------------" << std::endl;
}

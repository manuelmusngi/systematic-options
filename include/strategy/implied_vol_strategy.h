#pragma once
#ifndef IMPLIED_VOL_STRATEGY_H
#define IMPLIED_VOL_STRATEGY_H

#include "data/market_data.h"
#include "data/option_data.h"
#include "strategy.h"
#include <vector> // For std::vector

class ImpliedVolStrategy {
public:
    // Analyzes a given option and market data to generate a trading signal.
    // option: the option contract to analyze
    // market: current market data for the underlying
    // historical_prices: vector of historical prices for volatility forecasting
    void analyze(const OptionData& option, 
                 const MarketData& market,
                 const std::vector<double>& historical_prices)override;
};

#endif // IMPLIED_VOL_STRATEGY_H

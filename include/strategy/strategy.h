#pragma once

#include "data/option_data.h"
#include "data/market_data.h"
#include <vector>

class Strategy {
public:
    virtual ~Strategy() {}
    virtual void analyze(const OptionData& option,
                         const MarketData& market,
                         const std::vector<double>& historical_prices) = 0;
};

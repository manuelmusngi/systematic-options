#### systematic-options-volatility-trading

This is a project development to design, build, backtest, and deploy a systematic options volatility trading strategy in a modular C++ framework. 

The project is a simple strategy pattern architecture designed for scalability and clarity which separates:

- Data handling
- Derivatives modeling
- Strategy logic
- Trade execution

#### Project architecture:

VolatilityTrading/\
├── [CMakeLists.txt](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/CMakeLists.txt)\
├── include/\
│   ├── data/\
│   │   ├── [market_data.h](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/include/data/market_data.h)\
│   │   └── [option_data.h](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/include/data/option_data.h)\
│   ├── models/\
│   │   ├── [black_scholes.h](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/include/models/black_scholes.h)\
│   │   ├── [volatility_forecast.h](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/include/models/volatility_forecast.h)\
│   │   └── [risk_management.h](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/include/models/risk_management.h)\
│   ├── strategy/\
│   │   ├── [strategy.h](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/include/strategy/strategy.h)\
│   │   └── [implied_vol_strategy.h](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/include/strategy/implied_vol_strategy.h)\
│   ├── utils/\
│   │   ├── [date_utils.h](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/include/utils/date_utils.h)\
│   │   └── [math_utils.h](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/include/utils/math_utils.h)\
├── src/\
│   ├── data/\
│   │   └── [data_loader.cpp](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/src/data/data_loader.cpp)\
│   ├── models/\
│   │   ├── [black_scholes.cpp](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/src/models/black_scholes.cpp)\
│   │   ├── [volatility_forecast.cpp](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/src/models/volatility_forecast.cpp)\
│   │   └── [risk_management.cpp](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/src/models/risk_management.cpp)\
│   ├── strategy/\
│   │   └── [implied_vol_strategy.cpp](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/src/strategy/implied_vol_strategy.cpp)\
│   ├── utils/\
│   │   ├── [date_utils.cpp](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/src/utils/date_utils.cpp)\
│   │   └── [math_utils.cpp](https://github.com/manuelmusngi/systematic-options-volatility-trading/blob/main/src/utils/math_utils.cpp)\
├── data/          // For storing historical data\
├── logs/          // For logging trading activity\
├── tests/         // Unit tests\
│   ├── models/\
│   │   └── black_scholes_test.cpp\
└── README.md
 

#### License
This project is licensed under the [MIT License](https://github.com/manuelmusngi/regime_switching_models/edit/main/LICENSE).

#### systematic-options-volatility-trading

This is a project development to design, build, backtest, and deploy a systematic options volatility trading strategy in a modular C++ framework. 

The planned Options volatility strategy that will be incorporated in the development:

- Volatility Arbitrage

The project is a simple architecture designed for scalability and clarity which separates:

- Data handling
- Derivatives modeling
- Strategy logic
- Trade execution

#### Project architecture:

VolatilityTrading/\
├── include/\
│   ├── data/\
│   │   ├── market_data.h\ 
│   │   └── option_data.h\
│   ├── models/\
│   │   ├── black_scholes.h\
│   │   ├── volatility_forecast.h\
│   │   └── risk_management.h\
│   ├── strategy/\
│   │   └── implied_vol_strategy.h\
│   ├── utils/\
│   │   ├── date_utils.h\
│   │   └── math_utils.h\
├── src/\
│   ├── data/\
│   │   ├── market_data.cpp\
│   │   └── option_data.cpp\
│   ├── models/\
│   │   ├── black_scholes.cpp\
│   │   ├── volatility_forecast.cpp\
│   │   └── risk_management.cpp\
│   ├── strategy/\
│   │   └── implied_vol_strategy.cpp\
│   ├── utils/\
│   │   ├── date_utils.cpp\
│   │   └── math_utils.cpp\
├── data/          // For storing historical data\
├── logs/          // For logging trading activity\
├── tests/         // Unit tests\
│   ├── models/\
│   │   └── black_scholes_test.cpp\
├── CMakeLists.txt\
└── README.md\
 

#### License
This project is licensed under the [MIT License](https://github.com/manuelmusngi/regime_switching_models/edit/main/LICENSE).

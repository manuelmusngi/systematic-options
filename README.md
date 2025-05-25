#### systematic-options-trading: a C++ framework

This project is a practice in development to build, backtest, and deploy a systematic options trading strategy in a modular C++ framework.  
This is designed for scalability and clarity and separates:

- Data handling
- Derivatives modeling
- Strategy logic
- Trade execution 

#### Highlights:

* **Organized Architecture:**
  - Easily navigate and extend the codebase with clear module separation (data, models, strategy, utils).
* **Extensible Design:**
  - Implement custom data feeds, pricing models, risk management techniques, and trading signals seamlessly.
* **Test-Driven Development:**
  - Includes a dedicated testing structure to ensure the reliability of the strategy.
* **Cross-Platform Ready:**
  - Leverages CMake for straightforward building on different operating systems.

#### Project architecture:

options_strategy_system/
├── CMakeLists.txt              # Top-level CMake build file\
├── README.md\                      
├── config/                     # Configuration files  
│   ├── app_config.json\
│   └── strategy_params.json\
├── data/\                        
│   ├── market_data/\
│   └── reference_data/\
├── docs/\                       
├── src/\                        # Source code
│   ├── main.cpp                 # Main application entry point
│   ├── Primary/                 # Primary infrastructure components
│   │   ├── Logger.h
│   │   ├── Logger.cpp
│   │   ├── ConfigManager.h
│   │   ├── ConfigManager.cpp
│   │   ├── EventBus.h
│   │   ├── ThreadPool.h
│   │   └── CMakeLists.txt
│   ├── Data/\                   # Data Management Module
│   │   ├── MarketDataFeed.h
│   │   ├── MarketDataFeed.cpp
│   │   ├── DataStorage.h
│   │   ├── DataStorage.cpp
│   │   ├── DataProcessor.h
│   │   ├── DataProcessor.cpp
│   │   ├── ReferenceData.h
│   │   ├── ReferenceData.cpp
│   │   └── CMakeLists.txt
│   ├── Strategy/\              # Strategy Module
│   │   ├── StrategyBase.h
│   │   ├── VolatilityStrategy.h
│   │   ├── VolatilityStrategy.cpp
│   │   ├── SignalGenerator.h
│   │   ├── PositionSizer.h
│   │   └── CMakeLists.txt
│   ├── Execution/\             # Execution Module
│   │   ├── OrderManager.h
│   │   ├── OrderManager.cpp
│   │   ├── BrokerInterface.h
│   │   ├── BrokerInterface.cpp
│   │   ├── FillMonitor.h
│   │   └── CMakeLists.txt
│   ├── RiskManagement/\        # Portfolio & Risk Management Module
│   │   ├── PortfolioManager.h
│   │   ├── PortfolioManager.cpp
│   │   ├── RiskMonitor.h
│   │   ├── RiskMonitor.cpp
│   │   └── CMakeLists.txt
│   ├── Backtesting/\           # Backtesting & Analysis Module
│   │   ├── BacktestEngine.h
│   │   ├── BacktestEngine.cpp
│   │   ├── PerformanceMetrics.h
│   │   ├── ReportGenerator.h
│   │   └── CMakeLists.txt
│   └── Utils/\                 # General utility functions/classes
│       ├── MathUtils.h
│       ├── TimeUtils.h
│       └── CMakeLists.txt
├── tests/\                     # Unit and integration tests
│   ├── CoreTests.cpp
│   ├── DataTests.cpp
│   ├── StrategyTests.cpp
│   └── CMakeLists.txt
└── lib/\                       # Third-party libraries  


#### License
This project is licensed under the [MIT License](https://github.com/manuelmusngi/regime_switching_models/edit/main/LICENSE).

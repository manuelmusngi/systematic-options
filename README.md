#### systematic-options-trading: C++ framework

This is a project development to design, build, backtest, and deploy a systematic options trading strategy in a modular C++ framework.  

The project architecture is designed for scalability and clarity which separates:

- Data handling
- Derivatives modeling
- Strategy logic
- Trade execution
  
#### Project architecture:

 OptionsStrategy/\
├── include/\
│   ├── data/\
│   │   ├── market_data.h\
│   │   ├── option_data.h\
│   │   └── data_provider.h\
│   ├── models/\
│   │   ├── option_pricing_model.h\
│   │   ├── volatility_model.h\
│   │   └── risk_model.h\
│   ├── strategy/\
│   │   ├── signal_generator.h\
│   │   ├── portfolio_manager.h\
│   │   └── execution_engine.h\
│   ├── utils/\
│   │   ├── logging.h\
│   │   ├── configuration.h\
│   │   └── math_utils.h\
│   └── common.h\
├── src/\
│   ├── data/\
│   │   ├── market_data.cpp\
│   │   ├── option_data.cpp\
│   │   └── data_provider.cpp\
│   ├── models/\
│   │   ├── option_pricing_model.cpp\
│   │   ├── volatility_model.cpp\
│   │   └── risk_model.cpp\
│   ├── strategy/\
│   │   ├── signal_generator.cpp\
│   │   ├── portfolio_manager.cpp\
│   │   └── execution_engine.cpp\
│   ├── utils/\
│   │   ├── logging.cpp\
│   │   ├── configuration.cpp\
│   │   └── math_utils.cpp\
│   └── main.cpp\
├── tests/\
│   ├── data/\
│   ├── models/\
│   ├── strategy/\
│   └── utils/\
├── CMakeLists.txt


#### License
This project is licensed under the [MIT License](https://github.com/manuelmusngi/regime_switching_models/edit/main/LICENSE).

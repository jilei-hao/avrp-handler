#ifndef HANDLER_PARAMETERS_HXX
#define HANDLER_PARAMETERS_HXX

#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

class HandlerParameters {
public:
  HandlerParameters() {}
  ~HandlerParameters() {}
  HandlerParameters(const HandlerParameters&) = default;
  HandlerParameters& operator=(const HandlerParameters&) = delete;

  std::string m_GatewayURL;
  std::string m_GatewayUsername;
  std::string m_GatewayPassword;
  std::string m_DataServerURL;
};

class HandlerParametersBuilder {
public:
  HandlerParametersBuilder() {}
  ~HandlerParametersBuilder() {}
  HandlerParametersBuilder(const HandlerParametersBuilder&) = delete;
  HandlerParametersBuilder& operator=(const HandlerParametersBuilder&) = delete;

  static HandlerParameters BuildFromArgs(int argc, char* argv[]) {
    HandlerParameters params;
    for (int i = 1; i < argc; i++) {
      if (std::string(argv[i]) == "-url") {
        if (i + 1 < argc) {
          params.m_GatewayURL = argv[i + 1];
        }
      } else if (std::string(argv[i]) == "-un") {
        if (i + 1 < argc) {
          params.m_GatewayUsername = argv[i + 1];
        }
      } else if (std::string(argv[i]) == "-pw") {
        if (i + 1 < argc) {
          params.m_GatewayPassword = argv[i + 1];
        }
      }
    }
    return params;
  }

  static HandlerParameters BuildFromConfigFile(int argc, char* argv[]) {
    HandlerParameters params;
    for (int i = 1; i < argc; i++) 
    {
      if (std::string(argv[i]) == "-config") 
      {
        if (i + 1 < argc) 
        {
          std::string configFile = argv[i + 1];

          std::cout << "Reading config file: " << configFile << "\n";

          // read the config json file
          std::ifstream file(configFile);
          if (file.is_open()) {
            nlohmann::json jsonConfig;
            file >> jsonConfig;

            // Set the parameters
            params.m_GatewayURL = jsonConfig["gateway_url"];
            params.m_GatewayUsername = jsonConfig["gateway_username"];
            params.m_GatewayPassword = jsonConfig["gateway_password"];
            params.m_DataServerURL = jsonConfig["dataserver_url"];

          } else {
            // Throw an exception or provide default values
            throw std::runtime_error("Could not open config file");
          }
        }
      }
    }
    return params;
  }
};



#endif // HANDLER_PARAMETERS_HXX
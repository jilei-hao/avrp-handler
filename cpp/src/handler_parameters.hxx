#ifndef HANDLER_PARAMETERS_HXX
#define HANDLER_PARAMETERS_HXX

#include <string>
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>


class HandlerParameters 
{
public:
  static HandlerParameters& getInstance() {
    static HandlerParameters instance;
    return instance;
  }

  // Delete copy constructor and assignment operator
  HandlerParameters(const HandlerParameters&) = default;
  HandlerParameters& operator=(const HandlerParameters&) = default;

  // Getter methods
  std::string getGatewayURL() const {
    return m_GatewayURL;
  }

  std::string getGatewayUsername() const {
    return m_GatewayUsername;
  }

  std::string getGatewayPassword() const {
    return m_GatewayPassword;
  }

  std::string getDataServerURL() const {
    return m_DataServerURL;
  }

  std::string getWorkDir() const {
    return m_WorkDir;
  }

  std::string getDownloadDir() const {
    return m_WorkDir + "/" + m_DownloadFolderName;
  }

  std::string getUploadDir() const {
    return m_WorkDir + "/" + m_UploadFolderName;
  }

  friend class HandlerParametersBuilder;
private:
  std::string m_GatewayURL;
  std::string m_GatewayUsername;
  std::string m_GatewayPassword;
  std::string m_DataServerURL;
  std::string m_WorkDir;

  const static std::string m_DownloadFolderName;
  const static std::string m_UploadFolderName;

  // Private constructor to prevent instantiation
  HandlerParameters() {}
};

const std::string HandlerParameters::m_DownloadFolderName = "download";
const std::string HandlerParameters::m_UploadFolderName = "upload";


class HandlerParametersBuilder {
public:
  HandlerParametersBuilder() {}
  ~HandlerParametersBuilder() {}
  HandlerParametersBuilder(const HandlerParametersBuilder&) = delete;
  HandlerParametersBuilder& operator=(const HandlerParametersBuilder&) = delete;

  static void BuildFromArgs(int argc, char* argv[]) {
    HandlerParameters params = HandlerParameters::getInstance();
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
  }

  static void BuildFromConfigFile(int argc, char* argv[]) {
    HandlerParameters *params = &HandlerParameters::getInstance();
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
            params->m_GatewayURL = jsonConfig["gateway_url"];
            params->m_GatewayUsername = jsonConfig["gateway_username"];
            params->m_GatewayPassword = jsonConfig["gateway_password"];
            params->m_DataServerURL = jsonConfig["dataserver_url"];
            params->m_WorkDir = jsonConfig["work_dir"];

          } else {
            // Throw an exception or provide default values
            throw std::runtime_error("Could not open config file");
          }
        }
      }
    }
  }
};



#endif // HANDLER_PARAMETERS_HXX
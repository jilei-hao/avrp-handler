#ifndef GATEWAY_HELPER_HXX
#define GATEWAY_HELPER_HXX

#include <string>
#include <vector>
#include <iostream>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>
#include "handler_task.hxx"



class GatewayConfig {
public:
  GatewayConfig(std::string url, std::string username, std::string password)
    : m_Url(url), m_Username(username), m_Password(password) {}
  ~GatewayConfig() {}
  GatewayConfig(const GatewayConfig&) = default;
  GatewayConfig& operator=(const GatewayConfig&) = default;

  std::string m_Url;
  std::string m_Username;
  std::string m_Password;
};

class GatewayHelper {
public:
  GatewayHelper(GatewayConfig config) : m_Config(config) 
  {
    login();
  }

  ~GatewayHelper() {}
  GatewayHelper(const GatewayHelper&) = default;
  GatewayHelper& operator=(const GatewayHelper&) = default;

  std::vector<HandlerTask> GetTasks()
  {
    std::cout << "[GatewayHelper] Getting tasks..." << std::endl;

    cpr::Response r = cpr::Get(cpr::Url{m_Config.m_Url + "/handler-tasks"}, 
      cpr::Header{{"Authorization", "Bearer " + m_Token}});

    // parse the json response
    nlohmann::json j = nlohmann::json::parse(r.text);

    // print out the json
    std::cout << j.dump(4) << std::endl;

    std::vector<HandlerTask> tasks;

    nlohmann::json taskArr = j["handler_tasks"];

    // parse tasks from the array
    for (size_t i = 0; i < taskArr.size(); i++) {
      std::cout << "---- parsing task " << i << " ----\n";
      auto t = taskArr[i];

      std::cout << "---- json dump: " << std::endl;
      std::cout << t.dump(4) << std::endl;

      int study_id = t["study_id"].get<int>();
      int64_t module_status = t["module_status"].get<int64_t>();

      std::cout << "---- study_id: " << study_id << std::endl;
      std::cout << "---- module_status: " << module_status << std::endl;

      StudyConfig studyConfig(t["study_config"]);

      tasks.push_back(HandlerTask(study_id, module_status, studyConfig));
    }
    
    return tasks;
  }

private:
  void login()
  {
    std::cout << "[GatewayHelper] Logging in, un: " << m_Config.m_Username
              << " pw: " << m_Config.m_Password << std::endl;

    cpr::Response r = cpr::Post(cpr::Url{m_Config.m_Url + "/login"}, 
      cpr::Authentication{m_Config.m_Username, m_Config.m_Password, cpr::AuthMode::BASIC});

    // parse the json response
    nlohmann::json j = nlohmann::json::parse(r.text);

    // get the token
    m_Token = j["token"];

    std::cout << "[GatewayHelper] Logged in with token: " << m_Token << std::endl;
  }

  GatewayConfig m_Config;
  std::string m_Token;
};

#endif // GATEWAY_HELPER_HXX
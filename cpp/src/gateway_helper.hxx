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
    // std::cout << "[GatewayHelper] Getting tasks..." << std::endl;

    cpr::Response r = cpr::Get(cpr::Url{m_Config.m_Url + "/handler-tasks"}, 
      cpr::Header{{"Authorization", "Bearer " + m_Token}});

    // parse the json response
    nlohmann::json j = nlohmann::json::parse(r.text);

    std::vector<HandlerTask> tasks;

    nlohmann::json taskArr = j["handler_tasks"];

    // parse tasks from the array
    for (size_t i = 0; i < taskArr.size(); i++) {
      auto t = taskArr[i];

      int study_id = t["study_id"].get<int>();
      int64_t module_status = t["module_status"].get<int64_t>();
      StudyConfig studyConfig(t["study_config"]);

      tasks.push_back(HandlerTask(study_id, module_status, studyConfig));
    }
    
    return tasks;
  }

  void UpdateTaskStatus(int study_id, std::string study_status, int64_t module_status)
  {
    std::cout << "[GatewayHelper] Updating task status for study " << study_id << std::endl;

    nlohmann::json j;
    j["study_id"] = study_id;
    j["study_status"] = study_status;
    j["module_status"] = module_status;

    cpr::Response r = cpr::Put(cpr::Url{m_Config.m_Url + "/handler-tasks"}, 
      cpr::Header{{"Authorization", "Bearer " + m_Token}},
      cpr::Body{j.dump()},
      cpr::Header{{"Content-Type", "application/json"}});

    std::cout << "[GatewayHelper] Updated task status for study " << study_id << " with status: " << study_status << std::endl;
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
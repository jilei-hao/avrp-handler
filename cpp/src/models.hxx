#ifndef MODELS_HXX
#define MODELS_HXX

#include <nlohmann/json.hpp>
#include <string>

class StudyConfig
{
public:
  StudyConfig(nlohmann::json j) 
  {
    m_MainImageDSID = j["main_image_dsid"].get<int64_t>();
    m_TPStart = j["tp_start"].get<int>();
    m_TPEnd = j["tp_end"].get<int>();
    m_SysSegrefDSID = j["sys_segref_dsid"].get<int64_t>();
    m_SysTPRef = j["sys_tp_ref"].get<int>();
    m_SysTPStart = j["sys_tp_start"].get<int>();
    m_SysTPEnd = j["sys_tp_end"].get<int>();
    m_DiasSegrefDSID = j["dias_segref_dsid"].get<int64_t>();
    m_DiasTPRef = j["dias_tp_ref"].get<int>();
    m_DiasTPStart = j["dias_tp_start"].get<int>();
    m_DiasTPEnd = j["dias_tp_end"].get<int>();
  }

  StudyConfig() {}

  ~StudyConfig() {}
  StudyConfig(const StudyConfig&) = default;
  StudyConfig& operator=(const StudyConfig&) = default;

  int64_t m_MainImageDSID;
  int m_TPStart;
  int m_TPEnd;
  int64_t m_SysSegrefDSID;
  int m_SysTPRef;
  int m_SysTPStart;
  int m_SysTPEnd;
  int64_t m_DiasSegrefDSID;
  int m_DiasTPRef;
  int m_DiasTPStart;
  int m_DiasTPEnd;
};

class HandlerTask
{
public:
  HandlerTask(int study_id, int64_t module_status, StudyConfig config) 
    : m_StudyID(study_id), m_ModuleStatus(module_status), m_Config(config) {}
  ~HandlerTask() {}
  HandlerTask(const HandlerTask&) = default;
  HandlerTask& operator=(const HandlerTask&) = delete;

  int m_StudyID;
  int64_t m_ModuleStatus;
  StudyConfig m_Config;
};


#endif
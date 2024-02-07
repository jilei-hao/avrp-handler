#ifndef HANDELR_TASK_HXX
#define HANDELR_TASK_HXX

#include "study_config.hxx"

class HandlerTask
{
public:
  HandlerTask(int study_id, int64_t module_status, StudyConfig config) 
    : m_StudyID(study_id), m_ModuleStatus(module_status), m_Config(config) {}
  HandlerTask() {}
  ~HandlerTask() {}
  HandlerTask(const HandlerTask&) = default;
  HandlerTask& operator=(const HandlerTask&) = default;

  int m_StudyID;
  int64_t m_ModuleStatus;
  StudyConfig m_Config;
};

#endif
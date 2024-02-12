#ifndef TASK_PROCESSOR_HXX
#define TASK_PROCESSOR_HXX

#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include "study_config.hxx"
#include "handler_task.hxx"
#include "gateway_helper.hxx"
#include "data_server_helper.hxx"

class TaskProcessor
{
public:
  TaskProcessor(GatewayHelper *gw, DataServerHelper *ds) 
    : m_GatewayHelper(gw), m_DataServerHelper(ds)
  {
    DownloadModuleConfigs();
  }
  ~TaskProcessor() {}
  TaskProcessor(const TaskProcessor&) = delete;
  TaskProcessor& operator=(const TaskProcessor&) = delete;

  // todo: run once at initialization of the processor
  // download module configs from the gateway
  // defines available modules, ids, and prerequisites
  void DownloadModuleConfigs()
  {
    std::cout << "[TaskProcessor] Downloading module configs..." << std::endl;
  }

  void FetchTasks()
  {
    std::cout << "[TaskProcessor] Fetching tasks..." << std::endl;
    std::lock_guard<std::mutex> lock(m_Mutex);
    std::vector<HandlerTask> tasks = m_GatewayHelper->GetTasks();
    
    for (auto &task : tasks)
    {
      if (!IsTaskInList(task.m_StudyID))
      {
        m_TaskList.push_back(task);
      }
    }
  }

  void Process()
  {
    std::cout << "[TaskProcessor] Processing tasks..." << std::endl;

    if (m_TaskList.empty())
      return;

    while (m_NumberOfRunningJobs < m_MaxNumberOfJobs && !m_TaskList.empty())
    {
      // pop a task from the list
      HandlerTask task = PopTask();
      if (task.m_StudyID != 0)
      {
        std::cout << "Processing task for study " << task.m_StudyID << std::endl;

        // create and run a module in a new thread
        std::thread([this, task]() 
          {
            m_NumberOfRunningJobs++;

            AbstractModule *module = GetModuleFromTask(task);
            module->SetGatewayHelper(m_GatewayHelper);
            module->SetDataServerHelper(m_DataServerHelper);
            module->Run();
          
            delete module;
            m_NumberOfRunningJobs--;
          }
        ).detach();
      }
    }
  }


private:

  HandlerTask PopTask()
  {
    HandlerTask ret;

    std::lock_guard<std::mutex> lock(m_Mutex);

    if (!m_TaskList.empty())
    {
      ret = m_TaskList.front();
      m_TaskList.pop_front();
    }

    return ret;
  }

  bool IsTaskInList(int studyId) const
  {
    for (const auto& task : m_TaskList)
    {
      if (task.m_StudyID == studyId)
      {
        return true;
      }
    }
    return false;
  }

  AbstractModule *GetModuleFromTask(const HandlerTask &task)
  {
    std::cout << "[TaskProcessor] Getting the right module to run from a task..." << std::endl;
    AbstractModule *ret = new StudyGenModule();
    ret->SetTask(task);
    return ret;
  }

  std::mutex m_Mutex;
  std::list<HandlerTask> m_TaskList;
  GatewayHelper *m_GatewayHelper;
  DataServerHelper *m_DataServerHelper;

  uint32_t m_NumberOfRunningJobs = 0u;
  uint32_t m_MaxNumberOfJobs = 10u;
};

// Access the singleton instance using TaskProcessor::GetInstance()
#endif

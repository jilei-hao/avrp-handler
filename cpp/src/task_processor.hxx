#ifndef TASK_PROCESSOR_HXX
#define TASK_PROCESSOR_HXX

#include <iostream>
#include <list>
#include <mutex>
#include "models.hxx"
#include "gateway_helper.hxx"

class TaskProcessor
{
public:
  TaskProcessor(GatewayHelper *gw) : m_GatewayHelper(gw) {}
  ~TaskProcessor() {}
  TaskProcessor(const TaskProcessor&) = delete;
  TaskProcessor& operator=(const TaskProcessor&) = delete;

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

  std::mutex m_Mutex;
  std::list<HandlerTask> m_TaskList;
  GatewayHelper *m_GatewayHelper;
};

// Access the singleton instance using TaskProcessor::GetInstance()
#endif

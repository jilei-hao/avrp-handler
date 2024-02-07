#ifndef ABSTRACT_MODULE_HXX
#define ABSTRACT_MODULE_HXX

#include "study_config.hxx"

class AbstractModule {
public:
  virtual ~AbstractModule() = default;
  AbstractModule(const AbstractModule&) = delete;
  AbstractModule& operator=(const AbstractModule&) = delete;
  AbstractModule(AbstractModule&&) = delete;
  AbstractModule& operator=(AbstractModule&&) = delete;
  AbstractModule() {};

  // set study config
  virtual void SetStudyConfig(const StudyConfig& config) 
  {
    m_config = config;
  }

  virtual void SetGatewayHelper(GatewayHelper *gw) 
  {
    m_GatewayHelper = gw;
  }

  // run the module
  virtual void Run() = 0;

protected:
  // prepare data, config; change module status
  virtual void Initialize() = 0;

  // upload data, config; change module status
  virtual void Finalize() = 0;

  StudyConfig m_config;
  GatewayHelper *m_GatewayHelper;
};

#endif
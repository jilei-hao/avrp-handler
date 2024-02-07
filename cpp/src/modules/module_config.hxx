#ifndef MODULE_CONFIG_HXX
#define MODULE_CONFIG_HXX

#include <iostream>

class ModuleConfig
{
public:
  ModuleConfig() {}
  ~ModuleConfig() {}
  ModuleConfig(const ModuleConfig&) = default;
  ModuleConfig& operator=(const ModuleConfig&) = default;

  int m_ModuleID;
  std::string m_ModuleName;
  
};

#endif
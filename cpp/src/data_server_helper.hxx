#ifndef DATA_SERVER_HELPER_HXX
#define DATA_SERVER_HELPER_HXX

#include <iostream>
#include <string>
#include <nlohmann/json.hpp>
#include <cpr/cpr.h>
#include "handler_parameters.hxx"

class DataServerHelper
{
public:
  DataServerHelper(std::string url): m_Url(url) {}
  ~DataServerHelper() {}
  DataServerHelper(const DataServerHelper&) = default;
  DataServerHelper& operator=(const DataServerHelper&) = default;

  // returns the file path of the data downloaded
  std::string GetData(uint64_t dsid, std::string extension)
  {
    std::cout << "[DataServerHelper::GetData](dsid: " << dsid << ")" << std::endl;

    // send get request to the data server
    cpr::Response r = cpr::Get(cpr::Url{m_Url + "/data?id=" + std::to_string(dsid)});

    std::cout << "[DataServerHelper::GetData](dsid: " << dsid << ") Response status: " << r.status_code << std::endl;

    // Save the response body to a file
    HandlerParameters& params = HandlerParameters::getInstance();
    std::string filename = params.getDownloadDir() + "/" + std::to_string(dsid) + "." + extension;
    std::ofstream outFile(filename);
    outFile << r.text;
    outFile.close();

    std::cout << "[DataServerHelper::GetData](dsid: " << dsid << ")" << "Saved to " << filename << std::endl;

    return filename;
  }

private:
  std::string m_Url;
};

#endif
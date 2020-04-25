/**
 * @file config_file_resolver.h
 * @author DustinKsi (dustinksi@126.com)
 * @brief 
 * @version 0.1
 * @date 2019-12-08
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#pragma once

#include <vector>

#include "dsfmapping/common/lua_param_dictionary.h"
#include "dsfmapping/common/port.h"

namespace DsFMapping {
namespace common {

class ConfigurationFileResolver : public FileResolver {
 public:
  explicit ConfigurationFileResolver(
      const std::vector<std::string>& configuration_files_directories);

  std::string GetFullPathOrDie(const std::string& basename) override;
  std::string GetFileContentOrDie(const std::string& basename) override;

 private:
  std::vector<std::string> configuration_files_directories_;
};

}  // namespace common
}  // namespace DsFMapping

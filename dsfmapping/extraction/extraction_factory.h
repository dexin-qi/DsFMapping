/******************************************************************************
* Copyright Authors DustinKsi@ Youibot 2019. All Rights Reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*****************************************************************************/

#pragma once

#include <memory>

#include <dsfmapping/common/utils/factory.h>
#include <dsfmapping/extraction/interface/abstract_extraction.h>

namespace DsFMapping {
namespace Extraction {
class ExtractionFactory
    : public DsFMapping::common::utils::Factory<ExtractionBrand,
                                          AbstractExtraction> {
public:
  /**
   * @brief Regist Extraction instance handler to Factory.
   *
   */
  void RegisterExtractionFactory();

  /**
   * @brief Creates an AbstractExtraction object based on
   * ExtractionOptions
   * @param options is defined in extraction_options.proto
   */
  std::unique_ptr<AbstractExtraction>
  CreateExtraction(const ExtractionOptions &options);
};
}
}
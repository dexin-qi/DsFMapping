/**
 * @file extraction_factory.cc
 * @author DustinKsi (dustinksi@126.com)
 * @brief
 * @version 0.1
 * @date 2019-12-11
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "dsfmapping/extraction/extraction_factory.h"

#include "dsfmapping/extraction/intensity_extraction/intensity_extraction.h"
#include "dsfmapping/extraction/corner_extraction/corner_extraction.h"

namespace DsFMapping {
namespace Extraction {

void ExtractionFactory::RegisterExtractionFactory() {
    Register(DsFMapping::Extraction::Intensity, []() -> AbstractExtraction
    * {
      return new IntensityExtraction();
    });

    Register(DsFMapping::Extraction::Corner, []() -> AbstractExtraction * {
      return new CornerExtraction();
    });
}

std::unique_ptr<AbstractExtraction>
ExtractionFactory::CreateExtraction(const ExtractionOptions &options)
{
  auto abstract_factory = CreateObject(options.brand());
  if (!abstract_factory) {
    D_ERROR << "ExtractionFactory failed to create instance";
  } else {
    abstract_factory->SetExtractionOptions(options);
  //  CLASS_LOG(ExtractionFactory) << " successfully created instance";
  }
  return abstract_factory;
}

}
}
/**
 * @file abstract_extraction.cc
 * @author DustinKsi (dustinksi@126.com)
 * @brief
 * @version 0.1
 * @date 2019-12-11
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "dsfmapping/extraction/interface/abstract_extraction.h"

namespace DsFMapping {
namespace Extraction {

void AbstractExtraction::SetExtractionOptions(const ExtractionOptions &options) {
  _options = options;
}

}  // namespace DsFMapping
}  // namespace Extraction

/**
 * @file abstract_association.cc
 * @author DustinKsi (dustinksi@126.com)
 * @brief
 * @version 0.1
 * @date 2019-12-11
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "dsfmapping/association/interface/abstract_association.h"

namespace DsFMapping {
namespace Association {
  
void AbstractAssociation::SetAssocoiationOptions(const AssociationOptions &options) {
  _options = options;
}

}
}
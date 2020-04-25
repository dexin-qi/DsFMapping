/**
 * @file association_factory.cc
 * @author DustinKsi (dustinksi@126.com)
 * @brief
 * @version 0.1
 * @date 2019-12-11
 *
 * @copyright Copyright (c) 2019
 *
 */

#include <dsfmapping/association/association_factory.h>

#include <dsfmapping/association/dbscan_association/dbscan_association.h>
#include <dsfmapping/association/dsu_association/dsu_association.h>

namespace DsFMapping {
namespace Association {

void AssociationFactory::RegisterAssociationFactory() {
  Register(DsFMapping::Association::DBscan,
           []() -> AbstractAssociation * { return new DBscanAssociation(); });

  Register(DsFMapping::Association::DSU, []() -> AbstractAssociation * { return new DSUAssociation(); });
}

std::unique_ptr<AbstractAssociation> AssociationFactory::CreateAssociation(
    const AssociationOptions &options) {
  auto abstract_factory = CreateObject(options.brand());
  if (!abstract_factory) {
    D_ERROR << "AssociationFactory failed to create instance";
  } else {
    abstract_factory->SetAssocoiationOptions(options);
    // CLASS_LOG(AssociationFactory) << " successfully created instance";
  }
  return abstract_factory;
}

}
}

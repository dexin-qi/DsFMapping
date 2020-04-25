/**
 * @file association_options_phrase.cc
 * @author DustinKsi (dustinksi@126.com)
 * @brief
 * @version 0.1
 * @date 2019-12-11
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "dsfmapping/association/association_options_phrase.h"

namespace DsFMapping {
namespace Association {

AssociationOptions CreateOptions(ParamDict* const association_params) {
  AssociationOptions options;
  options.set_merge_distance(association_params->GetDouble("merge_distance"));
  options.set_reflect_cylinder_diameter(association_params->GetDouble("reflect_cylinder_diameter"));
  options.set_dbscan_eps_radius(association_params->GetDouble("dbscan_eps_radius"));
  options.set_dbscan_min_points(association_params->GetInt("dbscan_min_points"));
  options.set_dsu_merge_max_distance(association_params->GetDouble("dsu_merge_max_distance"));
  options.set_dsu_merge_min_points(association_params->GetInt("dsu_merge_min_points"));
  options.set_deadzone_radius(association_params->GetDouble("deadzone_radius"));

  D_INFO << "================DsFMapping::Association================";
  PARAM_LOG(merge_distance) << options.merge_distance();
  PARAM_LOG(reflect_cylinder_diameter) << options.reflect_cylinder_diameter();
  PARAM_LOG(dbscan_eps_radius) << options.dbscan_eps_radius();
  PARAM_LOG(dbscan_min_points) << options.dbscan_min_points();
  PARAM_LOG(dsu_merge_max_distance) << options.dsu_merge_max_distance();
  PARAM_LOG(dsu_merge_min_points) << options.dsu_merge_min_points();
  PARAM_LOG(deadzone_radius) << options.deadzone_radius();

  return options;
}

}  // Association
}  // DsFMapping
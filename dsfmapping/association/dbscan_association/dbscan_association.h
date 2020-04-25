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

#include <unordered_map>
#include <vector>

#include "dsfmapping/association/interface/abstract_association.h"

using std::unordered_map;
using std::vector;
using std::pair;

namespace DsFMapping {
namespace Association {
class DBscanAssociation : public AbstractAssociation {
 private:
  enum PointStatus { FAILURE = -3, NOISE, UNCLASSIFIED, CLASSIFIED };

  struct PointDBSCAN {
    PointStatus status;
    int id;
    double x;
    double y;

    PointDBSCAN(double px, double py) {
      x = px;
      y = py;
      status = UNCLASSIFIED;
      id = 0;
    }
  };

  double reflect_cylinder_radius;
  unsigned int dbscan_min_points;
  float dbscan_eps_radius_square;

  vector<PointDBSCAN> dataset;
  vector<pair<double, double> > center_list;

 public:
  void Init();

  bool Association(DsFMapping::Sensor::IntensityRange2D& candidate_cloud,
                   DsFMapping::Sensor::Feature2DList& feature_list);

  /**
   * @brief merge origin cluster result
   *
   * @param tmp_cluster a temp cluster result of origin dataset
   */
  void merge_cluster(vector<pair<double, double> >& tmp_cluster);

  /**
   * @brief expand dbscan cluster by one point and it's id
   *
   * @param point the {core} point in dataset
   * @param cluster_id the {core}'s id
   * @return true cluster expand success, got it's neighboor points
   * @return false cluster expand failed, maybe it's noise points
   */
  bool expand_cluster(vector<PointDBSCAN>::iterator point, int cluster_id);

  void calculate_cluster(vector<int>& cluster_index, vector<PointDBSCAN>::iterator point);

  inline double distance_square(vector<PointDBSCAN>::iterator point_core,
                                vector<PointDBSCAN>::iterator point_target);

  ~DBscanAssociation();

 private:
  friend class AssociationFactory;
  DBscanAssociation();
};
}
}
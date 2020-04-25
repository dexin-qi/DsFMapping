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
#include <unordered_set>
#include <vector>

#include "dsfmapping/association/interface/abstract_association.h"

using std::vector;
using std::pair;
using std::make_pair;
using std::unordered_map;
using std::unordered_set;

namespace DsFMapping {
namespace Association {

class DSUAssociation : public AbstractAssociation {
 private:
  class DSU {
   private:
    vector<int> root;

   public:
    DSU(int n);
    int find(int x);
    void merge(int x, int y);
  };

  double reflect_cylinder_radius;
  double dsu_merge_max_distance_square;
  int dsu_merge_min_points;

  vector<pair<double, double> > dataset;

 public:
  void Init();

  bool Association(DsFMapping::Sensor::IntensityRange2D& candidate_cloud,
                   DsFMapping::Sensor::Feature2DList& feature_list);

  void result_cleanup(vector<pair<double, double> >& tmp_cluster, vector<int>& tmp_cluster_weight,
                      double search_radius_square, bool merge_target);
                      
  inline double distance_square(vector<pair<double, double> >::iterator p1,
                                vector<pair<double, double> >::iterator p2);
  ~DSUAssociation();

 private:
  friend class AssociationFactory;

  DSUAssociation();
};
}
}
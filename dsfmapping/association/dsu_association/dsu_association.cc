/**
 * @file dsu_association.cc
 * @author DustinKsi (dustinksi@126.com)
 * @brief
 * @version 0.1
 * @date 2019-12-11
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "dsfmapping/association/dsu_association/dsu_association.h"

namespace DsFMapping {

namespace Association {

DSUAssociation::DSU::DSU(int n) {
  root.resize(n);
  for (int i = 0; i < n; i++) {
    root[i] = i;
  }
}

int DSUAssociation::DSU::find(int x) {
  if (x != root[x]) {
    root[x] = find(root[x]);
  }
  return root[x];
}

void DSUAssociation::DSU::merge(int x, int y) { root[find(x)] = find(y); }

void DSUAssociation::Init() {
  reflect_cylinder_radius = _options.reflect_cylinder_diameter() / 2.0;
  dsu_merge_max_distance_square = pow(_options.dsu_merge_max_distance(), 2);
  dsu_merge_min_points = _options.dsu_merge_min_points();
}

bool DSUAssociation::Association(DsFMapping::Sensor::IntensityRange2D& candidate_cloud,
                                 DsFMapping::Sensor::Feature2DList& feature_list) {
  dataset.clear();
  for (auto p : candidate_cloud.points()) {
    dataset.emplace_back(make_pair(p.x(), p.y()));
  }

  int sz = dataset.size();
  if (sz == 0) {
    return false;
  }

  DSU dsu(sz);
  for (int i = 0; i < sz - 1; i++) {
    for (int j = i + 1; j < sz; j++) {
      if (distance_square(dataset.begin() + i, dataset.begin() + j) <
          dsu_merge_max_distance_square) {
        dsu.merge(i, j);
      }
    }
  }

  unordered_map<int, unordered_set<int> > res;
  for (int i = 0; i < sz; i++) {
    res[dsu.find(i)].insert(i);
  }

  vector<pair<double, double> > tmp_res;
  vector<int> tmp_res_weight;
  for (auto pr : res) {
    if (pr.second.size() > (uint32_t)dsu_merge_min_points) {
      double avr_x = 0.0, avr_y = 0.0;

      auto iter = pr.second.begin();
      for (; iter != pr.second.end(); iter++) {
        avr_x += dataset[*iter].first;
        avr_y += dataset[*iter].second;
      }
      int set_sz = pr.second.size();
      avr_x = avr_x / double(set_sz);
      avr_y = avr_y / double(set_sz);

      tmp_res.push_back(std::make_pair(avr_x, avr_y));
      tmp_res_weight.push_back(set_sz);
    }
  }

  double merge_radius_square = _options.merge_distance() * _options.merge_distance();
  result_cleanup(tmp_res, tmp_res_weight, merge_radius_square, true);
  double deadzone_radius_square = _options.deadzone_radius() * _options.deadzone_radius();
  result_cleanup(tmp_res, tmp_res_weight, deadzone_radius_square, false);
  

  DsFMapping::Sensor::Feature2DWithID* new_feature_2d;
  for (auto pr : tmp_res) {
    new_feature_2d = feature_list.add_feature_2d_with_ids();
    new_feature_2d->set_id(-1);

    double distance = sqrt(pow(pr.first, 2) + pow(pr.second, 2));
    double factor = 1 + reflect_cylinder_radius / distance;

    new_feature_2d->set_x(factor * pr.first);
    new_feature_2d->set_y(factor * pr.second);
  }

  return true;
}

void DSUAssociation::result_cleanup(vector<pair<double, double> >& tmp_cluster,
                                    vector<int>& tmp_cluster_weight, double search_radius_square,
                                    bool merge_target) {
  int sz = tmp_cluster.size();
  int i = 0, j;
  bool got_merger_target = false;
  for (; i < sz; i++) {
    for (j = i + 1; j < sz; j++) {
      double new_distance = distance_square(tmp_cluster.begin() + i, tmp_cluster.begin() + j);
      if (new_distance < search_radius_square) {
        got_merger_target = true;
        break;
      }
    }
    if (got_merger_target) {
      break;
    }
  }

  if (!got_merger_target) {
    return;
  }

  if (merge_target) {
    D_INFO << "merge: [" << i << "][" << j << "]";
    tmp_cluster[i].first = (tmp_cluster[i].first + tmp_cluster[j].first) / 2.0;
    tmp_cluster[i].second = (tmp_cluster[i].second + tmp_cluster[j].second) / 2.0;
    tmp_cluster.erase(tmp_cluster.begin() + i);
  } else {
    if (tmp_cluster_weight[i] < tmp_cluster_weight[j]) {
      tmp_cluster.erase(tmp_cluster.begin() + i);
    } else {
      tmp_cluster.erase(tmp_cluster.begin() + j);
    }
  }
  result_cleanup(tmp_cluster, tmp_cluster_weight, search_radius_square, merge_target);
}

inline double DSUAssociation::distance_square(vector<pair<double, double> >::iterator p1,
                                              vector<pair<double, double> >::iterator p2) {
  return pow(p1->first - p2->first, 2) + pow(p1->second - p2->second, 2);
}

DSUAssociation::DSUAssociation() { CLASS_LOG(DSUAssociation) << "built!!"; }

DSUAssociation::~DSUAssociation() { CLASS_LOG(DSUAssociation) << "released!!"; }
}
}
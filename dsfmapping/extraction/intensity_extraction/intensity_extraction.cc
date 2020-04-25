/**
 * @file intensity_extraction.cc
 * @author DustinKsi (dustinksi@126.com)
 * @brief
 * @version 0.1
 * @date 2019-12-11
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "dsfmapping/extraction/intensity_extraction/intensity_extraction.h"

namespace DsFMapping {
namespace Extraction {

bool IntensityExtraction::Extract(DsFMapping::Sensor::IntensityRange2D &cloud,
                                  DsFMapping::Sensor::IntensityRange2D &candidate_cloud) {
  candidate_cloud.clear_points();
  candidate_cloud.set_frame_id(cloud.frame_id());
  candidate_cloud.set_timestamp(cloud.timestamp());

  int intensity_threshold = _options.intensity_down_threshold();
  int intensity_median_filter_param = _options.intensity_median_filter_param();
  int half_window = intensity_median_filter_param / 2;

  vector<double> mFilterBody;
  int cloud_sz = cloud.points_size();
  for (int id = 0; id < cloud_sz; id ++) {
    auto iter = cloud.points().begin() + id;

    mFilterBody.clear();
    for (int bias = id - half_window; bias <= id + half_window; bias++) {
      if (bias < 0) {
        mFilterBody.push_back((cloud.points().begin() + bias + cloud_sz)->intensity());
      } else if (bias >= cloud_sz) {
        mFilterBody.push_back((cloud.points().begin() + bias - cloud_sz)->intensity());
      } else {
        mFilterBody.push_back((cloud.points().begin() + bias)->intensity());
      }
    }
    std::sort(mFilterBody.begin(), mFilterBody.end());
    if (mFilterBody[half_window] >= intensity_threshold) {
      DsFMapping::Sensor::IntensityPoint2D *candidate = candidate_cloud.add_points();
      candidate->set_x(iter -> x());
      candidate->set_y(iter -> y());
    }
  }

  return true;
}

}  // namespace DsFMapping
}  // namespace Extraction

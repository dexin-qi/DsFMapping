/**
 * @file extraction_options_phrase.cc
 * @author DustinKsi (dustinksi@126.com)
 * @brief
 * @version 0.1
 * @date 2019-12-11
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "dsfmapping/extraction/extraction_options_phrase.h"

namespace DsFMapping {
namespace Extraction {

ExtractionOptions CreateOptions(ParamDict* const extraction_params) {
  ExtractionOptions options;

  options.set_use_adaptive_intensity_threshold(
      extraction_params->GetBool("use_adaptive_intensity_threshold"));
  options.set_intensity_median_filter_param(extraction_params->GetInt("intensity_median_filter_param"));
  options.set_intensity_down_threshold(extraction_params->GetInt("intensity_down_threshold"));
  options.set_corner_search_method(extraction_params->GetString("corner_search_method"));
  options.set_corner_curve_thresold(extraction_params->GetDouble("corner_curve_thresold"));

  D_INFO << "================DsFMapping::Extraction================";
  PARAM_LOG(use_adaptive_intensity_threshold)
      << (options.use_adaptive_intensity_threshold() ? "true" : "false");
  PARAM_LOG(intensity_median_filter_param) << options.intensity_median_filter_param();
  PARAM_LOG(intensity_down_threshold) << options.intensity_down_threshold();
  PARAM_LOG(corner_search_method) << options.corner_search_method();
  PARAM_LOG(corner_curve_thresold) << options.corner_curve_thresold();

  return options;
}
}
}
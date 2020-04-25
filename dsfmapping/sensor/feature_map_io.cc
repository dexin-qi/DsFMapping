/**
 * @file feature_map_io.cc
 * @author DustinKsi (dustinksi@126.com)
 * @brief
 * @version 0.1
 * @date 2019-12-24
 *
 * @copyright Copyright (c) 2019
 *
 */

#include "dsfmapping/sensor/feature_map_io.h"

namespace DsFMapping {
namespace Sensor {

bool feature_map_saver(Feature2DList& map_data, string& map_filename) {
  fstream map_writer(map_filename, ios::out | ios::binary | ios::ate);
  map_data.SerializePartialToOstream(&map_writer);
  map_writer.close();
  return true;
}

bool feature_map_loader(string& map_filename, Feature2DList* map_data) {
  fstream map_reader(map_filename, ios::in | ios::binary);
  map_data -> ParseFromIstream(&map_reader);
  map_reader.close();
  return true;
}
}
}
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

#include "dsfmapping/sensor/proto/sensor.pb.h"

#include <fstream>
#include <string>

using std::string;
using std::fstream;
using std::ios;

namespace DsFMapping {
namespace Sensor {

bool feature_map_saver(Feature2DList& map_data, string& map_filename);

bool feature_map_loader(string& map_filename, Feature2DList* map_data);
}
}
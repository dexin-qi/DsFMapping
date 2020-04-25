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

#include "dsfmapping/common/config_file_resolver.h"
#include "dsfmapping/common/lua_param_dictionary.h"
#include "dsfmapping/extraction/proto/extraction_options.pb.h"

namespace DsFMapping {
namespace Extraction {

using ParamDict = common::LuaParameterDictionary;

ExtractionOptions CreateOptions(ParamDict* const extraction_params);
}
}
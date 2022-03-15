/*
 * Copyright (c) 2021 DIY356
 * All rights reserved
 *
 * Licensed under the Apache License, Version 2.0 (the ""License"");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an ""AS IS"" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MG_BVALVE_SDK_H_
#define MG_BVALVE_SDK_H_

#include <stdbool.h>
#include "mg_bthing_sdk.h"
#include "mg_bactuator_sdk.h"
#include "mgos_bvalve.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MG_BVALVE_NEW(valve) MG_BTHING_ACTU_NEW(valve);

/*****************************************
 * Cast Functions
 */

// Convert (mgos_bvalve_t) into (struct mg_bthing_sens *)
struct mg_bthing_sens *MG_BVALVE_CAST1(mgos_bvalve_t thing);

// Convert (mgos_bvalve_t) into (struct mg_bthing_actu *)
struct mg_bthing_actu *MG_BVALVE_CAST2(mgos_bvalve_t thing);
/*****************************************/

#define MG_BVALVE_CFG(valve) ((struct mg_bvalve_cfg *)MG_BVALVE_CAST2(valve)->cfg)

struct mg_bvalve_overrides {
  mg_bthing_setting_state_handler_t setting_state_cb;
};

struct mg_bvalve_cfg {
  struct mg_bactuator_cfg base;
  struct mg_bvalve_overrides overrides;
  enum mgos_bvalve_type valve_type;
};

bool mg_bvalve_init(mgos_bvalve_t valve, enum mgos_bvalve_type valve_type,
                     struct mg_bvalve_cfg *valve_cfg,
                     struct mg_bsensor_cfg *sens_cfg);

void mg_bvalve_reset(mgos_bvalve_t valve);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MG_BVALVE_SDK_H_ */
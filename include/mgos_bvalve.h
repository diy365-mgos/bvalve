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

#ifndef MGOS_BVALVE_H_
#define MGOS_BVALVE_H_

#include <stdbool.h>
#include "mgos_bthing.h"
#include "mgos_bvalve.h"
#include "mgos_bactuator.h"
#include "mgos_bsensor.h"

#ifdef __cplusplus
extern "C" {
#endif

struct mg_bthing_actu;
typedef struct mg_bthing_actu *mgos_bvalve_t;

enum mgos_bvalve_type {
  MGOS_BVALVE_TYPE_NO = 1,          // 00001
  MGOS_BVALVE_TYPE_NC = 2,          // 00010
  MGOS_BVALVE_TYPE_SOLENOID = 4,    // 00100
  MGOS_BVALVE_TYPE_BISTABLE = 8,    // 01000
  MGOS_BVALVE_TYPE_MOTORIZED = 16,  // 10000
};

enum mgos_bvalve_state {
  MGOS_BVALVE_STATE_UNKNOWN = 0,
  MGOS_BVALVE_STATE_CLOSED = 1,
  MGOS_BVALVE_STATE_OPEN = 2,
  MGOS_BVALVE_STATE_OPENING = 3,
  MGOS_BVALVE_STATE_CLOSING = 4,
};

mgos_bthing_t MGOS_BVALVE_THINGCAST(mgos_bvalve_t valve);

mgos_bsensor_t MGOS_BVALVE_SENSCAST(mgos_bvalve_t valve);

mgos_bactuator_t MGOS_BVALVE_DOWNCAST(mgos_bvalve_t valve);

mgos_bvalve_t mgos_bvalve_create(const char *id, enum mgos_bvalve_type valve_type, const char *domain);

enum mgos_bvalve_type mgos_bvalve_get_type(mgos_bvalve_t valve);

enum mgos_bvalve_state mgos_bvalve_get_state(mgos_bvalve_t valve);

bool mgos_bvalve_set_state(mgos_bvalve_t valve, enum mgos_bvalve_state state);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* MGOS_BVALVE_H_ */
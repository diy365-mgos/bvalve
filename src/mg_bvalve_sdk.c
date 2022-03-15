#include "mgos.h"
#include "mg_bvalve_sdk.h"


/*****************************************
 * Cast Functions
 */

// Convert (mgos_bvalve_t) into (struct mg_bthing_sens *)
struct mg_bthing_sens *MG_BVALVE_CAST1(mgos_bvalve_t thing) {
  return (struct mg_bthing_sens *)thing;
}

// Convert (mgos_bvalve_t) into (struct mg_bthing_actu *)
struct mg_bthing_actu *MG_BVALVE_CAST2(mgos_bvalve_t thing) {
  return (struct mg_bthing_actu *)thing;
}
/*****************************************/

bool mg_bvalve_init(mgos_bvalve_t valve, enum mgos_bvalve_type valve_type,
                    struct mg_bvalve_cfg *valve_cfg,
                    struct mg_bsensor_cfg *sens_cfg) {
  bool is_type_ok = false;
  if (((valve_type & MGOS_BVALVE_TYPE_SOLENOID) == MGOS_BVALVE_TYPE_SOLENOID) ||
      ((valve_type & MGOS_BVALVE_TYPE_MOTORIZED) == MGOS_BVALVE_TYPE_MOTORIZED)) {
    bool is_no = ((valve_type & MGOS_BVALVE_TYPE_NO) == MGOS_BVALVE_TYPE_NO);
    bool is_nc = ((valve_type & MGOS_BVALVE_TYPE_NC) == MGOS_BVALVE_TYPE_NC);
    if (is_no && is_nc) {
      LOG(LL_ERROR, ("Invalid 'valve_type': 'NO' and 'NC' cannot both be active at the same time."));
    } else if (!is_no && !is_nc) {
      LOG(LL_ERROR, ("Invalid 'valve_type': 'NO' or 'NC' must be set."));
    } else {
      is_type_ok = true;
    }
  } else if ((valve_type & MGOS_BVALVE_TYPE_BISTABLE) == MGOS_BVALVE_TYPE_BISTABLE) {
    is_type_ok = true;
  }

  if (is_type_ok) {
    if (valve_cfg) {
      // init actuator-base obj
      if (mg_bactuator_init(valve, &valve_cfg->base, sens_cfg)) {
        /* initalize general settings */
        valve_cfg->valve_type = valve_type;
        /* initalize overrides cfg */
        valve_cfg->overrides.setting_state_cb = NULL;
      
        return true; // initialization successfully completed
      }
      mg_bvalve_reset(valve);
    } else {
      LOG(LL_ERROR, ("Invalid NULL 'valve_cfg' parameter."));
    }
  } else {
    LOG(LL_ERROR, ("Invalid 'valve_type' parameter value (%d).", valve_type));
  }

  LOG(LL_ERROR, ("Error initializing bValve '%s'. See above error message for more details.",
    mgos_bthing_get_uid(MGOS_BVALVE_THINGCAST(valve))));
  return false; 
}

void mg_bvalve_reset(mgos_bvalve_t valve) {
  struct mg_bvalve_cfg *cfg = MG_BVALVE_CFG(valve);

  /* clear overrides cfg */
  if (cfg->overrides.setting_state_cb) {
    mg_bthing_on_setting_state(valve, cfg->overrides.setting_state_cb);
    cfg->overrides.setting_state_cb = NULL;
  }

  // reset actuator-base obj
  mg_bactuator_reset(valve);
}

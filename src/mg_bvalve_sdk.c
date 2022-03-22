#include "mgos.h"
#include "mg_bthing_sdk.h"
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
  if (((valve_type & MGOS_BVALVE_TYPE_NO) == MGOS_BVALVE_TYPE_NO) &&
      ((valve_type & MGOS_BVALVE_TYPE_NC) == MGOS_BVALVE_TYPE_NC)) {
    // ERROR: the valve is set as both NO and NC 
    LOG(LL_ERROR, ("Invalid 'valve_type': 'NO' and 'NC' cannot both be set at the same time."));
  } else if ((valve_type & MGOS_BVALVE_TYPE_BISTABLE) == MGOS_BVALVE_TYPE_BISTABLE) {
    // Bistable valve: NO and NC flags are optional
    is_type_ok = true;
  } else {
    // Solenoid or motorized valve...
    if (((valve_type & MGOS_BVALVE_TYPE_NO) != MGOS_BVALVE_TYPE_NO) &&
        ((valve_type & MGOS_BVALVE_TYPE_NC) != MGOS_BVALVE_TYPE_NC)) {
      // NO and NC flags are mandatory for solenoid and motorized valves
      LOG(LL_ERROR, ("Invalid 'valve_type': 'NO' or 'NC' must be set."));
    } else {
      is_type_ok = true;
    }
  }

  if (is_type_ok) {
    if (valve_cfg) {
      // init actuator-base obj
      if (mg_bactuator_init(valve, &valve_cfg->base, sens_cfg)) {
        /* initalize general settings */
        valve_cfg->valve_type = valve_type;
        /* initalize overrides cfg */
        valve_cfg->overrides.setting_state_cb = NULL;

        // set initial state
        enum mgos_bvalve_state initial_state = MGOS_BVALVE_STATE_UNKNOWN;
        if ((valve_type & MGOS_BVALVE_TYPE_NO) == MGOS_BVALVE_TYPE_NO)
          initial_state = MGOS_BVALVE_STATE_OPEN;
        else if ((valve_type & MGOS_BVALVE_TYPE_NC) == MGOS_BVALVE_TYPE_NC)
          initial_state = MGOS_BVALVE_STATE_CLOSED;
        mgos_bvar_set_integer(mg_bthing_get_state_4update(MGOS_BVALVE_THINGCAST(valve)), initial_state);
      
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

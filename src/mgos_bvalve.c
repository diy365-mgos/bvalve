#include "mgos.h"
#include "mgos_bthing.h"
#include "mg_bvalve_sdk.h"
#include "mgos_bvalve.h"

#ifdef MGOS_HAVE_MJS
#include "mjs.h"
#endif

mgos_bthing_t MGOS_BVALVE_THINGCAST(mgos_bvalve_t valve) {
  return MG_BTHING_SENS_CAST4(MG_BVALVE_CAST1(valve));
}

mgos_bsensor_t MGOS_BVALVE_SENSCAST(mgos_bvalve_t valve) {
  return (mgos_bsensor_t)MG_BVALVE_CAST1(valve);
}

mgos_bactuator_t MGOS_BVALVE_DOWNCAST(mgos_bvalve_t valve) {
  return (mgos_bactuator_t)valve;
}

mgos_bvalve_t mgos_bvalve_create(const char *id, enum mgos_bvalve_type valve_type, const char *domain) {
  mgos_bvalve_t MG_BVALVE_NEW(valve);
  if (mg_bthing_init(MG_BTHING_ACTU_CAST4(valve), id, MGOS_BVALVE_TYPE, domain)) {
    struct mg_bvalve_cfg *valve_cfg = calloc(1, sizeof(struct mg_bvalve_cfg));
    struct mg_bsensor_cfg *sens_cfg = calloc(1, sizeof(struct mg_bsensor_cfg));
    if (sens_cfg && valve_cfg) {
      mgos_bthing_t thing = MGOS_BVALVE_THINGCAST(valve);
      if (mg_bvalve_init(valve, valve_type, valve_cfg, sens_cfg) && mg_bthing_register(thing)) {
        LOG(LL_INFO, ("bValve '%s' successfully created.", mgos_bthing_get_uid(thing)));
        return valve;
      }
    } else {
      LOG(LL_ERROR, ("Unable to allocate memory for 'mg_bsensor_cfg' and/or 'mg_bvalve_cfg'"));
    }
    free(sens_cfg);
    free(valve_cfg);
    mg_bthing_reset(MG_BTHING_ACTU_CAST4(valve));
  }
  free(valve);
  LOG(LL_ERROR, ("Error creating bValve '%s'. See above error message for more details.'", (id ? id : "")));
  return NULL; 
}

enum mgos_bvalve_type mgos_bvalve_get_type(mgos_bvalve_t valve) {
  if (valve) {
    struct mg_bvalve_cfg *cfg = MG_BVALVE_CFG(valve);
    if (cfg) {
      return cfg->valve_type;
    }
  }
  return (enum mgos_bvalve_type)-1;
}

enum mgos_bvalve_state mgos_bvalve_get_state(mgos_bvalve_t valve) {
  mgos_bvarc_t state = mgos_bthing_get_state(MGOS_BVALVE_THINGCAST(valve));
  if (mgos_bvar_get_type(valve) == MGOS_BVAR_TYPE_INTEGER) {
    return (enum mgos_bvalve_state)mgos_bvar_get_integer(valve);
  }
  return (enum mgos_bvalve_state)-1;
}

bool mgos_bvalve_set_state(mgos_bvalve_t valve, enum mgos_bvalve_state state) {
  bool ret = false;
  if (valve && (state == MGOS_BVALVE_STATE_CLOSED || state == MGOS_BVALVE_STATE_OPEN)) {
    mgos_bvar_t var_state = mgos_bvar_new_integer(state);
    ret = mgos_bthing_set_state(MGOS_BVALVE_THINGCAST(valve), MGOS_BVAR_CONST(var_state));
    mgos_bvar_free(var_state);
  }
  return ret;
}

bool mgos_bvalve_init() {
  return true;
}
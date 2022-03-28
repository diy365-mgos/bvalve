# bValves Library
## Overview
A bValve allows you to easily manage valves. You can find some [examples here](https://github.com/diy365-mgos/bvalve-gpio#get-started) on how to use bValves to control valves.
## Inherited APIs
A bValve inherits inherits APIs from:
- [bThing](https://github.com/diy365-mgos/bthing)
- [bSensor](https://github.com/diy365-mgos/bsensor)
- [bActuator](https://github.com/diy365-mgos/bactuator)
### Remarks on: mgos_bthing_on_get_state()
The [get-state handler](https://github.com/diy365-mgos/bthing#mgos_bthing_get_state_handler_t) must set the `state` parameter to one of the [enum mgos_bvalve_state](#mgos_bvalve_state) values.
```c
static bool my_get_state_handler(mgos_bthing_t thing, mgos_bvar_t state, void *userdata) {
  enum mgos_bvalve_state valve_state = MGOS_BVALVE_STATE_OPENING; // or any other allowed enum value
  mgos_bvar_set_integer(state, valve_state):
  return true;
}
mgos_bthing_on_get_state(..., my_get_state_handler, NULL);
```
### Remarks on: mgos_bthing_get_state()
The [mgos_bthing_get_state()](https://github.com/diy365-mgos/bthing#mgos_bthing_get_state) returns an [enum mgos_bvalve_state](#mgos_bvalve_state) value. Alternatively you can use the [mgos_bvalve_get_state()](#mgos_bvalve_get_state) helper function.
```c
mgos_bvalve_t valve = mgos_bvalve_create(...);
mgos_bvarc_t state = mgos_bthing_get_state(MGOS_BVALVE_THINGCAST(valve));
enum mgos_bvalve_state valve_state = (enum mgos_bvalve_state)mgos_bvar_get_integer(state);
```
### Remarks on: mgos_bthing_on_set_state()
The `state` parameter value in the [set-state handler](https://github.com/diy365-mgos/bthing#mgos_bthing_set_state_handler_t) is a [enum mgos_bvalve_state](#mgos_bvalve_state) value and it can be `MGOS_BVALVE_STATE_OPEN` or `MGOS_BVALVE_STATE_CLOSED`.
```c
static bool my_set_state_handler(mgos_bthing_t thing, mgos_bvarc_t state, void *userdata) {
  enum mgos_bvalve_state state_to_set = (enum mgos_bvalve_state)mgos_bvar_get_integer(state)
  if (state_to_set == MGOS_BVALVE_STATE_OPEN)
    // open the valve
  else if (state_to_set == MGOS_BVALVE_STATE_CLOSED)
    // close the valve
  else
    return false; // invalid requested state
  return true;
}
mgos_bvalve_t valve = mgos_bvalve_create(...);
mgos_bthing_on_set_state(MGOS_BVALVE_THINGCAST(valve), my_set_state_handler, NULL);
```
### Remarks on: mgos_bthing_set_state()
The [mgos_bthing_set_state()](https://github.com/diy365-mgos/bthing#mgos_bthing_set_state) allows allows one of the following [enum mgos_bvalve_state](#mgos_bvalve_state) values as input parameter: `MGOS_BVALVE_STATE_OPEN` or `MGOS_BVALVE_STATE_CLOSED`. No other values are allowed. Alternatively you can use the [mgos_bvalve_set_state()](#mgos_bvalve_set_state) helper function.
```c
mgos_bvalve_t valve = mgos_bvalve_create(...);
mgos_bvar_t state = mgos_bvar_new_integer(MGOS_BVALVE_STATE_CLOSED);
mgos_bthing_set_state(MGOS_BVALVE_THINGCAST(valve), MGOS_BVAR_CONST(state));
mgos_bvar_free(state);
```
## C/C++ APIs Reference
### MGOS_BVALVE_TYPE
```c
#define MGOS_BVALVE_TYPE 
```
The bValve type ID. It can be used with [mgos_bthing_is_typeof()](https://github.com/diy365-mgos/bthing#mgos_bthing_is_typeof).

Example:
```c
mgos_bvalve_t valve = mgos_bvalve_create(...);
if (mgos_bthing_is_typeof(MGOS_BVALVE_THINGCAST(valve), MGOS_BVALVE_TYPE))
  LOG(LL_INFO, ("I'm a bValve."));
if (mgos_bthing_is_typeof(MGOS_BVALVE_THINGCAST(valve), MGOS_BACTUATOR_TYPE))
  LOG(LL_INFO, ("I'm a bActuator."));
if (mgos_bthing_is_typeof(MGOS_BVALVE_THINGCAST(valve), MGOS_BTHING_TYPE_ACTUATOR))
  LOG(LL_INFO, ("I'm a bThing actuator."));
if (mgos_bthing_is_typeof(MGOS_BVALVE_THINGCAST(valve), MGOS_BSENSOR_TYPE))
  LOG(LL_INFO, ("I'm a bSensor."));
if (mgos_bthing_is_typeof(MGOS_BVALVE_THINGCAST(valve), MGOS_BTHING_TYPE_SENSOR))
  LOG(LL_INFO, ("I'm a bThing sensor."));
```
Output console:
```bash
I'm a bValve.
I'm a bActuator.
I'm a bThing actuator.
I'm a bSensor.
I'm a bThing sensor.
```
### MGOS_BVALVE_THINGCAST
```c
mgos_bthing_t MGOS_BVALVE_THINGCAST(mgos_bvalve_t valve);
```
Casts a bValve to a generic bThing to be used with [inherited bThing APIs](https://github.com/diy365-mgos/bthing).

|Parameter||
|--|--|
|valve|A bValve.|

Example:
```c
mgos_bvalve_t valve = mgos_bvalve_create(...);
LOG(LL_INFO, ("%s successfully created.", mgos_bthing_get_uid(MGOS_BVALVE_THINGCAST(valve))));
```
### MGOS_BVALVE_SENSCAST
```c
mgos_bsensor_t MGOS_BVALVE_SENSCAST(mgos_bvalve_t valve);
```
Casts a bValve to a bSensor to be used with [inherited bSensor APIs](https://github.com/diy365-mgos/bsensor).

|Parameter||
|--|--|
|valve|A bValve.|
### MGOS_BVALVE_DOWNCAST
```c
mgos_bactuator_t MGOS_BVALVE_DOWNCAST(mgos_bvalve_t valve);
```
Casts a bValve to a bActuator to be used with [inherited bActuator APIs](https://github.com/diy365-mgos/bactuator).

|Parameter||
|--|--|
|valve|A bValve.|
### mgos_bvalve_type
```c
enum mgos_bvalve_type {
  MGOS_BVALVE_TYPE_NO = 1,
  MGOS_BVALVE_TYPE_NC = 2,
  MGOS_BVALVE_TYPE_SOLENOID = 4,
  MGOS_BVALVE_TYPE_BISTABLE = 8,
  MGOS_BVALVE_TYPE_MOTORIZED = 16,
};
```
bValve types.

|Type||
|--|--|
|MGOS_BVALVE_TYPE_NO|Normally open valve.|
|MGOS_BVALVE_TYPE_NC|Normally closed valve.|
|MGOS_BVALVE_TYPE_SOLENOID|Solenoid valve. This must be used in combination with `MGOS_BVALVE_TYPE_NO` or with `MGOS_BVALVE_TYPE_NC`.|
|MGOS_BVALVE_TYPE_BISTABLE|Bistable valve. Optionally, this can be used in combination with `MGOS_BVALVE_TYPE_NO` or with `MGOS_BVALVE_TYPE_NC`.|
|MGOS_BVALVE_TYPE_MOTORIZED|Motorized valve. This must be used in combination with `MGOS_BVALVE_TYPE_NO` or with `MGOS_BVALVE_TYPE_NC`.|
```c
// Example: normally open solenoid valve
enum mgos_bvalve_type type1 = (MGOS_BVALVE_TYPE_SOLENOID | MGOS_BVALVE_TYPE_NO);
// Example: normally open motorized valve
enum mgos_bvalve_type type2 = (MGOS_BVALVE_TYPE_MOTORIZED | MGOS_BVALVE_TYPE_NO);
```
### mgos_bvalve_create
```c
mgos_bvalve_t mgos_bvalve_create(const char *id, enum mgos_bvalve_type valve_type, const char *domain);
```
Creates a bValve. Returns `NULL` on error.

|Parameter||
|--|--|
|id|The bValve ID.|
|valve_type|The valve [type](#mgos_bvalve_type).|
|domain|The domain name or `NULL`.|

Examples:
```c
// Create a bistable valve
mgos_bvalve_t v1 = mgos_bvalve_create("v1", MGOS_BVALVE_TYPE_BISTABLE, NULL);
// Create a solenoid NC (normally closed() valve
mgos_bvalve_t v2 = mgos_bvalve_create("v2", MGOS_BVALVE_TYPE_SOLENOID | MGOS_BVALVE_TYPE_NC, NULL);
// Create a motorized NO (normally open) valve
mgos_bvalve_t v3 = mgos_bvalve_create("v3", MGOS_BVALVE_TYPE_MOTORIZED | MGOS_BVALVE_TYPE_NO, NULL);
```
### mgos_bvalve_get_type
```c
enum mgos_bvalve_type mgos_bvalve_get_type(mgos_bvalve_t valve);
```
Gest the bValve's [type](#mgos_bvalve_type).

|Parameter||
|--|--|
|valve|A bValve.|
### mgos_bvalve_state
```c
enum mgos_bvalve_state {
  MGOS_BVALVE_STATE_CLOSED = 0,
  MGOS_BVALVE_STATE_OPEN = 1,
  MGOS_BVALVE_STATE_OPENING = 2,
  MGOS_BVALVE_STATE_CLOSING = 3,
  MGOS_BVALVE_STATE_UNKNOWN = 4,
};
```
bValve states.
### mgos_bvalve_get_state
```c
enum mgos_bvalve_state mgos_bvalve_get_state(mgos_bvalve_t valve);
```
Gets the [state](#mgos_bvalve_state) of a bValve.

|Parameter||
|--|--|
|valve|A bValve.|
### mgos_bvalve_set_state
```c
bool mgos_bvalve_set_state(mgos_bvalve_t valve, enum mgos_bvalve_state state);
```
Closes or opens a bValve.

|Parameter||
|--|--|
|valve|A bValve.|
|state|The [state](#mgos_bvalve_state) to set. Only `MGOS_BVALVE_STATE_OPEN` and `MGOS_BVALVE_STATE_CLOSED` values are allowed.|
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).

# bValves Library
## Overview
A bValve allows you to easily manage valves. You can find some [examples here](https://github.com/diy365-mgos/bvalve-gpio#get-started) on how to use bValves to control valves.
## C/C++ APIs Reference
### Inherited APIs
A bValve inherits inherits APIs from:
- [bThing](https://github.com/diy365-mgos/bthing)
- [bSensor](https://github.com/diy365-mgos/bsensor)
- [bActuator](https://github.com/diy365-mgos/bactuator)
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
|MGOS_BVALVE_TYPE_SOLENOID|Solenoid valve. This can be used in combination with `MGOS_BVALVE_TYPE_NO` or with `MGOS_BVALVE_TYPE_NC`.|
|MGOS_BVALVE_TYPE_BISTABLE|Bistable valve.|
|MGOS_BVALVE_TYPE_MOTORIZED|Motorized valve. This can be used in combination with `MGOS_BVALVE_TYPE_NO` or with `MGOS_BVALVE_TYPE_NC`.|
```c
// Example: normally open solenoid valve
enum mgos_bvalve_type type1 = (MGOS_BVALVE_TYPE_SOLENOID | MGOS_BVALVE_TYPE_NO);
// Example: normally open motorized valve
enum mgos_bvalve_type type2 = (MGOS_BVALVE_TYPE_MOTORIZED | MGOS_BVALVE_TYPE_NO);
```
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
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).

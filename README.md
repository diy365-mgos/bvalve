# bValves Library
## Overview
A bValve allows you to easily manage valves.
## C/C++ APIs Reference
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
## To Do
- Implement javascript APIs for [Mongoose OS MJS](https://github.com/mongoose-os-libs/mjs).

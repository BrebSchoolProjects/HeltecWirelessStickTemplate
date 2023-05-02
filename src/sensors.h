#ifndef SENSORS_H
#define SENSORS_H

#ifdef __cplusplus
extern "C"
{
#endif

bool initSensors(void);
bool readSensors(void);
#ifdef __cplusplus
}
#endif

#endif //SENSORS_H
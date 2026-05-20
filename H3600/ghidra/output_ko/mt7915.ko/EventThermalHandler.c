// module: mt7915.ko
// function: EventThermalHandler @ 0x1a7fec
// size: 28 bytes
//

void EventThermalHandler(undefined4 param_1,char *param_2)

{
  if (*param_2 == '\x01') {
    EventThermalSensorShowInfo();
    return;
  }
  if (*param_2 != '\x02') {
    return;
  }
  EventThermalSensorTaskResp();
  return;
}


// module: mt7915.ko
// function: EventThermalProtectHandler @ 0x1a7e08
// size: 52 bytes
//

void EventThermalProtectHandler(undefined4 param_1,undefined1 *param_2,undefined2 param_3)

{
  switch(*param_2) {
  case 0:
    EventThermalProtectReasonNotify();
    return;
  case 1:
    EventThermalProtectInfo();
    return;
  case 2:
    EventThermalProtDutyNotify();
    return;
  case 3:
    EventThermalRadioNotify();
    return;
  case 4:
    EventThermalProtInfo(param_1,param_2,param_3);
    return;
  case 5:
    EventThermalProtDutyInfo(param_1,param_2,param_3);
    return;
  default:
    return;
  }
}


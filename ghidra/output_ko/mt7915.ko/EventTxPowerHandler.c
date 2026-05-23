// module: mt7915.ko
// function: EventTxPowerHandler @ 0x1a870c
// size: 112 bytes
//

void EventTxPowerHandler(int param_1,undefined1 *param_2)

{
  switch(*param_2) {
  case 0:
    EventTxPowerShowInfo();
    return;
  case 1:
    break;
  case 2:
    *(undefined1 *)(param_1 + 0x285a2c) = param_2[1];
    return;
  case 3:
    EventPowerTableShowInfo();
    return;
  default:
    return;
  case 5:
    EventTxPowerAllRatePowerShowInfo();
    return;
  case 6:
    EventThermalCompTableShowInfo();
    return;
  case 7:
    EventTxvBbpPowerInfo();
    return;
  }
  if (1 < (byte)param_2[1]) {
    return;
  }
  os_move_mem((void *)(param_1 + (uint)(byte)param_2[1] * 0xc4 + 0x794ead),param_2 + 4,0xc4);
  return;
}


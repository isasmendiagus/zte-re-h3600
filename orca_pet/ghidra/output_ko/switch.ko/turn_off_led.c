// module: switch.ko
// function: turn_off_led @ 0x16b34
// size: 52 bytes
//

void turn_off_led(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = g_LAN_LEDON_COUNT + -1;
  g_LAN_LEDON_COUNT = iVar1;
  if (iVar1 != 0) {
    return;
  }
  LedActionSet(0xb200,param_1,param_3,param_4,param_4);
  g_LAN_ON_Flag = iVar1;
  return;
}


// module: switch.ko
// function: turn_off_led @ 0x16a74
// size: 36 bytes
//

void turn_off_led(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  LedActionSet(0xb200,param_1 + -1,param_3,param_4,param_4);
  g_LAN_ON_Flag = 0;
  return;
}


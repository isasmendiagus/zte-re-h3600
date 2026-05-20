// module: switch.ko
// function: turn_on_led_green @ 0x16a48
// size: 44 bytes
//

void turn_on_led_green(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  LedActionSet(0xb100,param_1 + -1,param_3,param_4,param_4);
  g_LAN_PACKET_COUNT = 0;
  g_LAN_ON_Flag = 1;
  return;
}


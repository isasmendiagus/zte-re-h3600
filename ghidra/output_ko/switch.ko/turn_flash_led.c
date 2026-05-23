// module: switch.ko
// function: turn_flash_led @ 0x16a98
// size: 116 bytes
//

void turn_flash_led(int param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  undefined1 auStack_88 [8];
  uint local_80;
  uint uStack_7c;
  
  __memzero(auStack_88,0x70);
  iVar2 = zte_api_sw_port_get_port_statistics1(param_2,auStack_88);
  if (iVar2 == 0) {
    uVar1 = (int)g_LAN_PACKET_COUNT >> 0x1f;
    bVar3 = uVar1 <= uStack_7c;
    if (uStack_7c == uVar1) {
      bVar3 = g_LAN_PACKET_COUNT <= local_80;
    }
    if (bVar3 && (uStack_7c != uVar1 || local_80 != g_LAN_PACKET_COUNT)) {
      LedActionSet(0x2200,param_1 + -1);
      g_LAN_PACKET_COUNT = local_80;
    }
  }
  else {
    turn_flash_led_part_1();
  }
  return;
}


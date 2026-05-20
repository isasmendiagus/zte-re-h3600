// module: mt7915.ko
// function: update_peer_he_params @ 0x205fec
// size: 124 bytes
//

void update_peer_he_params(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  byte bVar2;
  
  FUN_00203c78();
  FUN_00203e8c(param_1,param_2 + 6);
  FUN_0020483c(param_1,param_2 + 0x11,param_2 + 0x15,param_2 + 0x19,param_4);
  FUN_0020423c(param_1,param_2 + 0x1d);
  bVar1 = *(byte *)(param_2 + 0x20);
  bVar2 = bVar1 & 0x40;
  *(byte *)(param_1 + 0x84) = bVar1 & 0x3f;
  if ((bVar1 & 0x40) != 0) {
    bVar2 = 1;
  }
  *(byte *)(param_1 + 0x85) = bVar2;
  *(bool *)(param_1 + 0x86) = (bVar1 & 0x80) != 0;
  set_bss_color_info(*(undefined4 *)(param_1 + 8));
  return;
}


// module: tm.ko
// function: EN_V6FAST_EXTIDXTBL @ 0x57d8c
// size: 132 bytes
//

undefined4 EN_V6FAST_EXTIDXTBL(int param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  undefined1 auStack_24 [16];
  ushort local_14;
  
  __memzero(auStack_24,0x14);
  cla_get_extra_index_table(param_2,auStack_24);
  if (param_1 == 0) {
    if (param_3 == 0) {
      uVar1 = 0x40;
    }
    else {
      uVar1 = 0xc0;
    }
    local_14 = uVar1 | local_14 & 0xff3f;
  }
  else {
    if (param_3 == 0) {
      uVar1 = 4;
    }
    else {
      uVar1 = 0xc;
    }
    local_14 = uVar1 | local_14 & 0xfff3;
  }
  cla_set_extra_index_table(param_2,auStack_24);
  return 1;
}


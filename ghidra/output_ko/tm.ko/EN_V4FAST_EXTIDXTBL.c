// module: tm.ko
// function: EN_V4FAST_EXTIDXTBL @ 0x57d08
// size: 132 bytes
//

undefined4 EN_V4FAST_EXTIDXTBL(int param_1,undefined4 param_2,int param_3)

{
  ushort uVar1;
  undefined1 auStack_24 [16];
  ushort local_14;
  
  __memzero(auStack_24,0x14);
  cla_get_extra_index_table(param_2,auStack_24);
  if (param_1 == 0) {
    if (param_3 == 0) {
      uVar1 = 0x10;
    }
    else {
      uVar1 = 0x30;
    }
    local_14 = uVar1 | local_14 & 0xffcf;
  }
  else {
    if (param_3 == 0) {
      uVar1 = 1;
    }
    else {
      uVar1 = 3;
    }
    local_14 = uVar1 | local_14 & 0xfffc;
  }
  cla_set_extra_index_table(param_2,auStack_24);
  return 1;
}


// module: mt7915.ko
// function: WifiSysUpdateRa @ 0x105938
// size: 192 bytes
//

void WifiSysUpdateRa(int param_1,int param_2,void *param_3)

{
  ushort uVar1;
  void *local_230;
  undefined4 local_22c [8];
  undefined1 local_20c;
  undefined2 local_20a;
  undefined4 local_208;
  undefined1 local_204;
  undefined4 local_200;
  int local_140;
  void *local_20;
  
  uVar1 = *(ushort *)(param_2 + 0xe2);
  local_230 = (void *)0x0;
  os_zero_mem(local_22c,0x214);
  local_20a = *(undefined2 *)(param_2 + 0xe0);
  local_208 = *(undefined4 *)(param_2 + 0x1424);
  local_20c = *(undefined1 *)(*(int *)(param_2 + 8) + 0x999);
  local_140 = param_1 + (uint)uVar1 * 0x620 + 0x2f6a0;
  local_204 = 1;
  local_200 = 8;
  os_alloc_mem(0,&local_230,0x1c);
  if (local_230 != (void *)0x0) {
    os_move_mem(local_230,param_3,0x1c);
    local_22c[0] = *(undefined4 *)(param_2 + 8);
    local_20 = local_230;
    HW_WIFISYS_RA_UPDATE(param_1,local_22c);
  }
  return;
}


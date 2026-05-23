// module: mt7915.ko
// function: WifiSysRaInit @ 0x1058b8
// size: 128 bytes
//

void WifiSysRaInit(int param_1,int param_2)

{
  ushort uVar1;
  int local_224 [8];
  undefined1 local_204;
  undefined2 local_202;
  undefined4 local_200;
  undefined1 local_1fc;
  undefined4 local_1f8;
  int local_138;
  
  uVar1 = *(ushort *)(param_2 + 0xe2);
  os_zero_mem(local_224,0x214);
  local_224[0] = *(int *)(param_2 + 8);
  local_202 = *(undefined2 *)(param_2 + 0xe0);
  local_200 = *(undefined4 *)(param_2 + 0x1424);
  local_204 = *(undefined1 *)(local_224[0] + 0x999);
  local_138 = param_1 + (uint)uVar1 * 0x620 + 0x2f6a0;
  local_1fc = 1;
  local_1f8 = 2;
  HW_WIFISYS_PEER_UPDATE(param_1,local_224);
  return;
}


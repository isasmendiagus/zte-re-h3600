// module: mt7915.ko
// function: WifiSysUpdatePortSecur @ 0x1057dc
// size: 220 bytes
//

void WifiSysUpdatePortSecur(int param_1,int param_2,void *param_3)

{
  int iVar1;
  int iVar2;
  int local_22c [8];
  undefined1 local_20c;
  undefined2 local_20a;
  undefined4 local_208;
  undefined1 local_204;
  undefined4 local_200;
  undefined1 local_1fc;
  undefined1 auStack_1f8 [184];
  int local_140;
  
  iVar2 = *(int *)(param_2 + 8);
  iVar1 = (uint)*(ushort *)(param_2 + 0xe2) * 0x620;
  if (*(char *)(param_1 + iVar1 + 0x2fa88) == '\0') {
    return;
  }
  os_zero_mem(local_22c,0x214);
  local_20a = *(undefined2 *)(param_2 + 0xe0);
  local_208 = *(undefined4 *)(param_2 + 0x1424);
  local_20c = *(undefined1 *)(iVar2 + 0x999);
  local_140 = param_1 + iVar1 + 0x2f6a0;
  local_204 = 2;
  local_200 = 1;
  local_1fc = 0;
  if (param_3 != (void *)0x0) {
    local_200 = 0x1001;
    memcpy(auStack_1f8,param_3,0x88);
  }
  local_22c[0] = iVar2;
  HW_WIFISYS_PEER_UPDATE(param_1,local_22c);
  CheckBMCPortSecured(param_1,param_2,1);
  return;
}


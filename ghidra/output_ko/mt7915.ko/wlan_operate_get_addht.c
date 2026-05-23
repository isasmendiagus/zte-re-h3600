// module: mt7915.ko
// function: wlan_operate_get_addht @ 0x107f14
// size: 24 bytes
//

int wlan_operate_get_addht(int param_1)

{
  int iVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_1 + 0xb14);
  if (iVar1 != 0) {
    iVar1 = iVar1 + 0x20;
  }
  return iVar1;
}


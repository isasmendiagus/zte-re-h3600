// module: mt7915.ko
// function: build_vht_txpwr_envelope @ 0x202e3c
// size: 208 bytes
//

size_t build_vht_txpwr_envelope(undefined4 param_1,undefined4 param_2,void *param_3)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  size_t __n;
  uint uVar4;
  byte local_15;
  byte local_14 [4];
  
  iVar1 = wlan_operate_get_vht_bw(param_2);
  iVar2 = wlan_operate_get_ht_bw(param_2);
  __memzero(&local_15,5);
  if ((iVar1 - 2U & 0xff) < 2) {
    __n = 5;
    uVar4 = 3;
  }
  else if (iVar1 == 1) {
    __n = 4;
    uVar4 = 2;
  }
  else {
    uVar4 = (uint)(iVar2 == 1);
    __n = uVar4 + 2;
  }
  pbVar3 = &local_15;
  iVar1 = 0;
  local_15 = local_15 & 0xc0 | (byte)uVar4;
  do {
    iVar1 = iVar1 + 1;
    pbVar3 = pbVar3 + 1;
    *pbVar3 = 0x2f;
  } while (iVar1 <= (int)uVar4);
  memcpy(param_3,&local_15,__n);
  return __n;
}


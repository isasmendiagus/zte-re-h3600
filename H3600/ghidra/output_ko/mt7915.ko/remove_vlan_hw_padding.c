// module: mt7915.ko
// function: remove_vlan_hw_padding @ 0xc5700
// size: 284 bytes
//

void remove_vlan_hw_padding(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  byte *__s1;
  size_t __n;
  
  iVar3 = *(int *)(param_2 + 0x38);
  if (iVar3 == 0) {
    return;
  }
  __s1 = *(byte **)(iVar3 + 0xcc);
  if (CONCAT11(__s1[0xc],__s1[0xd]) == -0x7f00) {
    __n = 0x10;
    iVar1 = 0x11;
  }
  else {
    __n = 0xc;
    iVar1 = 0xd;
  }
  if ((uint)CONCAT11(__s1[__n],__s1[iVar1]) != (*(int *)(iVar3 + 100) + -2) - __n) {
    return;
  }
  if ((*(int *)(param_2 + 0x18) != 0) &&
     ((*(uint *)(*(int *)(param_2 + 0x18) + 8) & 0x2002000) == 0x2002000)) {
    iVar3 = memcmp(__s1,&_LANCHOR1,6);
    if (iVar3 == 0) {
      return;
    }
    if (((*__s1 & 1) != 0) && (iVar3 = memcmp(__s1 + 0xe,&DAT_0032f468,3), iVar3 == 0)) {
      return;
    }
  }
  memmove(__s1 + 2,__s1,__n);
  RtmpOsSkbPullRcsum(*(undefined4 *)(param_2 + 0x38),2);
  RtmpOsSkbResetNetworkHeader(*(undefined4 *)(param_2 + 0x38));
  RtmpOsSkbResetTransportHeader(*(undefined4 *)(param_2 + 0x38));
  RtmpOsSkbResetMacLen(*(undefined4 *)(param_2 + 0x38));
  uVar2 = *(undefined4 *)(*(int *)(param_2 + 0x38) + 0xcc);
  *(short *)(param_2 + 0x40) = *(short *)(param_2 + 0x40) + -2;
  *(undefined4 *)(param_2 + 0x3c) = uVar2;
  update_rxblk_addr(param_2);
  return;
}


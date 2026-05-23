// module: mt7915.ko
// function: WscCheckEnrolleeNonceFromUpnp @ 0x3c998
// size: 444 bytes
//

undefined4 WscCheckEnrolleeNonceFromUpnp(undefined4 param_1,uint *param_2,uint param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint *__s1;
  ushort uStack_3b;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  if (DebugLevel < 3) {
    if (param_3 < 5) {
      return 0;
    }
  }
  else {
    printk("check Enrollee Nonce\n");
    if (param_3 < 5) goto LAB_0003cab0;
  }
  do {
    uVar2 = *param_2;
    __s1 = param_2 + 1;
    local_38 = 0;
    local_34 = 0;
    uStack_3b = (ushort)(uVar2 >> 0x10);
    uVar3 = (uStack_3b & 0xff) << 8 | (uint)(uStack_3b >> 8);
    local_30 = 0;
    local_2c = 0;
    param_2 = (uint *)((int)__s1 + uVar3);
    if ((int)param_3 < (int)(uVar3 + 4)) {
      if (DebugLevel < 3) {
        return 0;
      }
      printk("unexpected WSC IE Length(%u)\n",uVar3);
      break;
    }
    if (((uVar2 & 0xff) << 8 | uVar2 >> 8 & 0xff) == 0x101a) {
      iVar1 = RTMPCompareMemory(param_4 + 0x1b60,__s1,0x10);
      if (iVar1 == 0) {
        if (DebugLevel < 3) {
          return 1;
        }
        printk("Nonce match!!\n");
joined_r0x0003cb24:
        if (2 < DebugLevel) {
          printk("<----- WscCheckNonce\n");
        }
        return 1;
      }
      iVar1 = memcmp(__s1,&local_38,0x10);
      if (iVar1 == 0) {
        if (DebugLevel < 3) {
          return 1;
        }
        printk("Zero Enrollee Nonce!!\n");
        goto joined_r0x0003cb24;
      }
    }
    param_3 = param_3 + (0xfffc - uVar3) & 0xffff;
  } while (4 < param_3);
LAB_0003cab0:
  if (2 < DebugLevel) {
    printk("Nonce mismatch!!\n");
  }
  return 0;
}


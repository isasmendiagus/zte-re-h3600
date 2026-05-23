// module: mt7915.ko
// function: TxOPUpdatingAlgo @ 0xc7ce0
// size: 388 bytes
//

undefined4 TxOPUpdatingAlgo(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar5 = *(uint *)(param_1 + 0xa78a18);
  uVar6 = *(uint *)(param_1 + 0xa78a1c);
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (uVar5 == 0 || uVar6 == 0) goto LAB_000c7d54;
  sVar3 = 0;
  if (*(ushort *)(param_1 + 0x285920) == 1) {
    if (((*(char *)(param_1 + 0x795b0e) != '\0') || (*(char *)(param_1 + 0x795071) == '\0')) ||
       (*(int *)(iVar1 + 0x78) != 1)) goto LAB_000c7d54;
    uVar4 = *(uint *)(param_1 + 0xa39f84);
    if ((uVar4 & 0x100000) != 0) {
      sVar3 = 0x80;
      goto LAB_000c7d38;
    }
    uVar2 = *(uint *)(param_1 + 0x795b10);
    if (uVar2 < (uVar6 + uVar5) * 8 >> 0x14) {
      if (uVar6 < uVar5) {
        uVar5 = __aeabi_uidiv(uVar5,uVar6,uVar2,uVar4,param_4);
        if (uVar5 < *(byte *)(param_1 + 0x795b14)) goto LAB_000c7de0;
      }
      else {
        uVar5 = __aeabi_uidiv(uVar6,uVar5,uVar2,uVar4,param_4);
        if (*(byte *)(param_1 + 0x795b14) <= uVar5) goto LAB_000c7df8;
LAB_000c7de0:
        if (*(byte *)(param_1 + 0x795b15) < uVar5) goto LAB_000c7d54;
        if (*(char *)(param_1 + 0x285941) != '\0') goto LAB_000c7df8;
      }
      sVar3 = 0x60;
    }
    else {
      if (2 < DebugLevel) {
        printk("Current TP=%lu < Threshold(%lu), turn-off TxOP\n");
        sVar3 = 0;
        goto LAB_000c7d38;
      }
LAB_000c7df8:
      sVar3 = 0;
    }
  }
  else if (*(ushort *)(param_1 + 0x285920) < 2) goto LAB_000c7d54;
LAB_000c7d38:
  if (*(short *)(param_1 + 0xa78a2e) != sVar3) {
    AsicUpdateTxOP(param_1,1,sVar3);
  }
LAB_000c7d54:
  *(undefined4 *)(param_1 + 0xa78a18) = 0;
  *(undefined4 *)(param_1 + 0xa78a1c) = 0;
  return 1;
}


// module: mt7915.ko
// function: net_ad_alloc_wtbl @ 0x25bda0
// size: 232 bytes
//

undefined4 net_ad_alloc_wtbl(int param_1,undefined4 param_2,int param_3,int *param_4,short *param_5)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    printk("%s: invalid adapter!\n","net_ad_alloc_wtbl");
    uVar3 = 0x606;
  }
  else if (param_3 == 0) {
    printk("%s: invalid wdev!\n","net_ad_alloc_wtbl");
    uVar3 = 0x607;
  }
  else {
    mac_entry_lookup(iVar2,param_2,param_3,param_4);
    iVar4 = *param_4;
    if (iVar4 == 0) {
      iVar4 = MacTableInsertEntry(iVar2,param_2,param_3,0x20,4,1);
      *param_4 = iVar4;
      if (iVar4 == 0) {
        return 0x600;
      }
    }
    if (param_5 == (short *)0x0) {
      uVar3 = 0;
    }
    else if (*param_5 == 0) {
      uVar3 = 0;
    }
    else {
      sVar1 = *(short *)(iVar4 + 0xf8);
      uVar3 = 0;
      *(short *)(iVar4 + 0xf8) = *param_5;
      *param_5 = sVar1;
    }
  }
  return uVar3;
}


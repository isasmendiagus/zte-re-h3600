// module: mt7915.ko
// function: WtcSetMaxStaNum @ 0xad998
// size: 176 bytes
//

uint WtcSetMaxStaNum(int param_1,int param_2,uint param_3)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  iVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(*(int *)(param_1 + 0x4328) + 0xa797a0));
  iVar2 = DebugLevel;
  uVar4 = iVar3 - ((param_3 & 0xffff) + param_2);
  uVar5 = uVar4 & 0xffff;
  uVar1 = (undefined2)uVar4;
  *(undefined2 *)(param_1 + 0x1a28) = uVar1;
  *(undefined2 *)(param_1 + 0x1a2a) = uVar1;
  if (0 < iVar2) {
    printk("%s: MaxStaNum:%d, BssidNum:%d, WdsNum:%d, MSTANum:%d, MaxNumChipRept:%d, MinMcastWcid:%d\n"
           ,"WtcSetMaxStaNum",
           uVar5 - ((param_3 & 0xffff) + (uint)*(byte *)(param_1 + 0xc7e)) & 0xffff,param_2,0,
           param_3,(uint)*(byte *)(param_1 + 0xc7e),uVar5);
  }
  return uVar5;
}


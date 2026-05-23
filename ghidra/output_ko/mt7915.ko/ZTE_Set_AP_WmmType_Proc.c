// module: mt7915.ko
// function: ZTE_Set_AP_WmmType_Proc @ 0x15f2d0
// size: 148 bytes
//

undefined4
ZTE_Set_AP_WmmType_Proc(int *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  byte bVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = *param_1;
  bVar1 = simple_strtol(param_2,0,10,param_4,param_4);
  if (1 < bVar1) {
    return 0;
  }
  bVar3 = DebugLevel < 0;
  *(byte *)((int)param_1 + *(int *)(iVar2 + 0x3c) * 0x5834 + 0x2b7b1d) = bVar1;
  if (bVar3) {
    return 1;
  }
  iVar2 = *(int *)(iVar2 + 0x3c);
  printk("IF(ra%d) Set_WmmType_Proc::(WmmType=%d)\n",iVar2,
         *(undefined1 *)((int)param_1 + iVar2 * 0x5834 + 0x2b7b1d));
  return 1;
}


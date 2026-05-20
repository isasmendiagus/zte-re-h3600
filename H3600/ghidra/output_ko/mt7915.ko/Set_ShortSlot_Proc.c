// module: mt7915.ko
// function: Set_ShortSlot_Proc @ 0xd99d0
// size: 80 bytes
//

int Set_ShortSlot_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 extraout_r2;
  
  iVar1 = RT_CfgSetShortSlot();
  if ((iVar1 == 1) && (2 < DebugLevel)) {
    printk("Set_ShortSlot_Proc::(ShortSlot=%d)\n",*(undefined1 *)(param_1 + 0x795070),extraout_r2,
           DebugLevel,param_4);
  }
  return iVar1;
}


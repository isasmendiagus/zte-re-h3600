// module: mt7915.ko
// function: mt_op_group_prek @ 0x259844
// size: 80 bytes
//

uint mt_op_group_prek(int param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    return 0x503;
  }
  if (param_2 < 3) {
    uVar2 = MtATE_Group_Pre_Cal_Store_Proc_7915(iVar1,param_2);
    return uVar2 ^ 1;
  }
  printk("%s: Invalid op\n","mt_op_group_prek");
  return 0x500;
}


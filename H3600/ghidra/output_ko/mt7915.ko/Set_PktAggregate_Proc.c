// module: mt7915.ko
// function: Set_PktAggregate_Proc @ 0xda084
// size: 156 bytes
//

undefined4
Set_PktAggregate_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  if ((iVar1 != 1) && (iVar1 != 0)) {
    return 0;
  }
  *(char *)(param_1 + 0x795072) = (char)iVar1;
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    *(undefined1 *)(param_1 + 0x795073) = *(undefined1 *)(param_1 + 0x795072);
    AsicSetPiggyBack(param_1);
  }
  if (DebugLevel < 3) {
    return 1;
  }
  printk("Set_PktAggregate_Proc::(AGGRE=%d)\n",*(undefined1 *)(param_1 + 0x795072));
  return 1;
}


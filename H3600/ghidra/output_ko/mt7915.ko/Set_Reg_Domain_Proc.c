// module: mt7915.ko
// function: Set_Reg_Domain_Proc @ 0x142614
// size: 88 bytes
//

undefined4 Set_Reg_Domain_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = simple_strtol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0xa7cc26) = uVar2;
  if (0 < iVar1) {
    printk("reg_domain = %u\n",uVar2);
  }
  return 1;
}


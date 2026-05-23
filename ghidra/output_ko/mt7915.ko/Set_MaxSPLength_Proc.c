// module: mt7915.ko
// function: Set_MaxSPLength_Proc @ 0x579d8
// size: 88 bytes
//

undefined4 Set_MaxSPLength_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 uVar2;
  
  uVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + 0x794cc4) = uVar2;
  if (2 < iVar1) {
    printk("MaxSPLength=%d\n",uVar2);
  }
  return 1;
}


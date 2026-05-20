// module: mt7915.ko
// function: Set_AuthMode_Proc @ 0x58654
// size: 144 bytes
//

undefined4 Set_AuthMode_Proc(int *param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(*param_1 + 0x3c);
  SetWdevAuthMode(param_1 + iVar2 * 0x84dec + 0xdb6e1);
  iVar1 = DebugLevel;
  *(undefined1 *)(param_1 + iVar2 * 0x84dec + 0xdb8f8) = 2;
  if (2 < iVar1) {
    printk("%s:: AKM=0x%x\n","Set_AuthMode_Proc",param_1[iVar2 * 0x84dec + 0xdb6e1]);
  }
  return 1;
}


// module: mt7915.ko
// function: GetAssociatedAPByWdev @ 0x14aa20
// size: 140 bytes
//

undefined4 GetAssociatedAPByWdev(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  if (param_2 == 0) {
    return 0;
  }
  iVar1 = *(int *)(param_2 + 4);
  if ((iVar1 != 0) &&
     ((param_3 = *(int *)(param_2 + 0x14), param_3 == 2 ||
      ((param_3 == 0x100 && (iVar1 = *(int *)(*(int *)(iVar1 + 0x4140) + 4), iVar1 != 0)))))) {
    return *(undefined4 *)(iVar1 + 0x21246c);
  }
  if (DebugLevel < 2) {
    return 0;
  }
  printk("%s(): Avoid calling this function when wdev type is not client!\n","GetAssociatedAPByWdev"
         ,param_3,DebugLevel,param_4);
  return 0;
}


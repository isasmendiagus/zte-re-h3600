// module: mt7915.ko
// function: wdev_search_by_idx @ 0x14e120
// size: 64 bytes
//

int wdev_search_by_idx(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + param_2 * 4 + 0xc);
  if ((iVar1 == 0) && (-1 < DebugLevel)) {
    printk("error: wdev(wdev_idx = %d) is null from idx\n");
  }
  return iVar1;
}


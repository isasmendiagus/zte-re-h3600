// module: mt7915.ko
// function: wdev_search_by_pkt @ 0x14e0dc
// size: 68 bytes
//

int wdev_search_by_pkt(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + *(char *)(param_2 + 0x2d) * 4 + 0xc);
  if ((iVar1 == 0) && (-1 < DebugLevel)) {
    printk("error: wdev(wdev_idx = %d) is null from pkt\n");
  }
  return iVar1;
}


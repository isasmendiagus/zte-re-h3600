// module: mt7915.ko
// function: sta_cntl_error_handle @ 0x70768
// size: 88 bytes
//

void sta_cntl_error_handle(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x92c);
  iVar2 = *(int *)(iVar1 + 8);
  if (iVar2 == 0) {
    printk(&_LC5,0x845);
    dump_stack();
  }
  iVar1 = GetStaCfgByWdev(iVar2,iVar1);
  if (iVar1 != 0) {
    return;
  }
  printk(&_LC1,0x846);
  dump_stack();
  return;
}


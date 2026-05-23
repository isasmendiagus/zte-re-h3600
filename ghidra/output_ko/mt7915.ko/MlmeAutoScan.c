// module: mt7915.ko
// function: MlmeAutoScan @ 0x129c0c
// size: 132 bytes
//

void MlmeAutoScan(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 auStack_39 [41];
  
  iVar1 = GetStaCfgByWdev();
  if (iVar1 != 0) {
    os_zero_mem(auStack_39,0x29);
    ScanParmFill(param_1,auStack_39,iVar1 + 0x4140,*(undefined1 *)(iVar1 + 0x4160),2,0);
    cntl_scan_request(param_2,auStack_39);
    return;
  }
  printk(&_LC14,0xad4);
  dump_stack();
  return;
}


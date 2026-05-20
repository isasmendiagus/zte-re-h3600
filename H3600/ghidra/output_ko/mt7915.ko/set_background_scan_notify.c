// module: mt7915.ko
// function: set_background_scan_notify @ 0xea818
// size: 236 bytes
//

undefined4 set_background_scan_notify(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined2 local_12;
  
  os_zero_mem(&local_12,2);
  iVar2 = rstrtok(param_2,&_LC232);
  if (iVar2 != 0) {
    iVar3 = 0;
    do {
      if (iVar3 == 0) {
        uVar1 = os_str_tol(iVar2,0,10);
        local_12 = CONCAT11(local_12._1_1_,uVar1);
        iVar2 = rstrtok(0,&_LC232);
        if (iVar2 == 0) break;
LAB_000ea85c:
        uVar1 = os_str_tol(iVar2,0,10);
        iVar3 = 1;
        local_12 = CONCAT11(uVar1,(undefined1)local_12);
      }
      else if (iVar3 == 1) goto LAB_000ea85c;
      iVar3 = iVar3 + 1;
      iVar2 = rstrtok(0,&_LC232);
    } while (iVar2 != 0);
  }
  if (2 < DebugLevel) {
    printk("%s  NotifyFunc=%d, BgndScanStatus=%d\n","set_background_scan_notify",
           (undefined1)local_12,local_12._1_1_);
  }
  MtCmdBgndScanNotify(param_1,local_12);
  return 1;
}


// module: mt7915.ko
// function: set_background_scan_test @ 0xea61c
// size: 476 bytes
//

undefined4 set_background_scan_test(undefined4 param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  undefined4 local_17;
  undefined1 local_13 [2];
  undefined1 local_11;
  
  os_zero_mem(&local_17,7);
  iVar2 = rstrtok(param_2,&_LC232);
  if (iVar2 != 0) {
    iVar3 = 0;
    do {
      switch(iVar3) {
      case 0:
        uVar1 = os_str_tol(iVar2,0,10);
        local_17 = CONCAT31(local_17._1_3_,uVar1);
        iVar2 = rstrtok(0,&_LC232);
        if (iVar2 == 0) goto LAB_000ea79c;
        break;
      case 1:
        break;
      case 2:
        goto switchD_000ea658_caseD_2;
      case 3:
        goto switchD_000ea658_caseD_3;
      case 4:
        goto switchD_000ea658_caseD_4;
      case 5:
        goto switchD_000ea658_caseD_5;
      case 6:
        goto switchD_000ea658_caseD_6;
      default:
        goto switchD_000ea658_default;
      }
      uVar1 = os_str_tol(iVar2,0,10);
      local_17._0_2_ = CONCAT11(uVar1,(undefined1)local_17);
      iVar2 = rstrtok(0,&_LC232);
      if (iVar2 == 0) break;
switchD_000ea658_caseD_2:
      uVar1 = os_str_tol(iVar2,0,10);
      local_17._0_3_ = CONCAT12(uVar1,(undefined2)local_17);
      iVar2 = rstrtok(0,&_LC232);
      if (iVar2 == 0) break;
switchD_000ea658_caseD_3:
      uVar1 = os_str_tol(iVar2,0,10);
      local_17 = CONCAT13(uVar1,(undefined3)local_17);
      iVar2 = rstrtok(0,&_LC232);
      if (iVar2 == 0) break;
switchD_000ea658_caseD_4:
      uVar1 = os_str_tol(iVar2,0,0x10);
      _local_13 = CONCAT21(stack0xffffffee,uVar1);
      iVar2 = rstrtok(0,&_LC232);
      if (iVar2 == 0) break;
switchD_000ea658_caseD_5:
      uVar1 = os_str_tol(iVar2,0,10);
      local_13 = (undefined1  [2])CONCAT11(uVar1,local_13[0]);
      iVar2 = rstrtok(0,&_LC232);
      if (iVar2 == 0) break;
switchD_000ea658_caseD_6:
      uVar1 = os_str_tol(iVar2,0,10);
      iVar3 = 6;
      _local_13 = CONCAT12(uVar1,local_13);
switchD_000ea658_default:
      iVar3 = iVar3 + 1;
      iVar2 = rstrtok(0,&_LC232);
    } while (iVar2 != 0);
  }
LAB_000ea79c:
  if (2 < DebugLevel) {
    printk("%s  Bandidx=%d, BW=%d, CtrlCh=%d, CenCh=%d, Reason=%d, RxPath=%d\n",
           "set_background_scan_test",local_11,local_17._2_1_,local_17 & 0xff,local_17 >> 8 & 0xff,
           local_13[1],local_13[0]);
  }
  BackgroundScanTest(param_1,local_17,(uint)_local_13);
  return 1;
}


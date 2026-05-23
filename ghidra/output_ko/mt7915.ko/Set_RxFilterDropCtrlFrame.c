// module: mt7915.ko
// function: Set_RxFilterDropCtrlFrame @ 0xe6550
// size: 464 bytes
//

undefined4 Set_RxFilterDropCtrlFrame(int *param_1,undefined4 param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  uint uVar5;
  short local_1e [5];
  
  uVar5 = 0;
  local_1e[0] = 0;
  local_1e[1] = 0;
  local_1e[2] = 0;
  iVar2 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  iVar3 = rstrtok(param_2,&_LC547);
  if (iVar3 != 0) {
    do {
      sVar1 = os_str_toul(iVar3,0,10);
      local_1e[uVar5] = sVar1;
      iVar3 = rstrtok(0,&_LC547);
      uVar5 = uVar5 + 1 & 0xff;
    } while (iVar3 != 0);
    if (uVar5 == 3) {
      if (iVar2 == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = HcGetBandByWdev(iVar2);
        if (1 < uVar5) goto LAB_000e65dc;
      }
      bVar4 = local_1e[0] == 1;
      if (local_1e[1] == 1) {
        bVar4 = bVar4 | 2;
      }
      if (local_1e[2] == 1) {
        bVar4 = bVar4 | 4;
      }
      iVar2 = CmdExtCmdCfgUpdate(param_1,4,uVar5,bVar4);
      if (iVar2 == 0) {
        return 1;
      }
    }
  }
LAB_000e65dc:
  if (((((0 < DebugLevel) && (printk("Wrong Cmd Format. Plz input:\n"), 0 < DebugLevel)) &&
       (printk("iwpriv ra0 set rx_filter_ctrl=[0]-[1]-[2]\n"), 0 < DebugLevel)) &&
      ((printk("  [0]=0: Don\'t Drop RTS CTRL Frame\n"), 0 < DebugLevel &&
       (printk("\t   1: Drop RTS CTRL Frame)\n"), 0 < DebugLevel)))) &&
     ((printk("  [1]=0: Don\'t Drop CTS CTRL Frame\n"), 0 < DebugLevel &&
      ((printk("\t   1: Drop CTS CTRL Frame)\n"), 0 < DebugLevel &&
       (printk("  [2]=0: Don\'t Drop Unwanted CTRL Frame\n"), 0 < DebugLevel)))))) {
    printk("\t   1: Drop Unwanted CTRL Frame)\n");
  }
  return 0;
}


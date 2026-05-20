// module: mt7915.ko
// function: setApTmrEnableProc @ 0x3f00c
// size: 824 bytes
//

undefined4 setApTmrEnableProc(int *param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint local_24;
  
  uVar5 = *(uint *)(*param_1 + 0x3c);
  local_24 = 0;
  iVar1 = hc_get_chip_cap(param_1[0x29e5e8]);
  uVar2 = os_str_tol(param_2,0,10);
  iVar3 = hc_get_hif_type(param_1[0x29e5e8]);
  if (iVar3 == 2) {
    if (uVar2 < 3) {
      uVar5 = uVar5 & 0xff;
      if (param_1 + uVar5 * 0x160d + 0xadc92 != (int *)0x0) {
        uVar4 = wlan_operate_get_bw(param_1 + uVar5 * 0x160d + 0xadc92);
        if (uVar2 == 1) {
          if (0 < DebugLevel) {
            printk("%s: enable TMR report, as Initialiter\n","setApTmrEnableProc");
          }
          mac_io_read32(param_1[0x29e5e8],0x820f503c,&local_24);
          local_24 = local_24 & 0xbfffffff | 0x80000000;
          mac_io_write32(param_1[0x29e5e8],0x820f503c);
          *(undefined1 *)(iVar1 + 0x146) = 1;
          MtCmdTmrCal(param_1,1,0xe < *(byte *)((int)param_1 + uVar5 * 0x5834 + 0x2b7262),uVar4,0,1)
          ;
          return 1;
        }
        if (uVar2 == 2) {
          if (0 < DebugLevel) {
            printk("%s: enable TMR report, as Responser\n","setApTmrEnableProc");
          }
          mac_io_read32(param_1[0x29e5e8],0x820f503c,&local_24);
          local_24 = local_24 | 0xc0000034;
          mac_io_write32(param_1[0x29e5e8],0x820f503c);
          *(undefined1 *)(iVar1 + 0x146) = 2;
          MtCmdTmrCal(param_1,2,0xe < *(byte *)((int)param_1 + uVar5 * 0x5834 + 0x2b7262),uVar4,0,2)
          ;
          return 1;
        }
        if (0 < DebugLevel) {
          printk("%s: disable TMR report\n","setApTmrEnableProc");
        }
        mac_io_read32(param_1[0x29e5e8],0x820f503c,&local_24);
        local_24 = local_24 & 0x7fffffff;
        mac_io_write32(param_1[0x29e5e8],0x820f503c);
        *(undefined1 *)(iVar1 + 0x146) = 0;
        MtCmdTmrCal(param_1,uVar2 & 0xff,0xe < *(byte *)((int)param_1 + uVar5 * 0x5834 + 0x2b7262),
                    uVar4,0,0);
        return 1;
      }
      printk(&_LC379,0x4ec3);
      dump_stack();
      if (-1 < DebugLevel) {
        printk("%s: pMbss == NULL!!\n","setApTmrEnableProc");
        return 0;
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s: enable is incorrect!!\n","setApTmrEnableProc");
      return 0;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: chip_cap is not HIF_MT\n","setApTmrEnableProc");
    return 0;
  }
  return 0;
}


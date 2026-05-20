// module: mt7915.ko
// function: ZTE_Monitor_parm_show @ 0x159314
// size: 340 bytes
//

undefined4
ZTE_Monitor_parm_show(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  undefined4 *puVar2;
  undefined2 *puVar3;
  int iVar4;
  
  if (param_1 == 0) {
    return 0xffffffff;
  }
  puVar3 = (undefined2 *)(param_1 + 0xa37720);
  puVar2 = (undefined4 *)(param_1 + 0xa37718);
  puVar1 = (undefined1 *)(param_1 + 0xa376ad);
  iVar4 = 0;
  do {
    if (0 < DebugLevel) {
      printk("%s : band_idx=%d\n","ZTE_Monitor_parm_show",iVar4,DebugLevel,param_4);
      if (DebugLevel < 1) {
LAB_00159410:
        if (0 < DebugLevel) {
          printk("        ucMonitorApIdx=%d\n",*puVar1);
          if (0 < DebugLevel) {
            printk("        ScanType=%d\n",*puVar2);
LAB_00159448:
            if (0 < DebugLevel) {
              printk("        duration=%d\n",*puVar3);
            }
          }
        }
      }
      else {
        printk("        bAutoChannel=%d\n",puVar1[-8]);
        if (0 < DebugLevel) {
          printk("        ucLastChannel=%d\n",puVar1[-6]);
          if (DebugLevel < 1) goto LAB_00159448;
          printk("        ucMonitorChannel=%d\n",puVar1[-4]);
          if (0 < DebugLevel) {
            printk("        ucRestoreChannel=%d\n",puVar1[-2]);
            goto LAB_00159410;
          }
        }
      }
    }
    puVar3 = puVar3 + 1;
    puVar2 = puVar2 + 1;
    puVar1 = puVar1 + 1;
    if (iVar4 == 1) {
      return 1;
    }
    iVar4 = 1;
  } while( true );
}


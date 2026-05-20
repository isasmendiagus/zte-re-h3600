// module: mt7915.ko
// function: show_radar_threshold_param_proc @ 0x101db4
// size: 612 bytes
//

undefined4 show_radar_threshold_param_proc(int param_1)

{
  int iVar1;
  int iVar2;
  undefined1 *puVar3;
  
  if (-1 < DebugLevel) {
    printk("pAd->CommonCfg.RDDurRegion = %d",*(undefined1 *)(param_1 + 0x795075));
    if (0 < DebugLevel) {
      printk(
            "---------------------------------Debug Log Conditions---------------------------------------\n"
            );
      if (0 < DebugLevel) {
        printk("HWRDD_LOG_ENB = %d\nSWRDD_LOG_ENB = %d\nSWRDD_LOG_COND = %d\n",
               *(undefined1 *)(param_1 + 0x795436),*(undefined1 *)(param_1 + 0x795437),
               *(undefined1 *)(param_1 + 0x795438));
        if (0 < DebugLevel) {
          printk(
                "-------------------------------Pulse Threshold Parameters-----------------------------------\n"
                );
          if (0 < DebugLevel) {
            printk("FCC5_LPN = %d\n",*(undefined2 *)(param_1 + 0x795434));
            if (0 < DebugLevel) {
              printk("PLS_POWER_MIN = %d\n",*(undefined4 *)(param_1 + 0x795444));
              if (0 < DebugLevel) {
                printk("PLS_POWER_MAX = %d\n",*(undefined4 *)(param_1 + 0x795440));
                if (0 < DebugLevel) {
                  printk("SP_PW_MAX = %d\n",*(undefined4 *)(param_1 + 0x79543c));
                  if (0 < DebugLevel) {
                    printk("PRI_MIN_STGR = %d\n",*(undefined4 *)(param_1 + 0x795448));
                    if (0 < DebugLevel) {
                      printk("PRI_MAX_STGR = %d\n",*(undefined4 *)(param_1 + 0x79544c));
                      if (0 < DebugLevel) {
                        printk("PRI_MIN_CR = %d\n",*(undefined4 *)(param_1 + 0x795450));
                        if (0 < DebugLevel) {
                          printk("PRI_MAX_CR = %d\n",*(undefined4 *)(param_1 + 0x795454));
                          if (0 < DebugLevel) {
                            printk(
                                  "---------------------------------RADAR Threshold Info---------------------------------------\n"
                                  );
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  iVar2 = 0;
  puVar3 = (undefined1 *)(param_1 + 0x795469);
  iVar1 = DebugLevel;
  do {
    if (0 < iVar1) {
      printk("RT - %d: ENB = %d, STGR = %d, CRPN_MIN = %d, CRPN_MAX = %d, CRPR_MIN = %d, PW_MIN = %d, PW_MAX = %d,PRI_MIN = %d, PRI_MAX = %d, CRBN_MIN = %d, CRBN_MAX = %d\n\tSTGPN_MIN = %d, STGPN_MAX = %d, STGPR_MIN = %d, RT_STGPRID_MIN = %d\n"
             ,iVar2,*puVar3,puVar3[1],puVar3[2],puVar3[3],puVar3[4],puVar3[5],puVar3[6],
             *(undefined4 *)(puVar3 + 7),*(undefined4 *)(puVar3 + 0xb),puVar3[0xf],puVar3[0x10],
             puVar3[0x11],puVar3[0x12],puVar3[0x13],*(undefined4 *)(puVar3 + 0x17));
      iVar1 = DebugLevel;
    }
    iVar2 = iVar2 + 1;
    puVar3 = puVar3 + 0x1c;
  } while (iVar2 != 0x10);
  if (0 < iVar1) {
    printk(
          "---------------------------------------------------------------------------------------------\n"
          );
  }
  return 1;
}


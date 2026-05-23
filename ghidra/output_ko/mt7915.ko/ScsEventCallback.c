// module: mt7915.ko
// function: ScsEventCallback @ 0xb7894
// size: 840 bytes
//

void ScsEventCallback(undefined4 param_1,int *param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  
  iVar1 = *param_2;
  if (DebugLevel < 0) {
    if (iVar1 != 4) {
      return;
    }
  }
  else {
    printk("%s: u4EventId = %u, len = %u\n","ScsEventCallback",iVar1,param_3);
    if (iVar1 != 4) {
      return;
    }
    if (-1 < DebugLevel) {
      printk("%s: SCS_SHOW_INFO\n","ScsEventCallback");
      if (param_2 == (int *)0x0) {
        if (-1 < DebugLevel) {
          printk("%s: error !! rsp_payload is null!!\n","scs_show_info_callback");
          return;
        }
        return;
      }
      goto LAB_000b78c8;
    }
  }
  if (param_2 == (int *)0x0) {
    return;
  }
LAB_000b78c8:
  iVar1 = 0;
  piVar2 = param_2;
  piVar3 = param_2;
  do {
    if (0 < DebugLevel) {
      printk("************** Bnad%d  Information*************\n",iVar1);
      if (DebugLevel < 1) {
LAB_000b7990:
        if (DebugLevel < 1) {
LAB_000b7a00:
          if (DebugLevel < 1) {
LAB_000b7a70:
            if (DebugLevel < 1) {
LAB_000b7ae0:
              if (DebugLevel < 1) {
LAB_000b7b50:
                if (0 < DebugLevel) {
                  printk("OfdmPdSupport =%u\n",(char)piVar2[0x1b]);
                }
              }
              else {
                printk("CckPdBlkTh =%u\n",(char)piVar2[0x19]);
                if (0 < DebugLevel) {
                  printk("SCSThTolerance =%u\n",*(undefined1 *)((int)piVar2 + 0x66));
LAB_000b7b18:
                  if ((0 < DebugLevel) &&
                     (printk("SCSMinRssiTolerance =%u\n",(char)piVar2[0x1a]), 0 < DebugLevel)) {
                    printk("SCSEnable =%u\n",*(undefined1 *)((int)piVar2 + 0x6a));
                    goto LAB_000b7b50;
                  }
                }
              }
            }
            else {
              printk("OfdmFixedRssiBound =%u\n",(short)piVar3[0x16]);
              if (0 < DebugLevel) {
                printk("OfdmPdBlkTh =%u\n",(short)piVar3[0x17]);
LAB_000b7aa8:
                if (DebugLevel < 1) goto LAB_000b7b18;
                printk("SCSMinRssi =%d\n",(int)(char)piVar2[0x18]);
                if (0 < DebugLevel) {
                  printk("SCSStatus =%u\n",*(undefined1 *)((int)piVar2 + 0x62));
                  goto LAB_000b7ae0;
                }
              }
            }
          }
          else {
            printk("RtsRtyCount =%u\n",param_2[0x11]);
            if (0 < DebugLevel) {
              printk("OfdmFalseCcaUpBound =%u\n",(short)piVar3[0x13]);
LAB_000b7a38:
              if (DebugLevel < 1) goto LAB_000b7aa8;
              printk("OfdmFalseCcaLowBound =%u\n",(short)piVar3[0x14]);
              if (0 < DebugLevel) {
                printk("CckFixedRssiBound =%u\n",(short)piVar3[0x15]);
                goto LAB_000b7a70;
              }
            }
          }
        }
        else {
          printk("OFDMFalseCcaCount =%d\n",param_2[9]);
          if (0 < DebugLevel) {
            printk("OneSecTxByteCount =%u\n",param_2[0xb]);
LAB_000b79c8:
            if (DebugLevel < 1) goto LAB_000b7a38;
            printk("OneSecRxByteCount =%u\n",param_2[0xd]);
            if (0 < DebugLevel) {
              printk("RtsCount =%u\n",param_2[0xf]);
              goto LAB_000b7a00;
            }
          }
        }
      }
      else {
        printk("SCSTrafficThreshold =%u\n",param_2[1]);
        if (0 < DebugLevel) {
          printk("CckFalseCcaUpBound =%d\n",param_2[3]);
          if (DebugLevel < 1) goto LAB_000b79c8;
          printk("CckFalseCcaLowBound =%d\n",param_2[5]);
          if (0 < DebugLevel) {
            printk("CckFalseCcaCount =%d\n",param_2[7]);
            goto LAB_000b7990;
          }
        }
      }
    }
    piVar2 = (int *)((int)piVar2 + 1);
    piVar3 = (int *)((int)piVar3 + 2);
    param_2 = param_2 + 1;
    if (iVar1 == 1) {
      return;
    }
    iVar1 = 1;
  } while( true );
}


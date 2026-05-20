// module: mt7915.ko
// function: Show_SCSinfo_proc @ 0xed10c
// size: 1064 bytes
//

undefined4 Show_SCSinfo_proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  undefined2 *puVar5;
  char *pcVar6;
  
  iVar1 = HcGetAmountOfBand();
  uVar2 = *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff;
  if ((uVar2 == 0x7663 ||
       (uVar2 == 0x7615 || (*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xfffb) == 0x7622)
      ) && (iVar1 != 0)) {
    piVar4 = (int *)(param_1 + 0xa7c2c8);
    puVar5 = (undefined2 *)(param_1 + 0xa7c2bc);
    pcVar6 = (char *)(param_1 + 0xa7c245);
    iVar3 = 0;
    do {
      if (DebugLevel < 1) {
LAB_000ed1b4:
        if (iVar3 != 0 || *(char *)(param_1 + 0xa7c240) != '\x02') {
LAB_000ed1c4:
          if ((((0 < DebugLevel) && (printk("=========CCK=============\n"), 0 < DebugLevel)) &&
              ((printk(" Bnad%d CCK false-CCA= %d\n",iVar3,piVar4[-10]), 0 < DebugLevel &&
               ((printk(" Bnad%d CCK false-CCA up bond= %d\n",iVar3,puVar5[-6]), 0 < DebugLevel &&
                (printk(" Bnad%d CCK false-CCA low bond= %d\n",iVar3,puVar5[-4]), 0 < DebugLevel))))
              )) && ((printk(" Bnad%d CCK fixed RSSI boundary= %d (%ddBm)\n",iVar3,piVar4[-2],
                             piVar4[-2] + -0x100), 0 < DebugLevel &&
                     ((((printk("=========OFDM=============\n"), 0 < DebugLevel &&
                        (printk(" Bnad%d OFDM false-CCA= %d\n",iVar3,piVar4[-8]), 0 < DebugLevel))
                       && (printk(" Bnad%d OFDM false-CCA up bond= %d\n",iVar3,puVar5[-2]),
                          0 < DebugLevel)) &&
                      (printk(" Bnad%d OFDM false-CCA low bond= %d\n",iVar3,*puVar5), 0 < DebugLevel
                      )))))) {
            printk(" Bnad%d OFDM fixed RSSI boundary= %d(%ddBm)\n",iVar3,*piVar4,
                   (*piVar4 + -0x200) / 2);
          }
        }
      }
      else {
        printk("************** Bnad%d  Information*************\n",iVar3);
        if (0 < DebugLevel) {
          printk(" Bnad%d SCSEnable = %d\n",iVar3,pcVar6[-4],DebugLevel,param_4);
          if (0 < DebugLevel) {
            printk(" Bnad%d SCSStatus = %d\n",iVar3,pcVar6[-2],DebugLevel,param_4);
            if (DebugLevel < 1) goto LAB_000ed2d0;
            printk(" Bnad%d SCSMinRssi = %d\n",iVar3,(int)*pcVar6);
            if (0 < DebugLevel) {
              printk(" Bnad%d CckPdBlkTh = %d (%ddBm)\n",iVar3,piVar4[-0x1a],piVar4[-0x1a] + -0x100)
              ;
              goto LAB_000ed284;
            }
          }
          goto LAB_000ed1b4;
        }
LAB_000ed284:
        if (0 < DebugLevel) {
          printk(" Bnad%d OfdmPdBlkTh = %d(%ddBm)\n",iVar3,piVar4[-0x18],
                 (piVar4[-0x18] + -0x200) / 2,param_4);
          if (0 < DebugLevel) {
            printk(" Bnad%d Traffic TH = %d\n",iVar3,piVar4[-0x20]);
LAB_000ed2d0:
            if (DebugLevel < 1) goto LAB_000ed350;
            printk(" Bnad%d MinRssiTolerance = %d\n",iVar3,piVar4[-0x16]);
            if (0 < DebugLevel) {
              printk(" Bnad%d SCSThTolerance = %d\n",iVar3,piVar4[-0x14]);
              goto LAB_000ed310;
            }
          }
          goto LAB_000ed1b4;
        }
LAB_000ed310:
        if (0 < DebugLevel) {
          printk(" Bnad%d One sec TxByte = %d\n",iVar3,piVar4[-0x1e]);
          if (0 < DebugLevel) {
            printk(" Bnad%d One sec RxByte = %d\n",iVar3,piVar4[-0x1c]);
LAB_000ed350:
            if ((0 < DebugLevel) &&
               (printk(" Bnad%d RTS count = %d\n",iVar3,piVar4[-0x11]), 0 < DebugLevel)) {
              printk(" Bnad%d RTS retry count = %d\n",iVar3,piVar4[-0xf]);
              goto LAB_000ed394;
            }
          }
          goto LAB_000ed1b4;
        }
LAB_000ed394:
        if (iVar3 != 0 || *(char *)(param_1 + 0xa7c240) != '\x02') goto LAB_000ed1c4;
        if (((0 < DebugLevel) &&
            (printk(" Bnad0 RTS   MPDU drop count = %d\n",*(undefined4 *)(param_1 + 0xa7c294)),
            0 < DebugLevel)) &&
           (printk(" Bnad0 Retry MPDU drop count = %d\n",*(undefined4 *)(param_1 + 0xa7c298)),
           0 < DebugLevel)) {
          printk(" Bnad0 LTO   MPDU drop count = %d\n",*(undefined4 *)(param_1 + 0xa7c29c));
          goto LAB_000ed1c4;
        }
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
      puVar5 = puVar5 + 1;
      pcVar6 = pcVar6 + 1;
    } while (iVar3 != iVar1);
  }
  return 1;
}


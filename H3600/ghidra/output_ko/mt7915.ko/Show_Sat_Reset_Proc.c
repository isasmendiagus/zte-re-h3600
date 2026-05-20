// module: mt7915.ko
// function: Show_Sat_Reset_Proc @ 0x2f470
// size: 1784 bytes
//

undefined4 Show_Sat_Reset_Proc(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int *piVar7;
  int *piVar8;
  int iVar9;
  int *piVar10;
  int iVar11;
  int *piVar12;
  bool bVar13;
  int local_38;
  
  iVar1 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  iVar2 = 0;
  if (iVar1 != 0) {
    iVar2 = HcGetBandByWdev();
  }
  if (DebugLevel < 3) {
    iVar1 = iVar2 << 5;
  }
  else {
    iVar1 = iVar2 * 0x20;
    uVar4 = param_1[iVar2 * 0x42 + 0x28e700];
    printk("TransmittedFragmentCount = %lld\n",uVar4,param_1[iVar2 * 0x42 + 0x28e702] + uVar4,
           param_1[iVar2 * 0x42 + 0x28e703] + (uint)CARRY4(param_1[iVar2 * 0x42 + 0x28e702],uVar4));
    if ((((((2 < DebugLevel) &&
           (printk("MulticastTransmittedFrameCount = %d\n",param_1[iVar2 * 0x42 + 0x28e702]),
           2 < DebugLevel)) &&
          (printk("FailedCount = %d\n",param_1[iVar2 * 0x42 + 0x28e704]), 2 < DebugLevel)) &&
         ((printk("RetryCount = %d\n",param_1[iVar2 * 0x42 + 0x28e706]), 2 < DebugLevel &&
          (printk("MultipleRetryCount = %d\n",param_1[iVar2 * 0x42 + 0x28e708]), 2 < DebugLevel))))
        && ((printk("RTSSuccessCount = %d\n",param_1[iVar2 * 0x42 + 0x28e70a]), 2 < DebugLevel &&
            ((printk("RTSFailureCount = %d\n",param_1[iVar2 * 0x42 + 0x28e70c]), 2 < DebugLevel &&
             (printk("ACKFailureCount = %d\n",param_1[iVar2 * 0x42 + 0x28e70e]), 2 < DebugLevel)))))
        ) && (printk("FrameDuplicateCount = %d\n",param_1[iVar2 * 0x42 + 0x28e710]), 2 < DebugLevel)
       ) {
      printk("ReceivedFragmentCount = %d\n",param_1[iVar2 * 0x42 + 0x28e712]);
      if ((((2 < DebugLevel) &&
           (printk("MulticastReceivedFrameCount = %d\n",param_1[iVar2 * 0x42 + 0x28e714]),
           2 < DebugLevel)) &&
          (printk("Rx drop due to out of resource  = %u\n",param_1[0x28e6fd]), 2 < DebugLevel)) &&
         ((printk("RealFcsErrCount = %d\n",param_1[0x28e79c]), 2 < DebugLevel &&
          (printk("TransmittedFrameCount = %d\n",param_1[iVar2 * 0x42 + 0x28e718]), 2 < DebugLevel))
         )) {
        printk("WEPUndecryptableCount = %d\n",param_1[iVar2 * 0x42 + 0x28e71a]);
      }
    }
  }
  iVar1 = iVar1 + iVar2;
  param_1[iVar1 * 2 + 0x28e700] = 0;
  param_1[iVar1 * 2 + 0x28e702] = 0;
  param_1[iVar1 * 2 + 0x28e704] = 0;
  param_1[iVar1 * 2 + 0x28e706] = 0;
  param_1[iVar1 * 2 + 0x28e708] = 0;
  param_1[iVar1 * 2 + 0x28e70a] = 0;
  param_1[iVar1 * 2 + 0x28e70c] = 0;
  param_1[iVar1 * 2 + 0x28e70e] = 0;
  param_1[iVar1 * 2 + 0x28e712] = 0;
  param_1[iVar1 * 2 + 0x28e714] = 0;
  param_1[0x28e6fd] = 0;
  param_1[0x28e79c] = 0;
  param_1[iVar1 * 2 + 0x28e716] = 0;
  param_1[iVar1 * 2 + 0x28e710] = 0;
  param_1[iVar1 * 2 + 0x28e717] = 0;
  param_1[iVar1 * 2 + 0x28e711] = 0;
  param_1[iVar1 * 2 + 0x28e718] = 0;
  param_1[iVar1 * 2 + 0x28e71a] = 0;
  param_1[iVar1 * 2 + 0x28e728] = 0;
  param_1[iVar1 * 2 + 0x28e726] = 0;
  param_1[iVar1 * 2 + 0x28e729] = 0;
  param_1[iVar1 * 2 + 0x28e727] = 0;
  param_1[iVar1 * 2 + 0x28e72e] = 0;
  param_1[iVar1 * 2 + 0x28e72f] = 0;
  param_1[iVar1 * 2 + 0x28e730] = 0;
  param_1[iVar1 * 2 + 0x28e731] = 0;
  param_1[iVar1 * 2 + 0x28e732] = 0;
  param_1[iVar1 * 2 + 0x28e733] = 0;
  param_1[iVar1 * 2 + 0x28e734] = 0;
  param_1[iVar1 * 2 + 0x28e735] = 0;
  param_1[iVar1 * 2 + 0x28e736] = 0;
  param_1[iVar1 * 2 + 0x28e737] = 0;
  param_1[iVar1 * 2 + 0x28e738] = 0;
  param_1[iVar1 * 2 + 0x28e739] = 0;
  param_1[iVar1 * 2 + 0x28e73a] = 0;
  param_1[iVar1 * 2 + 0x28e73b] = 0;
  param_1[iVar1 * 2 + 0x28e73c] = 0;
  param_1[iVar1 * 2 + 0x28e73d] = 0;
  param_1[iVar1 * 2 + 0x28e73e] = 0;
  param_1[iVar1 * 2 + 0x28e73f] = 0;
  param_1[iVar1 * 2 + 0x28e72a] = 0;
  piVar10 = param_1 + 0x28748;
  iVar2 = 0;
  param_1[iVar1 * 2 + 0x28e72c] = 0;
  param_1[iVar1 * 2 + 0x28e71e] = 0;
  local_38 = 0;
  param_1[iVar1 * 2 + 0x28e720] = 0;
  param_1[iVar1 * 2 + 0x28e722] = 0;
  param_1[iVar1 * 2 + 0x28e724] = 0;
  do {
    iVar1 = HcGetMaxStaNum(param_1);
    if (iVar1 <= local_38) {
      DisplayTxAgg(param_1);
      return 1;
    }
    if ((*piVar10 == 0x20001) && (piVar10[0x3f] == 2)) {
      if ((2 < DebugLevel) &&
         (printk("\n%02x:%02x:%02x:%02x:%02x:%02x - ",(char)piVar10[0x3b],
                 *(undefined1 *)((int)piVar10 + 0xed),*(undefined1 *)((int)piVar10 + 0xee),
                 *(undefined1 *)((int)piVar10 + 0xef),(char)piVar10[0x3c],
                 *(undefined1 *)((int)piVar10 + 0xf1)), 2 < DebugLevel)) {
        printk("%-4d\n",(short)piVar10[0x3e]);
      }
      piVar7 = piVar10 + 0x47a;
      iVar1 = 0xf;
      piVar8 = piVar10 + 0x35a;
      do {
        piVar12 = piVar8 + -1;
        iVar9 = *piVar12;
        if (iVar9 == 0) {
          iVar5 = piVar8[0x1f];
          if (iVar5 != 0) {
            if (2 < DebugLevel) {
              iVar11 = piVar8[0xf];
              uVar3 = 0;
              goto LAB_0002f864;
            }
            goto LAB_0002f7e8;
          }
        }
        else {
          if (2 < DebugLevel) {
            iVar11 = piVar8[0xf];
            uVar3 = __aeabi_uidiv(iVar11 * 100,iVar9);
            iVar5 = piVar8[0x1f];
LAB_0002f864:
            printk("MCS[%02d]: Expected %u, Successful %u (%d%%), Failed %u\n",iVar1,iVar9,iVar11,
                   uVar3,iVar5);
          }
LAB_0002f7e8:
          iVar9 = 0xf;
          piVar8 = piVar7;
          do {
            piVar8 = piVar8 + -1;
            iVar5 = *piVar8;
            if ((iVar5 != 0) && (2 < DebugLevel)) {
              uVar3 = __aeabi_uidiv(iVar5 * 100,*piVar12);
              printk("\t\t\tAutoMCS[%02d]: %u (%d%%)\n",iVar9,iVar5,uVar3);
            }
            bVar13 = iVar9 != 0;
            iVar9 = iVar9 + -1;
          } while (bVar13);
        }
        iVar1 = iVar1 + -1;
        piVar7 = piVar7 + -0x10;
        piVar8 = piVar12;
      } while (iVar1 != -1);
    }
    iVar1 = 0;
    piVar8 = piVar10 + 0x349;
    piVar12 = piVar10 + 0x359;
    piVar7 = piVar10 + 0x369;
    do {
      puVar6 = (undefined4 *)((int)param_1 + iVar2 + 0xa2b48 + iVar1);
      piVar8 = piVar8 + 1;
      *piVar8 = 0;
      piVar12 = piVar12 + 1;
      *piVar12 = 0;
      piVar7 = piVar7 + 1;
      *piVar7 = 0;
      do {
        puVar6 = puVar6 + -1;
        *puVar6 = 0;
      } while (puVar6 != (undefined4 *)((int)param_1 + iVar2 + 0xa2b08 + iVar1));
      iVar1 = iVar1 + 0x40;
    } while (iVar1 != 0x400);
    iVar2 = iVar2 + 0x14c0;
    piVar10 = piVar10 + 0x530;
    local_38 = local_38 + 1;
  } while( true );
}


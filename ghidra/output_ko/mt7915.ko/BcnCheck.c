// module: mt7915.ko
// function: BcnCheck @ 0xb5d68
// size: 900 bytes
//

void BcnCheck(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint *puVar6;
  uint uVar7;
  uint uVar8;
  int *piVar9;
  
  if (*(uint *)(param_1 + 0x829214) % 0x19 == 0) {
    uVar7 = 0;
    while( true ) {
      uVar8 = uVar7 & 0xff;
      uVar1 = HcGetAmountOfBand(param_1);
      if ((((((uVar1 <= uVar8) || ((*(uint *)(param_1 + 0xa39f84) & 0x4044) != 4)) ||
            (iVar2 = IsErrRecoveryInIdleStat(param_1), iVar2 == 0)) ||
           ((*(char *)(param_1 + 0x795941) != '\0' || ((*(uint *)(param_1 + 0xa3ac14) & 1) != 0))))
          || ((*(int *)(param_1 + 0xa77bb4) == 1 &&
              ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)))) ||
         (*(char *)(param_1 + (uVar8 + 0x51bb9) * 0x20 + 8) == '\x02')) break;
      piVar9 = (int *)(param_1 + 8);
      while( true ) {
        piVar9 = piVar9 + 1;
        iVar2 = *piVar9;
        if (((iVar2 != 0) && (iVar3 = HcIsRadioAcq(iVar2), iVar3 != 0)) &&
           ((iVar3 = IsHcRadioCurStatOffByWdev(iVar2), iVar3 == 0 &&
            (((uVar1 = HcGetBandByWdev(iVar2), uVar8 == uVar1 && (*(int *)(iVar2 + 0x990) == 3)) &&
             (*(char *)(iVar2 + 0x950) != '\0')))))) break;
        if (piVar9 == (int *)(param_1 + 0x1a8)) {
          return;
        }
      }
      iVar2 = asic_get_bcn_tx_cnt(param_1,uVar8);
      *(int *)(&DAT_0036db38 + param_1 + uVar8 * 0xc) =
           iVar2 + *(int *)(&DAT_0036db38 + param_1 + uVar8 * 0xc);
      if ((iVar2 != 0) && (*(char *)(param_1 + 0xa7d167) != '\0')) {
        WLAN_BeaconLostNumClear(param_1,uVar8,iVar2);
      }
      if (*(uint *)(param_1 + 0x829214) % 0x32 == 0) {
        iVar3 = param_1 + uVar8 * 0xc;
        puVar6 = (uint *)(&DAT_0036db30 + iVar3);
        iVar4 = *(int *)(&DAT_0036db34 + iVar3);
        *(undefined4 *)(&DAT_0036db34 + iVar3) = 0;
        if (iVar2 + iVar4 == 0) {
          uVar1 = *puVar6 + 1;
          *puVar6 = uVar1;
          if (uVar1 < 5) {
            if ((uVar1 != 0) && (0 < DebugLevel)) {
              uVar5 = RtmpOsGetNetDevName(*(undefined4 *)(param_1 + 4));
              printk("%s: nobcn occurs within %d sec for band %d (%s)!!\n","BcnCheck",uVar1 * 5,
                     uVar8,uVar5);
            }
          }
          else {
            if ((uVar1 == (uVar1 / 6) * 6) && (-1 < DebugLevel)) {
              uVar5 = RtmpOsGetNetDevName(*(undefined4 *)(param_1 + 4));
              printk("%s: nobcn still occur within %d sec for band %d (%s)!!\n","BcnCheck",uVar1 * 5
                     ,uVar8,uVar5);
            }
            if (*(char *)(param_1 + 0xa7d167) != '\0') {
              WLAN_BeaconLostReset(param_1,uVar8);
            }
            if (*(int *)(&DAT_0036db30 + param_1 + uVar8 * 0xc) == 5) {
              MtCmdFwLog2Host(param_1,0,0);
            }
          }
        }
        else if ((*puVar6 != 0) && (*puVar6 = 0, 0 < DebugLevel)) {
          uVar5 = RtmpOsGetNetDevName(*(undefined4 *)(param_1 + 4));
          printk("%s: bcn recover for band %d (%s)!!\n","BcnCheck",uVar8,uVar5);
        }
      }
      else {
        *(int *)(&DAT_0036db34 + param_1 + uVar8 * 0xc) = iVar2;
      }
      uVar7 = uVar7 + 1;
    }
  }
  return;
}


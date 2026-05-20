// module: mt7915.ko
// function: assoc_vht_info_debugshow @ 0xe9ba8
// size: 752 bytes
//

void assoc_vht_info_debugshow(undefined4 param_1,int param_2,byte *param_3,undefined1 *param_4)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if ((*(ushort *)(*(int *)(param_2 + 8) + 0x18) & 0x20) == 0) {
    return;
  }
  if (2 < DebugLevel) {
    printk("Peer - 11AC VHT Info\n");
  }
  if (param_3 == (byte *)0x0) {
LAB_000e9dbc:
    if (param_4 == (undefined1 *)0x0) goto LAB_000e9e54;
LAB_000e9dc4:
    if (DebugLevel < 3) {
      return;
    }
    printk("\tVHT OP Info:\n");
    if (DebugLevel < 3) {
      return;
    }
    printk("\t\tChannel Width(%d), CenteralFreq1(%d), CenteralFreq2(%d)\n",*param_4,param_4[1],
           param_4[2]);
  }
  else {
    hex_dump("peer vht_cap raw data",param_3,4);
    hex_dump("peer vht_mcs raw data",param_3 + 4,8);
    if (DebugLevel < 3) {
      return;
    }
    printk("\tVHT Cap Info:\n");
    if (DebugLevel < 3) {
LAB_000e9d84:
      if (2 < DebugLevel) {
        printk("\t\tETxBfCap: Bfer(%d), Bfee(%d), SndDim(%d)\n",((uint)param_3[1] << 0x1c) >> 0x1f,
               ((uint)param_3[1] << 0x1b) >> 0x1f,param_3[2] & 7);
        goto LAB_000e9dbc;
      }
    }
    else {
      uVar4 = (uint)*param_3;
      uVar3 = (uint)(*param_3 >> 7);
      uVar1 = param_3[1] & 7;
      uVar2 = ((uint)param_3[2] << 0x19) >> 0x1f;
      printk("\t\tMaxMpduLen(%d), BW(%d), SGI_80M(%d), RxLDPC(%d), TxSTBC(%d), RxSTBC(%d), +HTC-VHT(%d)\n"
             ,uVar4 & 3,(uVar4 << 0x1c) >> 0x1e,(uVar4 << 0x1a) >> 0x1f,(uVar4 << 0x1b) >> 0x1f,
             uVar3,uVar1,uVar2);
      if (DebugLevel < 3) {
        if (param_4 == (undefined1 *)0x0) {
          return;
        }
        goto LAB_000e9dc4;
      }
      uVar4 = (uint)param_3[3];
      printk("\t\tMaxAmpduExp(%d), VhtLinkAdapt(%d), RxAntConsist(%d), TxAntConsist(%d)\n",
             (uVar4 & 3) << 1 | (uint)(param_3[2] >> 7),(uVar4 << 0x1c) >> 0x1e,
             (uVar4 << 0x1b) >> 0x1f,(uVar4 << 0x1a) >> 0x1f,uVar3,uVar1,uVar2);
      if (2 < DebugLevel) {
        uVar1 = (uint)param_3[4];
        uVar3 = (uint)param_3[5];
        printk("\t\tRxMcsSet: HighRate(%d), RxMCSMap(%d,%d,%d,%d,%d,%d,%d)\n",
               (uint)param_3[6] | (param_3[7] & 0x1f) << 8,uVar1 & 3,(uVar1 << 0x1c) >> 0x1e,
               (uVar1 << 0x1a) >> 0x1e,param_3[4] >> 6,uVar3 & 3,(uVar3 << 0x1c) >> 0x1e,
               (uVar3 << 0x1a) >> 0x1e);
        if (DebugLevel < 3) {
          return;
        }
        uVar1 = (uint)param_3[8];
        uVar3 = (uint)param_3[9];
        printk("\t\tTxMcsSet: HighRate(%d), TxMcsMap(%d,%d,%d,%d,%d,%d,%d)\n",
               (uint)param_3[10] | (param_3[0xb] & 0x1f) << 8,uVar1 & 3,(uVar1 << 0x1c) >> 0x1e,
               (uVar1 << 0x1a) >> 0x1e,param_3[8] >> 6,uVar3 & 3,(uVar3 << 0x1c) >> 0x1e,
               (uVar3 << 0x1a) >> 0x1e);
        goto LAB_000e9d84;
      }
    }
    if (param_4 == (undefined1 *)0x0) {
      return;
    }
  }
  if (DebugLevel < 3) {
    return;
  }
  uVar3 = (uint)(byte)param_4[3];
  uVar1 = (uint)(byte)param_4[4];
  printk("\t\tBasicMCSSet(SS1:%d, SS2:%d, SS3:%d, SS4:%d, SS5:%d, SS6:%d, SS7:%d)\n",uVar3 & 3,
         (uVar3 << 0x1c) >> 0x1e,(uVar3 << 0x1a) >> 0x1e,(byte)param_4[3] >> 6,uVar1 & 3,
         (uVar1 << 0x1c) >> 0x1e,(uVar1 << 0x1a) >> 0x1e);
LAB_000e9e54:
  if (DebugLevel < 3) {
    return;
  }
  printk(&_LC22);
  return;
}


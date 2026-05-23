// module: mt7915.ko
// function: RcAcquiredBandForObj @ 0xac354
// size: 760 bytes
//

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int RcAcquiredBandForObj
              (int param_1,char *param_2,char param_3,uint param_4,char param_5,short param_6)

{
  char cVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  undefined1 *puVar5;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  ushort local_34;
  
  if (param_2[0x1c] == '\x01') {
    RcReleaseBandForObj();
  }
  uVar6 = param_4 & 0xff;
  cVar1 = *(char *)(param_1 + 0x32d8);
  if (cVar1 != '\x01') {
    if (cVar1 != '\0') {
      pcVar7 = (char *)(param_1 + 0x1360);
      iVar2 = param_1;
      iVar8 = 0;
      do {
        if (((((param_4 & 0x4e) == 0) || (iVar4 = iVar2, pcVar7[0x33c] != '\0')) &&
            (iVar4 = iVar8, (param_4 & 0xb1) != 0)) && (pcVar7[0x33c] == '\x01')) {
          iVar4 = iVar2;
        }
        if (iVar4 != 0) {
          if (param_5 == '\0') {
            if (*(char *)(iVar4 + 0x14) != '\0') {
              puVar5 = *(undefined1 **)(iVar4 + 4);
              if (puVar5[4] == '\0') goto LAB_000ac474;
              goto LAB_000ac3fc;
            }
          }
          else {
            puVar5 = *(undefined1 **)(iVar4 + 4);
            if (puVar5[4] == param_5) {
LAB_000ac474:
              if (*(ushort *)(puVar5 + 2) == uVar6) goto LAB_000ac490;
            }
LAB_000ac3fc:
            if ((param_4 & 0x4e) == 0) {
              if (((param_4 & 0xb1) == 0) || (*pcVar7 != '\x02')) goto LAB_000ac418;
              puVar5 = *(undefined1 **)(iVar4 + 4);
              goto LAB_000ac490;
            }
          }
          puVar5 = *(undefined1 **)(iVar4 + 4);
          goto LAB_000ac490;
        }
LAB_000ac418:
        pcVar7 = pcVar7 + 0x354;
        iVar2 = iVar2 + 0x1c;
        iVar8 = iVar4;
      } while (pcVar7 != (char *)((uint)(byte)(cVar1 - 1) * 0x354 + param_1 + 0x16b4));
      if (iVar4 != 0) {
        puVar5 = *(undefined1 **)(iVar4 + 4);
LAB_000ac490:
        bVar3 = false;
        goto LAB_000ac49c;
      }
    }
    if (-1 < DebugLevel) {
      printk("%s(): can\'t find radio for phymode:%u, channel: %d !\n","rcGetHdevByPhyMode",uVar6,
             param_5);
    }
  }
  iVar4 = param_1;
  if (param_1 == 0) {
    if ((param_4 & 0xb1) != 0) {
      printk("[%s] rdev received NULL in 5G mode\n","RcAcquiredBandForObj");
    }
    bVar3 = true;
    puVar5 = _DAT_00000004;
  }
  else {
    puVar5 = *(undefined1 **)(param_1 + 4);
    bVar3 = false;
  }
LAB_000ac49c:
  if (puVar5[1] == '\0') {
    puVar5[1] = 1;
  }
  local_34 = (ushort)param_4;
  if ((param_6 == 2) && (uVar6 != 0)) {
    *(ushort *)(puVar5 + 2) = local_34;
    if (*(char *)(param_1 + 0x32d9) == '\x01') {
      param_2[0x1e] = '\x01';
    }
  }
  else {
    if (!bVar3) {
      iVar2 = wmode_band_equal(*(undefined2 *)(puVar5 + 2),param_4);
      if (iVar2 != 0) {
        local_34 = local_34 | *(ushort *)(puVar5 + 2);
      }
      *(ushort *)(puVar5 + 2) = local_34;
    }
    if ((*(char *)(param_1 + 0x32d9) == '\x01') && (param_6 != 0x4000 && param_6 != 0x1000)) {
      param_2[0x1e] = '\x01';
    }
  }
  *(short *)(param_2 + 2) = param_6;
  *param_2 = param_3;
  cVar1 = GetOmacIdx(param_1,param_6,iVar4,(int)param_3);
  param_2[4] = cVar1;
  HdevObjAdd(iVar4,param_2);
  if (3 < DebugLevel) {
    printk("%s(): BandIdx:%d, PhyMode=%d,Channel=%d,OMACIDX=%d,pHdevObj=%p, tx_mode=%d\n",
           "RcAcquiredBandForObj",*puVar5,*(undefined2 *)(puVar5 + 2),puVar5[4],param_2[4],param_2,
           param_2[0x1e]);
  }
  RcUpdateBandCtrl(param_1);
  param_2[0x20] = '\0';
  param_2[0x21] = '\0';
  param_2[0x22] = '\0';
  param_2[0x23] = '\0';
  return iVar4;
}


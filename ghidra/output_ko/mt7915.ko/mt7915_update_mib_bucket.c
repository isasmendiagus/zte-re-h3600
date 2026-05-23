// module: mt7915.ko
// function: mt7915_update_mib_bucket @ 0x174390
// size: 408 bytes
//

void mt7915_update_mib_bucket(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  byte bVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int *piVar8;
  undefined4 local_88 [2];
  int local_80;
  undefined4 local_78;
  int local_70;
  undefined4 local_68;
  int local_60;
  undefined4 local_58;
  int local_50;
  undefined4 local_48;
  int local_40;
  undefined4 local_38;
  int local_30;
  
  uVar1 = HcGetAmountOfBand();
  bVar4 = *(char *)(param_1 + 0xa7c348) + 1;
  if (1 < bVar4) {
    bVar4 = 0;
  }
  *(byte *)(param_1 + 0xa7c348) = bVar4;
  if ((*(char *)(param_1 + 0xa7c349) == '\x01') &&
     (iVar3 = scan_in_run_state(param_1,0), iVar3 == 0)) {
    uVar5 = (uint)*(byte *)(param_1 + 0xa7c348);
  }
  else {
    uVar5 = 0;
  }
  if (uVar1 != 0) {
    uVar7 = 0;
    uVar2 = 0;
    piVar8 = (int *)(param_1 + (int)("cmd_txbf_en_dynsnd_intr" + uVar5 + 0x13) * 4);
    do {
      if (*(char *)(param_1 + 0xa7c349) == '\x01') {
        local_68 = 0x52;
        local_78 = 0x51;
        local_48 = 0xe;
        local_58 = 0x57;
        local_88[0] = 0x56;
        local_38 = 0xb;
        MtCmdMultipleMibRegAccessRead(param_1,uVar2,local_88,6);
        iVar3 = _prPrevMibCnt;
        iVar6 = _prPrevMibCnt + uVar7 * 4;
        *piVar8 = local_80 - *(int *)(_prPrevMibCnt + uVar7 * 4);
        piVar8[4] = local_70 - *(int *)(iVar6 + 8);
        piVar8[8] = local_60 - *(int *)(iVar6 + 0x10);
        piVar8[0xc] = local_50 - *(int *)(iVar6 + 0x18);
        piVar8[-4] = local_40 - *(int *)(iVar6 + 0x20);
        piVar8[-8] = local_30 - *(int *)(iVar6 + 0x28);
        *(int *)(iVar3 + uVar7 * 4) = local_80;
        iVar3 = _prPrevMibCnt + uVar7 * 4;
        *(int *)(iVar3 + 8) = local_70;
        *(int *)(iVar3 + 0x10) = local_60;
        *(int *)(iVar3 + 0x18) = local_50;
        *(int *)(iVar3 + 0x20) = local_40;
        *(int *)(iVar3 + 0x28) = local_30;
      }
      uVar7 = uVar7 + 1;
      piVar8 = piVar8 + 2;
      uVar2 = uVar7 & 0xff;
    } while (uVar2 < uVar1);
  }
  return;
}


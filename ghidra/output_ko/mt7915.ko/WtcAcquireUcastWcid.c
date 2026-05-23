// module: mt7915.ko
// function: WtcAcquireUcastWcid @ 0xadd30
// size: 528 bytes
//

uint WtcAcquireUcastWcid(int param_1,int param_2,uint param_3,undefined4 param_4)

{
  ushort uVar1;
  undefined2 uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  
  iVar8 = *(int *)(param_1 + 0x4328);
  uVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(iVar8 + 0xa797a0));
  iVar6 = param_1 + 0x1360;
  if (param_2 == 0 || (iVar6 == 0 || param_1 == -0x1a28)) {
LAB_000adecc:
    if (-1 < DebugLevel) {
      printk("%s: unexpected NULL please check!!\n","WtcAcquireUcastWcid",iVar6,DebugLevel,param_4);
      return 0xffff;
    }
  }
  else {
    iVar9 = param_1 + 0x2c30;
    _raw_spin_lock_bh(iVar9);
    if ((iVar8 != 0) && (*(ushort *)(iVar8 + 0xa7c23c) != 0)) {
      param_3 = (uint)*(ushort *)(iVar8 + 0xa7c23c);
    }
    if (param_3 < *(ushort *)(param_1 + 0x1a28)) {
      do {
        if (param_3 < uVar4) {
          if ((((*(uint *)("Get_RBIST_IQ_Data_Proc" + iVar8 + 0xc) & 0xffff) == 0x7915) &&
              ("Get_RBIST_IQ_Data_Proc"[iVar8 + 0x10] == '\0')) &&
             (*(char *)(iVar8 + 0x79504d) != '\0')) {
            uVar3 = param_3 >> 5 & 0x3fff;
            uVar7 = uVar3 * 4;
            uVar5 = uVar7 + 4;
            if (uVar7 < uVar5) {
              uVar1 = *(ushort *)(&DAT_00293c50 + uVar3 * 8);
              while (uVar1 != param_3) {
                uVar7 = uVar7 + 1 & 0xffff;
                if (uVar5 <= uVar7) goto LAB_000adddc;
                uVar1 = *(ushort *)(&DAT_00293c50 + uVar7 * 2);
              }
              if (1 < DebugLevel) {
                printk("%s: WTBL entry +++\n","WtcAcquireUcastWcid",(uint)uVar1,DebugLevel,param_4);
              }
              goto LAB_000addfc;
            }
          }
LAB_000adddc:
          iVar6 = param_3 * 0x10 + 8;
          if (param_1 + 0x1a28 + iVar6 == 0) goto LAB_000adecc;
          iVar6 = param_1 + 0x1000 + param_3 * 0x10;
          if (*(char *)(iVar6 + 0xa30) == '\0') {
            *(undefined1 *)(iVar6 + 0xa30) = 1;
            *(short *)(iVar6 + 0xa34) = (short)param_3;
            *(undefined1 *)(iVar6 + 0xa31) = *(undefined1 *)(param_2 + 4);
            uVar2 = *(undefined2 *)(param_2 + 2);
            *(undefined1 *)(iVar6 + 0xa36) = 1;
            *(char *)(iVar6 + 0xa32) = (char)uVar2;
            _raw_spin_unlock_bh(iVar9);
            return param_3;
          }
        }
LAB_000addfc:
        param_3 = param_3 + 1 & 0xffff;
      } while (param_3 < *(ushort *)(param_1 + 0x1a28));
    }
    _raw_spin_unlock_bh(iVar9);
  }
  return 0xffff;
}


// module: mt7915.ko
// function: apcli_fp_tx_pkt_allowed @ 0x676f8
// size: 668 bytes
//

bool apcli_fp_tx_pkt_allowed(int param_1,undefined *param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  ushort local_2a [3];
  
  local_2a[0] = *(ushort *)(param_3 + 0x42);
  if (*(int *)(param_2 + 0x14) == 2) {
    if (param_2 == &DAT_0036db58 + param_1) {
      iVar4 = 0;
    }
    else {
      if (param_2 != &DAT_00581308 + param_1) {
        return false;
      }
      iVar4 = 1;
    }
    iVar5 = param_1 + iVar4 * 0x2137b0;
    if (((&DAT_00580e8e)[iVar5] == '\x01') && ((&DAT_00580e8d)[iVar5] == '\x01')) {
      iVar5 = iVar4 * 0x2137b0 + param_1;
      uVar1 = *(ushort *)(&DAT_00580e38 + iVar5);
      uVar2 = HcGetMaxStaNum(param_1);
      if ((uVar1 < uVar2) &&
         (*(int *)((uint)*(ushort *)(&DAT_00580e38 + iVar5) * 0x14c0 + param_1 + 0xa1d20) == 2)) {
        if ((((&DAT_0036790d)[param_1] == '\x01') &&
            (iVar3 = repeater_enable_by_any_band(param_1), iVar3 != 0)) &&
           ((&DAT_00580eea)[iVar5] == '\0')) {
          iVar5 = ReptTxPktCheckHandler(param_1,param_2,param_3,local_2a);
          if (iVar5 != 0) {
            if (iVar5 == 1) {
              if (DebugLevel < 4) {
                return false;
              }
              printk(
                    "apcli_fp_tx_pkt_allowed: return FALSE as ReptTxPktCheckHandler indicated INSERT_REPT_ENTRY\n"
                    );
              return false;
            }
            if (iVar5 != 3) {
              if (iVar5 != 2) {
                return false;
              }
              local_2a[0] = *(ushort *)(&DAT_00580e38 + iVar4 * 0x2137b0 + param_1);
            }
          }
        }
        else {
          *(int *)(param_1 + 0xa39e78) = *(int *)(param_1 + 0xa39e78) + 1;
          *(undefined *)(param_3 + 0x2d) = param_2[0xc];
          local_2a[0] = *(ushort *)(&DAT_00580e38 + param_1 + iVar4 * 0x2137b0);
        }
        goto LAB_00067850;
      }
    }
  }
  else if (((*(int *)(param_2 + 0x14) == 0x100) &&
           (iVar4 = (uint)(byte)param_2[0xe] * 0x42f4 + *(int *)(&DAT_003687a8 + param_1),
           iVar4 != 0)) && (*(char *)(iVar4 + 5) == '\x02')) {
LAB_00067850:
    *(ushort *)(param_3 + 0x42) = local_2a[0];
    uVar2 = get_frag_num(param_1,param_2,param_3);
    *(char *)(param_3 + 0x2b) = (char)uVar2;
    if (1 < uVar2) {
      iVar4 = RTMPCheckEtherType(param_1,param_3,param_1 + (uint)local_2a[0] * 0x620 + 0x2f6a0,
                                 param_2);
      return iVar4 != 0;
    }
    if (uVar2 != 1) {
      return true;
    }
    RTMPSetFlagsOfEtherType(param_1,param_3,param_1 + (uint)local_2a[0] * 0x620 + 0x2f6a0,param_2);
    return true;
  }
  return false;
}


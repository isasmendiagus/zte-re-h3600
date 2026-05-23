// module: mt7915.ko
// function: apcli_tx_pkt_allowed @ 0x673d0
// size: 808 bytes
//

bool apcli_tx_pkt_allowed(int param_1,undefined *param_2,int param_3)

{
  char cVar1;
  ushort uVar2;
  undefined1 uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  bool bVar8;
  ushort local_2a [3];
  
  local_2a[0] = *(ushort *)(param_3 + 0x42);
  if (*(int *)(param_2 + 0x14) == 2) {
    if (param_2 == &DAT_0036db58 + param_1) {
      iVar6 = 0;
    }
    else {
      if (param_2 != &DAT_00581308 + param_1) {
        return false;
      }
      iVar6 = 1;
    }
    iVar7 = param_1 + iVar6 * 0x2137b0;
    if ((&DAT_00580e8e)[iVar7] != '\x01') {
      return false;
    }
    if ((&DAT_00580e8d)[iVar7] != '\x01') {
      return false;
    }
    iVar7 = iVar6 * 0x2137b0 + param_1;
    uVar2 = *(ushort *)(&DAT_00580e38 + iVar7);
    uVar4 = HcGetMaxStaNum(param_1);
    if (uVar4 <= uVar2) {
      return false;
    }
    if (*(int *)((uint)*(ushort *)(&DAT_00580e38 + iVar7) * 0x14c0 + param_1 + 0xa1d20) != 2) {
      return false;
    }
    if ((((&DAT_0036790d)[param_1] == '\x01') &&
        (iVar5 = repeater_enable_by_any_band(param_1), iVar5 != 0)) &&
       ((&DAT_00580eea)[iVar7] == '\0')) {
      iVar7 = ReptTxPktCheckHandler(param_1,param_2,param_3,local_2a);
      if (iVar7 != 0) {
        if (iVar7 == 1) {
          if (DebugLevel < 4) {
            return false;
          }
          printk(
                "apcli_tx_pkt_allowed: return FALSE as ReptTxPktCheckHandler indicated INSERT_REPT_ENTRY\n"
                );
          return false;
        }
        if (iVar7 != 3) {
          if (iVar7 != 2) {
            return false;
          }
          local_2a[0] = *(ushort *)(&DAT_00580e38 + iVar6 * 0x2137b0 + param_1);
        }
      }
    }
    else {
      *(int *)(param_1 + 0xa39e78) = *(int *)(param_1 + 0xa39e78) + 1;
      *(undefined *)(param_3 + 0x2d) = param_2[0xc];
      local_2a[0] = *(ushort *)(&DAT_00580e38 + param_1 + iVar6 * 0x2137b0);
    }
  }
  else {
    if (*(int *)(param_2 + 0x14) != 0x100) {
      return false;
    }
    iVar6 = (uint)(byte)param_2[0xe] * 0x42f4 + *(int *)(&DAT_003687a8 + param_1);
    if (iVar6 == 0) {
      return false;
    }
    if (*(char *)(iVar6 + 5) != '\x02') {
      return false;
    }
  }
  *(ushort *)(param_3 + 0x42) = local_2a[0];
  uVar3 = get_frag_num(param_1,param_2,param_3);
  *(undefined1 *)(param_3 + 0x2b) = uVar3;
  if (*(int *)(param_2 + 0x12e4) == 0) {
    iVar6 = RTMPCheckEtherType(param_1,param_3,param_1 + (uint)local_2a[0] * 0x620 + 0x2f6a0,param_2
                              );
    bVar8 = iVar6 != 0;
    if (*(char *)(param_1 + (uint)local_2a[0] * 0x620 + 0x2175e2) != '\x02') {
      return bVar8;
    }
  }
  else {
    cVar1 = param_2[0x3cc8];
    iVar6 = RTMPCheckEtherType(param_1,param_3,param_1 + (uint)local_2a[0] * 0x620 + 0x2f6a0,param_2
                              );
    bVar8 = iVar6 != 0;
    if (*(char *)(param_1 + (uint)local_2a[0] * 0x620 + 0x2175e2) != '\x02') {
      return bVar8;
    }
    if (cVar1 != '\0') goto LAB_000675dc;
  }
  if (((*(uint *)(param_2 + 0x2c) & 0x12cf8) == 0) && (param_2[0x5c0] != '\x01')) {
    return false;
  }
LAB_000675dc:
  if ((*(byte *)(param_3 + 0x30) & 10) == 0) {
    return false;
  }
  return bVar8;
}


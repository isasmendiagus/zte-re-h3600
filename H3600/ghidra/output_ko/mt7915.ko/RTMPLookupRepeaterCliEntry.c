// module: mt7915.ko
// function: RTMPLookupRepeaterCliEntry @ 0x811d0
// size: 408 bytes
//

char * RTMPLookupRepeaterCliEntry(int param_1,int param_2,undefined4 *param_3,int param_4)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 local_1e;
  undefined2 local_1a;
  
  uVar6 = *param_3;
  uVar1 = *(undefined2 *)(param_3 + 1);
  local_1e._0_1_ = (byte)uVar6;
  local_1e._1_1_ = (byte)((uint)uVar6 >> 8);
  local_1e._2_1_ = (byte)((uint)uVar6 >> 0x10);
  local_1e._3_1_ = (byte)((uint)uVar6 >> 0x18);
  local_1a._0_1_ = (byte)uVar1;
  local_1a._1_1_ = (byte)((ushort)uVar1 >> 8);
  uVar3 = (uint)(byte)(local_1e._1_1_ ^ (byte)local_1e ^ local_1e._2_1_ ^ local_1e._3_1_ ^
                       (byte)local_1a ^ local_1a._1_1_);
  local_1e = uVar6;
  local_1a = uVar1;
  if (param_4 == 1) {
    _raw_spin_lock_bh(&DAT_00367914 + param_1);
    if (param_2 == 1) {
      puVar5 = *(undefined4 **)(param_1 + (uVar3 + 0xd9f46) * 4);
      if (puVar5 != (undefined4 *)0x0) goto LAB_000812e8;
      pcVar4 = (char *)0x0;
    }
    else {
      pcVar4 = *(char **)(param_1 + (uVar3 + 0xd9e46) * 4);
      if (pcVar4 != (char *)0x0) goto LAB_00081244;
    }
    _raw_spin_unlock_bh(&DAT_00367914 + param_1);
  }
  else {
    _raw_spin_lock_bh(*(undefined4 *)(param_1 + 4));
    if (param_2 == 1) {
      puVar5 = (undefined4 *)(*(int *)(param_1 + 0xc) + uVar3 * 4);
      if (puVar5 == (undefined4 *)0x0) {
        pcVar4 = (char *)0x0;
        goto LAB_00081280;
      }
LAB_000812e8:
      do {
        pcVar4 = (char *)*puVar5;
        if (((pcVar4 != (char *)0x0) && (*pcVar4 != '\0')) &&
           (iVar2 = memcmp(pcVar4 + 0x7d,&local_1e,6), iVar2 == 0)) goto LAB_00081278;
        puVar5 = (undefined4 *)puVar5[1];
      } while (puVar5 != (undefined4 *)0x0);
    }
    else {
      pcVar4 = (char *)(*(int *)(param_1 + 8) + uVar3 * 4);
      if (pcVar4 == (char *)0x0) goto LAB_00081280;
LAB_00081244:
      do {
        if ((*pcVar4 != '\0') && (iVar2 = memcmp(pcVar4 + 0x83,&local_1e,6), iVar2 == 0))
        goto LAB_00081278;
        pcVar4 = *(char **)(pcVar4 + 0x90);
      } while (pcVar4 != (char *)0x0);
    }
    pcVar4 = (char *)0x0;
LAB_00081278:
    if (param_4 != 1) {
LAB_00081280:
      _raw_spin_unlock_bh(*(undefined4 *)(param_1 + 4));
      return pcVar4;
    }
    _raw_spin_unlock_bh(&DAT_00367914 + param_1);
  }
  return pcVar4;
}


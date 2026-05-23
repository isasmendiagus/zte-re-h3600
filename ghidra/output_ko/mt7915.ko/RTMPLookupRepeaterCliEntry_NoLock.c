// module: mt7915.ko
// function: RTMPLookupRepeaterCliEntry_NoLock @ 0x81800
// size: 276 bytes
//

char * RTMPLookupRepeaterCliEntry_NoLock(int param_1,int param_2,undefined4 *param_3,int param_4)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  char *pcVar4;
  char *pcVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  undefined4 local_16;
  undefined2 local_12;
  
  uVar7 = *param_3;
  uVar1 = *(undefined2 *)(param_3 + 1);
  local_16._1_1_ = (byte)((uint)uVar7 >> 8);
  local_16._0_1_ = (byte)uVar7;
  local_16._2_1_ = (byte)((uint)uVar7 >> 0x10);
  local_16._3_1_ = (byte)((uint)uVar7 >> 0x18);
  local_12._0_1_ = (byte)uVar1;
  local_12._1_1_ = (byte)((ushort)uVar1 >> 8);
  uVar3 = (uint)(byte)((byte)local_16 ^ local_16._1_1_ ^ local_16._2_1_ ^ local_16._3_1_ ^
                       (byte)local_12 ^ local_12._1_1_);
  local_16 = uVar7;
  local_12 = uVar1;
  if (param_2 == 1) {
    if (param_4 == 1) {
      puVar6 = *(undefined4 **)(param_1 + (uVar3 + 0xd9f46) * 4);
    }
    else {
      puVar6 = *(undefined4 **)(*(int *)(param_1 + 0xc) + uVar3 * 4);
    }
    while( true ) {
      if (puVar6 == (undefined4 *)0x0) {
        return (char *)0x0;
      }
      pcVar5 = (char *)*puVar6;
      if (((pcVar5 != (char *)0x0) && (*pcVar5 != '\0')) &&
         (iVar2 = memcmp(pcVar5 + 0x7d,&local_16,6), iVar2 == 0)) break;
      puVar6 = (undefined4 *)puVar6[1];
    }
  }
  else {
    if (param_4 == 1) {
      pcVar4 = *(char **)(param_1 + (uVar3 + 0xd9e46) * 4);
    }
    else {
      pcVar4 = *(char **)(*(int *)(param_1 + 8) + uVar3 * 4);
    }
    for (; pcVar5 = (char *)0x0, pcVar4 != (char *)0x0; pcVar4 = *(char **)(pcVar4 + 0x90)) {
      if ((*pcVar4 != '\0') && (iVar2 = memcmp(pcVar4 + 0x83,&local_16,6), iVar2 == 0)) {
        return pcVar4;
      }
    }
  }
  return pcVar5;
}


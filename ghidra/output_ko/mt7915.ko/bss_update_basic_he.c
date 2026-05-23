// module: mt7915.ko
// function: bss_update_basic_he @ 0x1c24f4
// size: 204 bytes
//

void bss_update_basic_he(undefined4 param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  byte *pbVar7;
  byte *pbVar8;
  byte *pbVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  uint local_28;
  undefined4 local_24;
  
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  os_zero_mem(&local_34,0x14);
  uVar10 = 0;
  pbVar7 = (byte *)(param_2 + 0x97);
  local_30 = *(undefined4 *)(param_2 + 0x94);
  pbVar9 = (byte *)(param_2 + 0xa7);
  pbVar8 = (byte *)(param_2 + 0x9f);
  uVar11 = local_2c & 0xffff;
  local_2c = local_2c >> 0x10;
  uVar12 = local_28 & 0xffff;
  local_34 = 0x14000d;
  do {
    pbVar7 = pbVar7 + 1;
    pbVar9 = pbVar9 + 1;
    pbVar8 = pbVar8 + 1;
    uVar1 = (uint)*pbVar7 << (uVar10 & 0xff);
    uVar4 = (ushort)uVar11;
    uVar2 = (uint)*pbVar9 << (uVar10 & 0xff);
    uVar5 = (ushort)local_2c;
    uVar3 = (uint)*pbVar8 << (uVar10 & 0xff);
    uVar6 = (ushort)uVar12;
    uVar10 = uVar10 + 2;
    uVar11 = uVar11 | uVar1 & 0xffff;
    local_2c = local_2c | uVar2 & 0xffff;
    uVar12 = uVar12 | uVar3 & 0xffff;
  } while (uVar10 != 0x10);
  local_2c = CONCAT22(uVar5 | (ushort)uVar2,uVar4 | (ushort)uVar1);
  local_28 = CONCAT22(local_28._2_2_,uVar6 | (ushort)uVar3);
  AndesAppendCmdMsg(param_3,&local_34,0x14);
  return;
}


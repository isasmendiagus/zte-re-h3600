// module: mt7915.ko
// function: sta_rec_update_he_info @ 0x1c1ef4
// size: 520 bytes
//

undefined4 sta_rec_update_he_info(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  byte bVar4;
  byte *pbVar5;
  byte *pbVar6;
  uint uVar7;
  byte *pbVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined2 local_44;
  undefined2 local_42;
  uint local_40;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined1 local_34;
  undefined1 local_33;
  undefined1 local_32;
  ushort local_30;
  ushort local_2e;
  ushort local_2c;
  
  if (*(int *)(param_3 + 0x9c) == 0) {
    return 0xffffffff;
  }
  os_zero_mem(&local_44,0x1c);
  local_3c = *(undefined1 *)(param_3 + 0xaa);
  local_3a = *(undefined1 *)(param_3 + 0xac);
  local_35 = *(undefined1 *)(param_3 + 0xb6);
  local_3b = *(undefined1 *)(param_3 + 0xa9);
  local_39 = *(undefined1 *)(param_3 + 0xaf);
  local_33 = *(undefined1 *)(param_3 + 0xae);
  local_36 = *(undefined1 *)(param_3 + 0xb5);
  local_38 = *(undefined1 *)(param_3 + 0xb3);
  local_37 = *(undefined1 *)(param_3 + 0xb4);
  local_34 = *(undefined1 *)(param_3 + 0xb7);
  local_42 = 0x1c;
  local_44 = 0xe;
  local_32 = 2;
  bVar4 = *(byte *)(param_3 + 0xb1);
  uVar9 = (uint)local_30;
  local_40 = *(byte *)(param_3 + 0xa4) | local_40 | (uint)*(byte *)(param_3 + 0xa5) << 1 |
             (uint)*(byte *)(param_3 + 0xa6) << 2 | (uint)*(byte *)(param_3 + 0xa7) << 3 |
             (uint)*(byte *)(param_3 + 0xa8) << 4 | (uint)*(byte *)(param_3 + 0xab) << 5 |
             (uint)*(byte *)(param_3 + 0xb0) << 6 | (uint)*(byte *)(param_3 + 0xba) << 7 |
             (uint)*(byte *)(param_3 + 0xbb) << 8 | (uint)*(byte *)(param_3 + 0xad) << 0x12 |
             (uint)*(byte *)(param_3 + 0xb8) << 0x13 | (uint)*(byte *)(param_3 + 0xb9) << 0x14;
  if ((bVar4 & 1) != 0) {
    local_40 = local_40 | 0x200;
  }
  uVar11 = (uint)local_2e;
  pbVar5 = (byte *)(param_3 + 0xbb);
  pbVar6 = (byte *)(param_3 + 0xcb);
  uVar10 = (uint)local_2c;
  pbVar8 = (byte *)(param_3 + 0xc3);
  if ((bVar4 & 2) != 0) {
    local_40 = local_40 | 0x400;
  }
  if ((bVar4 & 8) != 0) {
    local_40 = local_40 | 0x1000;
  }
  if ((bVar4 & 4) != 0) {
    local_40 = local_40 | 0x800;
  }
  bVar4 = *(byte *)(param_3 + 0xb2);
  if ((bVar4 & 1) != 0) {
    local_40 = local_40 | 0x2000;
  }
  if ((bVar4 & 2) != 0) {
    local_40 = local_40 | 0x4000;
  }
  if ((bVar4 & 4) != 0) {
    local_40 = local_40 | 0x8000;
  }
  if ((bVar4 & 8) != 0) {
    local_40 = local_40 | 0x10000;
  }
  if ((bVar4 & 0x10) != 0) {
    local_40 = local_40 | 0x20000;
  }
  uVar7 = 0;
  do {
    pbVar5 = pbVar5 + 1;
    pbVar6 = pbVar6 + 1;
    pbVar8 = pbVar8 + 1;
    uVar1 = (uint)*pbVar5 << (uVar7 & 0xff);
    local_30 = (ushort)uVar9 | (ushort)uVar1;
    uVar2 = (uint)*pbVar6 << (uVar7 & 0xff);
    local_2e = (ushort)uVar11 | (ushort)uVar2;
    uVar3 = (uint)*pbVar8 << (uVar7 & 0xff);
    local_2c = (ushort)uVar10 | (ushort)uVar3;
    uVar7 = uVar7 + 2;
    uVar9 = uVar9 | uVar1 & 0xffff;
    uVar11 = uVar11 | uVar2 & 0xffff;
    uVar10 = uVar10 | uVar3 & 0xffff;
  } while (uVar7 != 0x10);
  AndesAppendCmdMsg(param_2,&local_44,0x1c);
  return 0;
}


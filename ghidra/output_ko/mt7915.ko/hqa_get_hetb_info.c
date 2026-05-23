// module: mt7915.ko
// function: hqa_get_hetb_info @ 0x246c04
// size: 228 bytes
//

undefined4 hqa_get_hetb_info(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint local_24 [2];
  
  iVar4 = (uint)*(byte *)(param_1 + 0x4cc) * 0xd18;
  param_1 = param_1 + iVar4 + (uint)*(byte *)(param_1 + iVar4 + 0x10dc) * 0x6c;
  uVar3 = *(uint *)(param_1 + 0xa4c);
  bVar1 = *(byte *)(param_1 + 0xa78);
  local_24[0] = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                uVar3 >> 0x18;
  bVar2 = *(byte *)(param_1 + 0xa80);
  uVar5 = *(uint *)(param_1 + 0xa48);
  uVar3 = *(uint *)(param_1 + 0xa84);
  sys_ad_move_mem((void *)(param_2 + 0xe),local_24,4);
  local_24[0] = (uint)bVar1 << 0x18;
  sys_ad_move_mem((void *)(param_2 + 0x12),local_24,4);
  local_24[0] = (uint)bVar2 << 0x18;
  sys_ad_move_mem((void *)(param_2 + 0x16),local_24,4);
  local_24[0] = uVar5 << 0x18 | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 |
                uVar5 >> 0x18;
  sys_ad_move_mem((void *)(param_2 + 0x1a),local_24,4);
  local_24[0] = uVar3 << 0x18 | (uVar3 >> 8 & 0xff) << 0x10 | (uVar3 >> 0x10 & 0xff) << 8 |
                uVar3 >> 0x18;
  sys_ad_move_mem((void *)(param_2 + 0x1e),local_24,4);
  FUN_00246b90(param_2,0x16,0);
  return 0;
}


// module: mt7915.ko
// function: WscDeriveKey @ 0x1f3748
// size: 312 bytes
//

/* WARNING: Type propagation algorithm not settling */
/* WARNING: Restarted to delay deadcode elimination for space: stack */

bool WscDeriveKey(undefined4 param_1,undefined4 param_2,void *param_3,size_t param_4,void *param_5,
                 uint param_6)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_108;
  undefined4 uStack_104;
  undefined4 uStack_100;
  undefined4 uStack_fc;
  undefined4 local_f8;
  undefined4 uStack_f4;
  undefined4 uStack_f0;
  undefined4 uStack_ec;
  uint local_e8 [16];
  undefined4 local_a8 [33];
  
  __memzero(local_e8,0x40);
  __memzero(local_a8,0x80);
  uVar2 = param_6 >> 3;
  uVar3 = uVar2 + 0x1f >> 5;
  __memzero(&local_108,0x20);
  local_e8[0] = 0;
  memcpy(local_e8 + 1,param_3,param_4);
  *(uint *)((int)local_e8 + param_4 + 4) =
       param_6 << 0x18 | (param_6 >> 8 & 0xff) << 0x10 | (param_6 >> 0x10 & 0xff) << 8 |
       param_6 >> 0x18;
  if (uVar3 != 0) {
    uVar4 = 0x1000000;
    uVar5 = 0;
    do {
      uVar6 = uVar5 + 1;
      local_e8[0] = uVar4;
      RT_HMAC_SHA256(param_1,param_2,local_e8,param_4 + 8,&local_108,0x20);
      uVar4 = uVar5 + 2;
      uVar4 = uVar4 * 0x1000000 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 |
              uVar4 >> 0x18;
      local_a8[uVar5 * 8] = local_108;
      local_a8[uVar5 * 8 + 1] = uStack_104;
      local_a8[uVar5 * 8 + 2] = uStack_100;
      local_a8[uVar5 * 8 + 3] = uStack_fc;
      local_a8[uVar5 * 8 + 4] = local_f8;
      local_a8[uVar5 * 8 + 5] = uStack_f4;
      local_a8[uVar5 * 8 + 6] = uStack_f0;
      local_a8[uVar5 * 8 + 7] = uStack_ec;
      uVar5 = uVar6;
    } while (uVar6 != uVar3);
  }
  bVar1 = uVar3 * 0x20 < uVar2;
  if (!bVar1) {
    memcpy(param_5,local_a8,0x50);
  }
  return bVar1;
}


// module: mt7915.ko
// function: mt_op_set_muru_manual @ 0x258c14
// size: 488 bytes
//

undefined4 mt_op_set_muru_manual(undefined4 param_1,int param_2,int param_3)

{
  byte bVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint *puVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined1 local_22a;
  undefined1 local_229;
  uint local_228;
  uint local_224;
  undefined1 local_21c;
  undefined1 uStack_21a;
  undefined1 local_219;
  undefined1 local_218;
  undefined1 local_216;
  undefined1 local_215;
  byte local_214;
  undefined1 local_213;
  undefined1 local_212;
  byte local_211;
  byte local_210;
  undefined1 auStack_20e [8];
  undefined1 auStack_206 [2];
  undefined2 local_204;
  char local_202 [12];
  undefined2 local_1f6 [103];
  uint auStack_128 [68];
  
  uVar4 = *(uint *)(param_3 + 0xc48);
  local_229 = 0;
  local_22a = 0;
  if ((int)uVar4 < 0) {
    local_229 = (undefined1)uVar4;
  }
  else {
    net_ad_get_speidx(param_2,uVar4 & 0xffff,&local_229);
  }
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_2 + 4));
  if (iVar2 == 0) {
    uVar3 = 0x503;
  }
  else {
    iVar6 = *(int *)(param_3 + 0x27c);
    sys_ad_zero_mem(&local_228,0x210);
    local_21c = 8;
    local_228 = 1;
    net_ad_get_band_idx(param_1,&uStack_21a);
    local_228 = local_228 | 4;
    net_ad_get_wmm_idx(param_1,&local_22a);
    bVar1 = *(byte *)(param_3 + 0xc57);
    local_215 = *(undefined1 *)(param_3 + 0xc55);
    local_216 = *(undefined1 *)(param_3 + 0x215);
    local_228 = local_228 | 0x18;
    local_218 = local_229;
    if (2 < bVar1) {
      local_214 = 3;
    }
    local_219 = local_22a;
    if (bVar1 < 3) {
      local_214 = bVar1;
    }
    local_224 = local_224 | 0xd5;
    local_211 = *(byte *)(param_3 + 0xc58) & 0xf;
    local_210 = (byte)(((uint)*(byte *)(param_3 + 0xc58) << 0x1a) >> 0x1f);
    sys_ad_move_mem(auStack_20e,(void *)(param_3 + 0xbfd),8);
    local_213 = *(undefined1 *)(param_3 + 0x343);
    local_212 = *(undefined1 *)(param_3 + 0x342);
    puVar5 = &local_228;
    do {
      if (*(char *)(param_3 + 0x53c) != '\0') {
        uVar4 = *(uint *)(param_3 + 0x548);
        uVar3 = *(undefined4 *)(param_3 + 0x560);
        *(undefined2 *)(puVar5 + 9) = *(undefined2 *)(iVar6 + 0xe0);
        uVar7 = uVar4 & 1;
        uVar4 = uVar4 >> 1;
        *(char *)((int)puVar5 + 0x26) = (char)uVar7;
        *(char *)((int)puVar5 + 0x27) = (char)uVar4;
        uVar8 = *(undefined4 *)(iVar6 + 0xd0);
        *(short *)((int)puVar5 + 0x32) = (short)uVar3;
        bVar1 = (byte)uVar8 & 0xf;
        *(byte *)((int)puVar5 + 0x2a) = bVar1;
        if ((*(uint *)(iVar6 + 0xd0) & 0x20) != 0) {
          *(byte *)((int)puVar5 + 0x2a) = bVar1 | 0x10;
        }
        *(char *)((int)puVar5 + 0x29) = *(char *)(iVar6 + 0xcd) + -1;
        *(undefined1 *)(puVar5 + 10) = *(undefined1 *)(iVar6 + 199);
        if (uVar4 == 0x12) {
          auStack_206[uVar7] = 1;
        }
      }
      puVar5 = puVar5 + 4;
      param_3 = param_3 + 0x6c;
      iVar6 = iVar6 + 0x14c0;
    } while (puVar5 != auStack_128);
    local_224 = local_224 | 0x21f002a;
    wifi_test_muru_set_manual_config(iVar2,&local_228);
    uVar3 = 0;
  }
  return uVar3;
}


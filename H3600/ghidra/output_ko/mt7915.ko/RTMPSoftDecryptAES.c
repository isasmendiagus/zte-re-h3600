// module: mt7915.ko
// function: RTMPSoftDecryptAES @ 0xb69a0
// size: 1348 bytes
//

undefined4 RTMPSoftDecryptAES(undefined4 param_1,byte *param_2,int param_3,int param_4)

{
  bool bVar1;
  uint uVar2;
  byte *pbVar3;
  int iVar4;
  byte bVar5;
  byte *pbVar6;
  byte *pbVar7;
  uint uVar8;
  byte *pbVar9;
  byte *pbVar10;
  byte *pbVar11;
  byte *pbVar12;
  uint __n;
  uint uVar13;
  int local_c4;
  int local_c0;
  byte local_ae;
  byte local_ad;
  byte local_ac;
  byte local_ab;
  byte local_aa;
  byte local_a9;
  byte local_a8 [8];
  undefined1 local_a0 [7];
  byte bStack_99;
  undefined1 local_98 [7];
  byte abStack_91 [8];
  byte bStack_89;
  undefined1 auStack_88 [15];
  byte bStack_79;
  undefined4 local_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 local_68;
  undefined4 uStack_64;
  undefined1 auStack_58 [15];
  byte bStack_49;
  byte local_48 [15];
  byte bStack_39;
  byte local_38 [20];
  
  bVar1 = (*param_2 >> 4) - 8 < 4;
  bVar5 = param_2[1] & 1 & param_2[1] >> 1;
  if (bVar5 == 0) {
    local_c4 = 0x18;
  }
  else {
    local_c4 = 0x1e;
  }
  if (bVar1) {
    local_c4 = local_c4 + 2;
  }
  if (*(char *)(param_4 + 0x41) == '\0') {
    if (2 < DebugLevel) {
      printk("RTMPSoftDecryptAES failed!(the Length can not be 0)\n");
      return 0;
    }
  }
  else {
    pbVar11 = &bStack_99;
    pbVar10 = param_2 + local_c4;
    uVar8 = (param_3 + -0x10) - local_c4;
    local_ad = pbVar10[1];
    __n = uVar8 & 0xf;
    local_ac = pbVar10[4];
    uVar2 = uVar8 >> 4;
    local_ae = param_2[local_c4];
    local_c0 = local_c4 + 8;
    pbVar7 = &bStack_79;
    local_ab = pbVar10[5];
    local_aa = pbVar10[6];
    local_a9 = pbVar10[7];
    if (uVar2 != 0) {
      uVar13 = 0;
      do {
        uVar13 = uVar13 + 1;
        construct_ctr_preload(auStack_88,bVar5,bVar1,param_2,&local_ae,uVar13);
        aes128k128d(param_4,auStack_88,local_98);
        pbVar3 = pbVar10 + 7;
        pbVar6 = pbVar7;
        pbVar9 = pbVar11;
        do {
          pbVar9 = pbVar9 + 1;
          pbVar3 = pbVar3 + 1;
          pbVar6 = pbVar6 + 1;
          *pbVar6 = *pbVar9 ^ *pbVar3;
        } while (pbVar9 != &bStack_89);
        *(undefined4 *)pbVar10 = local_78;
        *(undefined4 *)(pbVar10 + 4) = uStack_74;
        *(undefined4 *)(pbVar10 + 8) = uStack_70;
        *(undefined4 *)(pbVar10 + 0xc) = uStack_6c;
        pbVar10 = pbVar10 + 0x10;
      } while (uVar13 != uVar2);
      local_c0 = local_c0 + uVar2 * 0x10;
    }
    if (__n != 0) {
      construct_ctr_preload(auStack_88,bVar5,bVar1,param_2,&local_ae,uVar2 + 1);
      pbVar9 = (byte *)((int)&uStack_6c + 3);
      __memzero(&local_68,0x10);
      memcpy(&local_68,param_2 + local_c0,__n);
      aes128k128d(param_4,auStack_88,local_98);
      pbVar10 = pbVar7;
      pbVar6 = pbVar11;
      do {
        pbVar6 = pbVar6 + 1;
        pbVar9 = pbVar9 + 1;
        pbVar10 = pbVar10 + 1;
        *pbVar10 = *pbVar6 ^ *pbVar9;
      } while (pbVar6 != &bStack_89);
      memcpy(param_2 + local_c0 + -8,&local_78,__n);
      local_c0 = local_c0 + __n;
    }
    pbVar3 = (byte *)((int)&uStack_6c + 3);
    construct_ctr_preload(auStack_88,bVar5,bVar1,param_2,&local_ae,0);
    __memzero(&local_68,0x10);
    local_68 = *(undefined4 *)(param_2 + local_c0);
    uStack_64 = *(undefined4 *)(param_2 + local_c0 + 4);
    aes128k128d(param_4,auStack_88,local_98);
    pbVar10 = pbVar3;
    pbVar6 = pbVar7;
    pbVar9 = pbVar11;
    do {
      pbVar9 = pbVar9 + 1;
      pbVar10 = pbVar10 + 1;
      pbVar6 = pbVar6 + 1;
      *pbVar6 = *pbVar9 ^ *pbVar10;
    } while (pbVar9 != &bStack_89);
    param_2[1] = param_2[1] | 0x40;
    construct_mic_iv(auStack_58,bVar1,bVar5,param_2,uVar8,&local_ae);
    construct_mic_header1(local_48,local_c4,param_2);
    construct_mic_header2(local_38,param_2,bVar5,bVar1);
    aes128k128d(param_4,auStack_58,local_98);
    pbVar9 = &bStack_49;
    pbVar10 = pbVar7;
    pbVar6 = pbVar11;
    do {
      pbVar6 = pbVar6 + 1;
      pbVar9 = pbVar9 + 1;
      pbVar10 = pbVar10 + 1;
      *pbVar10 = *pbVar6 ^ *pbVar9;
    } while (&bStack_89 != pbVar6);
    aes128k128d(param_4,&local_78,local_98);
    pbVar9 = &bStack_39;
    pbVar10 = pbVar7;
    pbVar6 = pbVar11;
    do {
      pbVar6 = pbVar6 + 1;
      pbVar9 = pbVar9 + 1;
      pbVar10 = pbVar10 + 1;
      *pbVar10 = *pbVar6 ^ *pbVar9;
    } while (&bStack_89 != pbVar6);
    aes128k128d(param_4,&local_78,local_98);
    if (uVar2 != 0) {
      pbVar12 = param_2 + local_c4 + -1;
      pbVar10 = pbVar11;
      pbVar6 = pbVar7;
      pbVar9 = pbVar12;
      do {
        do {
          pbVar10 = pbVar10 + 1;
          pbVar12 = pbVar12 + 1;
          pbVar6[1] = *pbVar10 ^ *pbVar12;
          pbVar6 = pbVar6 + 1;
        } while (&bStack_89 != pbVar10);
        pbVar12 = pbVar9 + 0x10;
        aes128k128d(param_4,&local_78,local_98);
        pbVar10 = pbVar11;
        pbVar6 = pbVar7;
        pbVar9 = pbVar12;
      } while (pbVar12 != param_2 + uVar2 * 0x10 + local_c4 + -1);
      local_c4 = local_c4 + uVar2 * 0x10;
    }
    if (__n != 0) {
      __memzero(&local_68,0x10);
      memcpy(&local_68,param_2 + local_c4,__n);
      pbVar10 = pbVar11;
      do {
        pbVar10 = pbVar10 + 1;
        pbVar3 = pbVar3 + 1;
        pbVar7 = pbVar7 + 1;
        *pbVar7 = *pbVar10 ^ *pbVar3;
      } while (&bStack_89 != pbVar10);
      aes128k128d(param_4,&local_78,local_98);
    }
    pbVar10 = &local_a9;
    do {
      pbVar11 = pbVar11 + 1;
      pbVar10 = pbVar10 + 1;
      *pbVar10 = *pbVar11;
    } while (pbVar11 != abStack_91);
    iVar4 = memcmp(local_a8,local_a0,8);
    if (iVar4 == 0) {
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("RTMPSoftDecryptAES, MIC Error !\n");
      return 0;
    }
  }
  return 0;
}


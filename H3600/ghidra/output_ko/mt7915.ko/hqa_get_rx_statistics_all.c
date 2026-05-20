// module: mt7915.ko
// function: hqa_get_rx_statistics_all @ 0x24a3b0
// size: 904 bytes
//

int hqa_get_rx_statistics_all(int *param_1,int param_2)

{
  void *pvVar1;
  char *pcVar2;
  sbyte *psVar3;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  void *__dest;
  uint *puVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  uint local_a4;
  uint local_a0;
  byte local_91;
  uint local_90;
  uint local_8c;
  uint local_88;
  uint *local_84;
  int local_80;
  sbyte local_7c [4];
  uint auStack_78 [21];
  sbyte *psVar4;
  
  local_80 = param_2 + 0xc;
  local_90 = 0;
  local_8c = 0;
  local_88 = 0;
  local_84 = (uint *)0x0;
  local_7c[0] = 0;
  local_7c[1] = 0;
  local_7c[2] = 0;
  local_7c[3] = 0;
  local_91 = 0;
  memcpy(auStack_78,&DAT_002a4320,0x50);
  FUN_002474f4(1,4,&local_80,&local_90);
  FUN_002474f4(1,4,&local_80,&local_8c);
  if ((*(char *)(*param_1 + 0x34) == '\0') && (local_8c != 0)) {
    pcVar2 = "%s: invalid band index for non-dbdc mode.\n";
    iVar12 = 0;
  }
  else {
    mt_serv_get_wf_path_comb(param_1,local_8c & 0xff,*(char *)(*param_1 + 0x34),local_7c,&local_91);
    uVar10 = 1 << (local_8c & 0xff);
    auStack_78[2] = uVar10;
    if (local_91 != 0) {
      psVar4 = local_7c;
      do {
        psVar3 = psVar4 + 1;
        auStack_78[7] = auStack_78[7] | 1 << *psVar4;
        psVar4 = psVar3;
      } while (psVar3 != local_7c + local_91);
    }
    uVar5 = 0;
    do {
      auStack_78[0xc] = auStack_78[0xc] | 1 << (uVar5 & 0xff);
      uVar5 = uVar5 + 1;
    } while (uVar5 != 0x10);
    auStack_78[0x11] = 1;
    iVar12 = 0;
    while( true ) {
      uVar5 = 0;
      do {
        uVar8 = uVar5 & 0xff;
        uVar5 = uVar5 + 1;
        if ((uVar10 >> uVar8 & 1) != 0) {
          auStack_78[iVar12 * 5 + 3] = auStack_78[iVar12 * 5 + 3] + 1;
        }
      } while (uVar5 != 0x20);
      iVar12 = iVar12 + 1;
      if (iVar12 == 4) break;
      uVar10 = auStack_78[iVar12 * 5 + 2];
    }
    iVar12 = sys_ad_alloc_mem(&local_84,0x38);
    __dest = (void *)(param_2 + 0x12);
    if (iVar12 == 0) {
      iVar12 = 0;
      local_a4 = 0;
      local_a0 = 0;
      do {
        if ((local_90 >> (local_a4 & 0xff) & 1) != 0) {
          local_a0 = local_a0 + 1;
          uVar11 = auStack_78[local_a4 * 5 + 4];
          iVar12 = iVar12 + 0x10;
          uVar10 = auStack_78[local_a4 * 5];
          uVar5 = auStack_78[local_a4 * 5 + 3] * uVar11;
          local_88 = uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
                     uVar10 >> 0x18;
          sys_ad_move_mem(__dest,&local_88,4);
          uVar10 = auStack_78[local_a4 * 5 + 1];
          local_88 = uVar10 << 0x18 | (uVar10 >> 8 & 0xff) << 0x10 | (uVar10 >> 0x10 & 0xff) << 8 |
                     uVar10 >> 0x18;
          uVar10 = uVar11 >> 2;
          sys_ad_move_mem((void *)((int)__dest + 4),&local_88,4);
          uVar8 = auStack_78[local_a4 * 5 + 2];
          local_88 = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 |
                     uVar8 >> 0x18;
          sys_ad_move_mem((void *)((int)__dest + 8),&local_88,4);
          pvVar1 = (void *)((int)__dest + 0xc);
          __dest = (void *)((int)__dest + 0x10);
          local_88 = uVar5 * 0x1000000 | (uVar5 >> 8 & 0xff) << 0x10 | (uVar5 >> 0x10 & 0xff) << 8 |
                     uVar5 >> 0x18;
          sys_ad_move_mem(pvVar1,&local_88,4);
          uVar5 = 0;
          do {
            while ((uVar8 >> (uVar5 & 0xff) & 1) != 0) {
              mt_serv_get_rx_stat(param_1,local_8c & 0xff,uVar5 & 0xff,local_a4 & 0xff,local_84);
              if (uVar10 != 0) {
                uVar7 = 0;
                pvVar1 = __dest;
                puVar9 = local_84;
                do {
                  uVar6 = *puVar9;
                  uVar7 = uVar7 + 1;
                  local_88 = uVar6 << 0x18 | (uVar6 >> 8 & 0xff) << 0x10 |
                             (uVar6 >> 0x10 & 0xff) << 8 | uVar6 >> 0x18;
                  sys_ad_move_mem(pvVar1,&local_88,4);
                  pvVar1 = (void *)((int)pvVar1 + 4);
                  puVar9 = puVar9 + 1;
                } while (uVar7 != uVar10);
                __dest = (void *)((int)__dest + uVar10 * 4);
              }
              uVar5 = uVar5 + 1;
              iVar12 = iVar12 + uVar11;
              if (uVar5 == 0x20) goto LAB_0024a6a8;
            }
            uVar5 = uVar5 + 1;
          } while (uVar5 != 0x20);
        }
LAB_0024a6a8:
        local_a4 = local_a4 + 1;
        if (local_a4 == 4) {
          sys_ad_free_mem(local_84);
          local_88 = local_a0 << 0x18 | (local_a0 >> 8 & 0xff) << 0x10 |
                     (local_a0 >> 0x10 & 0xff) << 8 | local_a0 >> 0x18;
          sys_ad_move_mem((void *)(param_2 + 0xe),&local_88,4);
          FUN_00246b90(param_2,iVar12 + 6,0);
          return 0;
        }
      } while( true );
    }
    pcVar2 = "%s: memory allocation fail for rx stat.\n";
  }
  printk(pcVar2,"hqa_get_rx_statistics_all");
  FUN_00246b90(param_2,2,iVar12);
  return iVar12;
}


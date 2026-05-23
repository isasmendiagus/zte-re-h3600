// module: mt7915.ko
// function: eFuseWrite @ 0x1d2468
// size: 1844 bytes
//

undefined4 eFuseWrite(int param_1,uint param_2,ushort *param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  uint extraout_r1;
  uint extraout_r1_00;
  uint extraout_r1_01;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  ushort *puVar7;
  uint uVar8;
  uint uVar9;
  ushort *puVar10;
  uint uVar11;
  bool bVar12;
  uint local_74;
  uint local_68;
  ushort local_64;
  ushort local_60;
  int local_5c;
  ushort *local_58;
  uint local_54;
  uint local_50;
  ushort local_46;
  ushort *local_44;
  short local_3e;
  undefined2 local_3c;
  ushort local_3a;
  ushort auStack_38 [8];
  ushort auStack_28 [2];
  
  os_alloc_mem(0,&local_44,4);
  if (local_44 == (ushort *)0x0) {
    return 0;
  }
  local_58 = param_3;
  local_54 = param_4;
  local_50 = param_2;
  if ((param_2 & 1) != 0) {
    local_50 = param_2 - 1 & 0xffff;
    local_54 = param_4 + 2 & 0xffff;
    eFuseRead(param_1,local_50,local_44,2);
    eFuseRead(param_1,param_2 + 1 & 0xffff,local_44 + 1);
    *local_44 = (ushort)(byte)*local_44;
    *local_44 = *local_44 | *param_3 << 8;
    local_44[1] = local_44[1] & 0xff00;
    local_44[1] = local_44[1] | *param_3 >> 8;
    local_58 = local_44;
  }
  if (local_54 == 0) {
LAB_001d2730:
    os_free_mem(local_44);
    return 1;
  }
  local_5c = 0;
LAB_001d24dc:
  uVar3 = local_50 + local_5c;
  uVar4 = uVar3 & 0xffff;
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if (2 < DebugLevel) {
    printk("eFuseWriteRegisters Offset=%x, pData=%x\n",uVar4,
           *(undefined2 *)((int)local_58 + local_5c));
  }
  local_68 = (uint)*(ushort *)(iVar1 + 0xe8);
  uVar9 = (uint)*(ushort *)(iVar1 + 0xe6);
  if ((*(ushort *)(iVar1 + 0xe8) & 1) != 0) {
    local_68 = local_68 - 1 & 0xffff;
  }
  bVar12 = (*(ushort *)(iVar1 + 0xe6) & 1) != 0;
  if (bVar12) {
    uVar9 = uVar9 - 1;
  }
  if (bVar12) {
    uVar9 = uVar9 & 0xffff;
  }
  uVar2 = eFuseReadRegisters(param_1,uVar3 & 0xfffe,2,0);
  if (uVar2 != 0x3f) {
    local_74 = uVar2 & 0xffff;
    if (2 < DebugLevel) {
      printk("eFuseWriteRegisters BlkNum = %d\n",uVar2);
    }
LAB_001d2584:
    uVar2 = local_74 << 4;
    puVar7 = auStack_38;
    uVar8 = uVar2;
    do {
      local_3e = (short)uVar8;
      uVar8 = (uVar8 & 0xffff) + 2;
      local_3c = 2;
      local_3a = 0;
      eFuseReadPhysical(param_1,&local_3e,4,&local_3a,2);
      puVar10 = puVar7 + 1;
      *puVar7 = local_3a;
      puVar7 = puVar10;
    } while (puVar10 != auStack_28);
    local_60 = (ushort)uVar2;
    uVar2 = uVar2 & 0xffff;
    uVar8 = uVar4 >> 4;
    local_3e = local_60 + ((ushort)uVar3 & 0xf);
    local_3c = 2;
    local_3a = *(ushort *)((int)local_58 + local_5c);
    *(ushort *)((int)auStack_38 + (uVar3 & 0xe)) = *(ushort *)((int)local_58 + local_5c);
    uVar3 = (~((uVar4 >> 6 ^ uVar4 >> 5 ^ uVar8 ^ uVar4 >> 7) & 1) & 1) << 6;
    bVar12 = false;
    uVar4 = (~((uVar4 >> 6 ^ uVar4 >> 7 ^ uVar4 >> 8 ^ uVar4 >> 9) & 1) & 1) << 7;
    local_60 = (ushort)uVar4 | (ushort)uVar3 | (ushort)uVar8;
    FUN_001d1dac(param_1,&local_3e);
    do {
      uVar5 = local_74 + *(ushort *)(iVar1 + 0xe6);
      local_3e = (short)uVar5;
      if ((uVar5 & 1) == 0) {
        local_3a = local_60;
      }
      else {
        local_3e = local_3e + -1;
        local_64 = (ushort)((uVar4 | uVar3 | uVar8 & 0xff) << 8);
        local_3a = local_64;
      }
      local_3c = 2;
      FUN_001d1dac(param_1,&local_3e);
      puVar7 = auStack_38;
      while( true ) {
        local_3e = (short)uVar2;
        local_3c = 2;
        local_3a = 0;
        eFuseReadPhysical(param_1,&local_3e,4,&local_3a,2);
        puVar10 = puVar7 + 1;
        uVar2 = uVar2 + 2 & 0xffff;
        if (local_3a != *puVar7) break;
        puVar7 = puVar10;
        if (auStack_28 == puVar10) goto LAB_001d2714;
      }
      if (DebugLevel < 3) {
        uVar5 = local_74 + *(ushort *)(iVar1 + 0xe6) & 0xffff;
        if (local_68 < uVar9) goto LAB_001d2714;
LAB_001d2784:
        uVar11 = local_68;
        do {
          EfusePhysicalReadRegisters(param_1,uVar11,2,&local_46);
          if ((local_46 >> 8 == 0) && (uVar2 = (uint)*(ushort *)(iVar1 + 0xe8), uVar2 != uVar11)) {
            iVar6 = 1 - (uint)*(ushort *)(iVar1 + 0xe6);
LAB_001d281c:
            local_74 = uVar11 + iVar6 & 0xffff;
            if (2 < DebugLevel) goto LAB_001d27f8;
            goto LAB_001d2830;
          }
          if ((local_46 & 0xff) == 0) {
            uVar2 = *(ushort *)(iVar1 + 0xe6) - 1;
            if (uVar11 != uVar2) {
              iVar6 = -(uint)*(ushort *)(iVar1 + 0xe6);
              goto LAB_001d281c;
            }
          }
          uVar11 = uVar11 - 2 & 0xffff;
        } while (uVar9 <= uVar11);
      }
      else {
        printk("Not bWriteSuccess BlkNum = %d\n",local_74);
        uVar5 = local_74 + *(ushort *)(iVar1 + 0xe6) & 0xffff;
        if (uVar9 <= local_68) goto LAB_001d2784;
      }
      if (DebugLevel < 3) goto LAB_001d2714;
      local_74 = 0xffff;
LAB_001d27f8:
      printk("Not bWriteSuccess and allocate new BlkNum = %d\n",local_74);
      uVar2 = extraout_r1;
LAB_001d2830:
      if (local_74 == 0xffff) goto joined_r0x001d2b44;
      local_3e = (short)uVar5;
      if ((uVar5 & 1) == 0) {
        local_3c = 2;
        eFuseReadPhysical(param_1,&local_3e,4,&local_3a,2);
        uVar2 = 0;
        uVar5 = 0;
        if ((local_3a & 1) != 0) {
          do {
            uVar2 = uVar5 + 1;
            if (uVar2 == 8) goto LAB_001d2890;
            uVar5 = uVar2;
          } while (((int)(uint)local_3a >> (uVar2 & 0xff) & 1U) != 0);
        }
LAB_001d292c:
        local_3a = local_3a | (ushort)(1 << (uVar2 & 0xff));
      }
      else {
        local_3e = local_3e + -1;
        local_3c = 2;
        eFuseReadPhysical(param_1,&local_3e,4,&local_3a,2);
        uVar2 = 8;
        do {
          if (((int)(uint)local_3a >> (uVar2 & 0xff) & 1U) == 0) goto LAB_001d292c;
          uVar2 = uVar2 + 1;
        } while (uVar2 != 0xf);
      }
LAB_001d2890:
      FUN_001d1dac(param_1,&local_3e);
      if (bVar12) goto LAB_001d2b58;
      bVar12 = true;
      uVar2 = (local_74 & 0xfff) << 4;
      puVar7 = auStack_38;
      uVar5 = uVar2;
      do {
        puVar10 = puVar7 + 1;
        local_3a = *puVar7;
        local_3e = (short)uVar5;
        local_3c = 2;
        FUN_001d1dac(param_1,&local_3e);
        uVar5 = uVar5 + 2 & 0xffff;
        puVar7 = puVar10;
      } while (auStack_28 != puVar10);
    } while( true );
  }
  if (uVar9 <= local_68) {
    uVar2 = local_68;
    do {
      EfusePhysicalReadRegisters(param_1,uVar2,2,&local_46);
      if ((local_46 >> 8 == 0) && (*(ushort *)(iVar1 + 0xe8) != uVar2)) {
        iVar6 = 1 - (uint)*(ushort *)(iVar1 + 0xe6);
LAB_001d29fc:
        local_74 = uVar2 + iVar6 & 0xffff;
        if (DebugLevel < 3) {
          if (local_74 == 0xffff) goto LAB_001d2714;
          goto LAB_001d2584;
        }
        printk("eFuseWriteRegisters BlkNum = %d\n",local_74);
        uVar2 = extraout_r1_01;
        if (local_74 == 0xffff) goto joined_r0x001d2b44;
        goto LAB_001d2584;
      }
      if (((local_46 & 0xff) == 0) && (uVar2 != *(ushort *)(iVar1 + 0xe6) - 1)) {
        iVar6 = -(uint)*(ushort *)(iVar1 + 0xe6);
        goto LAB_001d29fc;
      }
      uVar2 = uVar2 - 2 & 0xffff;
    } while (uVar9 <= uVar2);
  }
  if (2 < DebugLevel) {
    printk("eFuseWriteRegisters BlkNum = %d\n",0xffff);
    uVar2 = extraout_r1_00;
joined_r0x001d2b44:
    if (2 < DebugLevel) {
      printk("eFuseWriteRegisters: out of free E-fuse space!!!\n",uVar2);
    }
  }
  goto LAB_001d2714;
LAB_001d2b58:
  if (-1 < DebugLevel) {
    printk("Efsue Write Failed!!\n");
  }
LAB_001d2714:
  local_5c = local_5c + 2;
  if ((int)local_54 <= local_5c) goto LAB_001d2730;
  goto LAB_001d24dc;
}


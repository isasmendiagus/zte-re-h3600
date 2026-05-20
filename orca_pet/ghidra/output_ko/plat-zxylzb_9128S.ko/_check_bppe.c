// module: plat-zxylzb_9128S.ko
// function: _check_bppe @ 0x1856c
// size: 1172 bytes
//

/* WARNING: Restarted to delay deadcode elimination for space: ram */

void _check_bppe(int param_1)

{
  ushort uVar1;
  uint *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  int iVar9;
  int *piVar10;
  uint uVar11;
  uint *puVar12;
  uint uVar13;
  uint uVar14;
  ushort *puVar15;
  int iVar16;
  ushort *puVar17;
  int local_244;
  uint local_23c;
  undefined4 local_22c;
  ushort local_228 [258];
  
  if (param_1 == 0) {
    puVar2 = (uint *)__kmalloc((u32_BPPE_POOL_SIZE >> 5) << 2,0xd0);
    uVar13 = u32_BPPE_POOL_SIZE;
    normal_bp_bits = puVar2;
    if (puVar2 != (uint *)0x0) {
      local_244 = bppe_va_addr;
      local_23c = u32_BPPE_POOL_SIZE >> 5;
      if (local_23c != 0) {
        __memzero();
      }
      uVar4 = *(uint *)(tm_base + 0x8048);
      uVar5 = *(undefined4 *)(tm_base + 0x8080);
      goto LAB_00018680;
    }
  }
  else {
    puVar2 = (uint *)__kmalloc((u32_JUMBO_BPPE_POOL_SIZE >> 5) << 2,0xd0);
    uVar13 = u32_JUMBO_BPPE_POOL_SIZE;
    jumbo_bp_bits = puVar2;
    if (puVar2 != (uint *)0x0) {
      local_244 = jumbo_bppe_va_addr;
      local_23c = u32_JUMBO_BPPE_POOL_SIZE >> 5;
      if (local_23c != 0) {
        __memzero();
      }
      uVar4 = *(uint *)(tm_base + 0x804c);
      uVar5 = *(undefined4 *)(tm_base + 0x8084);
LAB_00018680:
      piVar10 = &bppe_va_addr;
      uVar6 = uVar4 & 0xffff;
      uVar7 = uVar4 >> 0x10;
      if (uVar7 < uVar6) {
        uVar7 = uVar7 + uVar13;
      }
      printk("bppe ptr 0x%x,bppe cnt 0x%x bp_type 0x%x  \n",uVar4,uVar5,param_1);
      dma_cache_maint(local_244,0x20000,2);
      if (uVar7 == uVar6) {
        iVar9 = 0;
      }
      else {
        iVar16 = 0;
        iVar9 = 0;
        uVar4 = uVar6;
        do {
          uVar1 = *(ushort *)(local_244 + uVar4 * 2);
          uVar14 = (uVar1 & 0xff) << 8 | (uint)(uVar1 >> 8);
          if (uVar14 < uVar13) {
            iVar3 = _test_and_set_bit(uVar14,puVar2);
            if (iVar3 != 0) {
              if (piVar10[0x12] == 0) {
                iVar9 = iVar9 + 1;
                printk("bppe bp %d : repeat @ %u\n",uVar14,uVar4);
              }
              else {
                iVar9 = iVar9 + 1;
                printk("bppe bp %d : repeat @:",uVar14);
                iVar3 = 0;
                uVar11 = uVar6;
                local_22c = piVar10;
                do {
                  iVar3 = iVar3 + 1;
                  uVar1 = *(ushort *)(local_244 + uVar11 * 2);
                  if (uVar14 == ((uVar1 & 0xff) << 8 | (uint)(uVar1 >> 8))) {
                    printk(&_LC3,uVar11);
                  }
                  piVar10 = local_22c;
                  uVar11 = uVar11 + 1;
                  if (uVar13 <= uVar11) {
                    uVar11 = 0;
                  }
                } while (uVar7 - uVar6 != iVar3);
                printk(&_LC4);
              }
            }
          }
          else {
            printk("bppe bp %d invalid\n",uVar14);
          }
          uVar4 = uVar4 + 1;
          iVar16 = iVar16 + 1;
          if (uVar13 <= uVar4) {
            uVar4 = 0;
          }
        } while (iVar16 != uVar7 - uVar6);
      }
      local_244 = iVar9;
      if (param_1 == 0) {
        puVar8 = (uint *)(tm_base + 0x8088);
      }
      else {
        puVar8 = (uint *)(tm_base + 0x808c);
      }
      uVar4 = *puVar8 & 0x1ff;
      printk("bppi cnt 0x%x\n",uVar4);
      if (uVar4 != 0) {
        puVar17 = (ushort *)((int)&local_22c + 2);
        uVar7 = 0;
        puVar15 = puVar17;
        do {
          if (param_1 == 0) {
            iVar9 = pon_tm_bmu_alloc_bp();
          }
          else {
            iVar9 = pon_tm_bmu_alloc_jumbo_bp();
          }
          if (iVar9 < 0) {
            printk("alloc bp failed\n");
            if (uVar7 == 0) goto LAB_000187ec;
            break;
          }
          uVar7 = uVar7 + 1;
          puVar15 = puVar15 + 1;
          *puVar15 = (ushort)iVar9;
        } while (uVar4 != uVar7);
        uVar4 = 0;
        do {
          puVar17 = puVar17 + 1;
          uVar6 = (uint)*puVar17;
          if (uVar6 < uVar13) {
            iVar9 = _test_and_set_bit(uVar6,puVar2);
            if (iVar9 != 0) {
              local_244 = local_244 + 1;
              printk("bppi bp %d : repeat\n",uVar6);
            }
          }
          else {
            printk("bppi bp %d invalid\n",uVar6);
          }
          uVar4 = uVar4 + 1;
          pp_bmu_free_bp(uVar6,0,param_1);
        } while (uVar4 != uVar7);
      }
LAB_000187ec:
      if (local_23c == 0) {
        iVar9 = 0;
      }
      else {
        iVar9 = 0;
        iVar16 = 0;
        puVar8 = puVar2;
        do {
          puVar12 = puVar8 + 1;
          uVar4 = *puVar8;
          if (uVar4 == 0xfffffff) {
            iVar9 = iVar9 + 0x20;
          }
          else {
            uVar7 = 0;
            while( true ) {
              if ((uVar4 & 1 << (uVar7 & 0xff)) == 0) {
                printk("bp %u miss\n",iVar16 + uVar7);
              }
              else {
                iVar9 = iVar9 + 1;
              }
              uVar7 = uVar7 + 1;
              if (uVar7 == 0x20) break;
              uVar4 = *puVar8;
            }
          }
          iVar16 = iVar16 + 0x20;
          puVar8 = puVar12;
        } while (puVar12 != puVar2 + local_23c);
      }
      if (param_1 == 0) {
        printk("%s bp total %u miss %d repeat %d\n","normal",iVar9,uVar13 - iVar9,local_244);
        iVar9 = piVar10[0x11];
      }
      else {
        printk("%s bp total %u miss %d repeat %d\n","jumbo",iVar9,uVar13 - iVar9,local_244);
        iVar9 = piVar10[0x10];
      }
      kfree(iVar9);
      return;
    }
  }
  return;
}


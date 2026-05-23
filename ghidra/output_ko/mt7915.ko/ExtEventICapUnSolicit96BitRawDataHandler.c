// module: mt7915.ko
// function: ExtEventICapUnSolicit96BitRawDataHandler @ 0x1a6c1c
// size: 940 bytes
//

void ExtEventICapUnSolicit96BitRawDataHandler(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  bVar1 = *(byte *)(iVar2 + 0x164);
  iVar7 = *(int *)(iVar2 + 0x160);
  iVar8 = *(int *)(iVar2 + 0x178);
  if (2 < DebugLevel) {
    printk("%s----------------->\n","ExtEventICapUnSolicit96BitRawDataHandler");
  }
  if (*(uint *)(param_1 + 0xa78a64) < *(uint *)(param_2 + 4)) {
    if (-1 < DebugLevel) {
      printk(&_LC41,"ExtEventICapUnSolicit96BitRawDataHandler");
      return;
    }
  }
  else {
    uVar6 = (uint)((int)((ulonglong)(uint)bVar1 * 0xaaaaaaab >> 0x20) << 0x17) >> 0x18;
    iVar8 = uVar6 * iVar8 * 4;
    if ((((*(int *)(param_1 + 0xa78a88) == 0) &&
         (iVar5 = os_alloc_mem(param_1,param_1 + 0xa78a88,iVar8), iVar5 != 0)) ||
        ((*(int *)(param_1 + 0xa78a8c) == 0 &&
         (iVar5 = os_alloc_mem(param_1,param_1 + 0xa78a8c,iVar8), iVar5 != 0)))) ||
       ((*(int *)(param_1 + 0xa78a90) == 0 &&
        (iVar5 = os_alloc_mem(param_1,param_1 + 0xa78a90,iVar8), iVar5 != 0)))) {
      if (DebugLevel < 0) {
        return;
      }
      printk("%s : Not enough memory for dynamic allocating !!\n",
             "ExtEventICapUnSolicit96BitRawDataHandler");
    }
    else {
      if (((*(int *)(param_1 + 0xa78a6c) == 0) && (*(int *)(param_1 + 0xa78a70) == 0)) &&
         (*(int *)(param_1 + 0xa78a74) == 0)) {
        os_zero_mem(*(undefined4 *)(param_1 + 0xa78a88),iVar8);
        os_zero_mem(*(undefined4 *)(param_1 + 0xa78a8c),iVar8);
        os_zero_mem(*(undefined4 *)(param_1 + 0xa78a90),iVar8);
      }
      if (uVar6 != 0) {
        uVar3 = 0;
        do {
          while (uVar4 = *(uint *)(param_2 + 8), uVar4 == *(byte *)(*(int *)(iVar7 + 0x13) + uVar3))
          {
            iVar5 = *(int *)(param_1 + 0xa78a6c);
            iVar8 = 0;
            do {
              iVar9 = iVar8 + 0xc;
              iVar8 = iVar8 + 1;
              *(undefined4 *)(*(int *)(param_1 + 0xa78a88) + iVar5 * 4) =
                   *(undefined4 *)(param_2 + iVar9 * 4);
              iVar5 = *(int *)(param_1 + 0xa78a6c) + 1;
              *(int *)(param_1 + 0xa78a6c) = iVar5;
            } while (iVar8 != 0x100);
            uVar3 = uVar3 + 1;
            if (uVar6 == uVar3) goto LAB_001a6d70;
          }
          if (uVar4 == *(byte *)(*(int *)(iVar7 + 0x17) + uVar3)) {
            iVar5 = *(int *)(param_1 + 0xa78a70);
            iVar8 = 0;
            do {
              iVar9 = iVar8 + 0xc;
              iVar8 = iVar8 + 1;
              *(undefined4 *)(*(int *)(param_1 + 0xa78a8c) + iVar5 * 4) =
                   *(undefined4 *)(param_2 + iVar9 * 4);
              iVar5 = *(int *)(param_1 + 0xa78a70) + 1;
              *(int *)(param_1 + 0xa78a70) = iVar5;
            } while (iVar8 != 0x100);
          }
          else if (uVar4 == *(byte *)(*(int *)(iVar7 + 0x1b) + uVar3)) {
            iVar5 = *(int *)(param_1 + 0xa78a74);
            iVar8 = 0;
            do {
              iVar9 = iVar8 + 0xc;
              iVar8 = iVar8 + 1;
              *(undefined4 *)(*(int *)(param_1 + 0xa78a90) + iVar5 * 4) =
                   *(undefined4 *)(param_2 + iVar9 * 4);
              iVar5 = *(int *)(param_1 + 0xa78a74) + 1;
              *(int *)(param_1 + 0xa78a74) = iVar5;
            } while (iVar8 != 0x100);
          }
          uVar3 = uVar3 + 1;
        } while (uVar6 != uVar3);
      }
LAB_001a6d70:
      iVar7 = 0;
      do {
        if (2 < DebugLevel) {
          printk(&_LC59,*(undefined4 *)(param_2 + (iVar7 + 0xc) * 4));
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 != 0x100);
      iVar7 = *(int *)(param_1 + 0xa78a64) + 1;
      *(int *)(param_1 + 0xa78a64) = iVar7;
      if (iVar7 == *(int *)(*(int *)(iVar2 + 0x160) + *(int *)(param_1 + 0xa78a78) * 0x1f + 0xc)) {
        if (*(int *)(param_1 + 0xa78a78) + 1U == (uint)bVar1) {
          ExtEventICap96BitDataParser(param_1);
        }
        *(undefined4 *)(param_1 + 0xa78a64) = 0;
        complete(param_1 + 0xa78abc);
      }
    }
    if ((0 < DebugLevel) &&
       (printk("%s:(Status = %d)\n","ExtEventICapUnSolicit96BitRawDataHandler",
               *(undefined4 *)(param_1 + 0xa78a50)), 2 < DebugLevel)) {
      printk("%s<-----------------\n","ExtEventICapUnSolicit96BitRawDataHandler");
      return;
    }
  }
  return;
}


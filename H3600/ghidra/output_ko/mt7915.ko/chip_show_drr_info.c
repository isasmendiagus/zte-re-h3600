// module: mt7915.ko
// function: chip_show_drr_info @ 0x18b088
// size: 1324 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 chip_show_drr_info(int param_1)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint *puVar8;
  char *pcVar9;
  uint auStack_144 [8];
  undefined4 local_124;
  undefined1 uStack_121;
  char local_120 [256];
  char acStack_20 [4];
  
  auStack_144[1] = 0;
  iVar4 = *(int *)(param_1 + 0x4328);
  auStack_144[2] = 0;
  auStack_144[3] = 0;
  auStack_144[4] = 0;
  auStack_144[5] = 0;
  auStack_144[6] = 0;
  auStack_144[7] = 0;
  local_124 = 0;
  if (0 < DebugLevel) {
    printk("DRR Table STA Info:\n");
  }
  uVar5 = 0;
  do {
    memset(local_120,0,0x100);
    hw_io_write32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0388,uVar5 | 0x80220000);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0350,auStack_144 + 1);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0354,auStack_144 + 2);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0358,auStack_144 + 3);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c035c,auStack_144 + 4);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0690,auStack_144 + 5);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0694,auStack_144 + 6);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0698,auStack_144 + 7);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c069c,&stack0xfffffedc);
    bVar1 = false;
    pcVar9 = local_120;
    puVar8 = auStack_144;
    do {
      puVar8 = puVar8 + 1;
      uVar2 = *puVar8;
      if (uVar2 != 0) {
        uVar3 = 0;
        do {
          if ((uVar2 & 1 << (uVar3 & 0xff)) >> (uVar3 & 0xff) != 0) {
            pcVar9[uVar3] = '\x01';
            bVar1 = true;
          }
          uVar3 = uVar3 + 1;
        } while (uVar3 != 0x20);
      }
      pcVar9 = pcVar9 + 0x20;
    } while (pcVar9 != acStack_20);
    if (bVar1) {
      if (0 < DebugLevel) {
        printk("\tDL AC%02d Queue Non-Empty STA:\n",uVar5);
      }
      pcVar9 = &uStack_121;
      iVar7 = 0;
      iVar6 = DebugLevel;
      do {
        pcVar9 = pcVar9 + 1;
        if ((*pcVar9 != '\0') && (0 < iVar6)) {
          printk(&_LC102,iVar7);
          iVar6 = DebugLevel;
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 != 0x100);
      if (0 < iVar6) {
        printk(&_LC12);
      }
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 != 0x10);
  do {
    memset(local_120,0,0x100);
    hw_io_write32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0388,uVar5 | 0x80220000);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0350,auStack_144 + 1);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0354,auStack_144 + 2);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0358,auStack_144 + 3);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c035c,auStack_144 + 4);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0690,auStack_144 + 5);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0694,auStack_144 + 6);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0698,auStack_144 + 7);
    hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c069c,&stack0xfffffedc);
    bVar1 = false;
    pcVar9 = local_120;
    puVar8 = auStack_144;
    do {
      puVar8 = puVar8 + 1;
      uVar2 = *puVar8;
      if (uVar2 != 0) {
        uVar3 = 0;
        do {
          if ((uVar2 & 1 << (uVar3 & 0xff)) >> (uVar3 & 0xff) != 0) {
            pcVar9[uVar3] = '\x01';
            bVar1 = true;
          }
          uVar3 = uVar3 + 1;
        } while (uVar3 != 0x20);
      }
      pcVar9 = pcVar9 + 0x20;
    } while (pcVar9 != acStack_20);
    if (bVar1) {
      if (0 < DebugLevel) {
        printk("\tUL AC%02d Queue Non-Empty STA:\n",uVar5);
      }
      pcVar9 = &uStack_121;
      iVar7 = 0;
      iVar6 = DebugLevel;
      do {
        pcVar9 = pcVar9 + 1;
        if ((*pcVar9 != '\0') && (0 < iVar6)) {
          printk(&_LC102,iVar7);
          iVar6 = DebugLevel;
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 != 0x100);
      if (0 < iVar6) {
        printk(&_LC12);
      }
    }
    uVar5 = uVar5 + 1;
  } while (uVar5 != 0x20);
  uVar5 = 0;
LAB_0018b3b8:
  hw_io_write32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0388,uVar5 | 0x80420000);
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0350,auStack_144 + 1);
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0354,auStack_144 + 2);
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0358,auStack_144 + 3);
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c035c,auStack_144 + 4);
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0690,auStack_144 + 5);
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0694,auStack_144 + 6);
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c0698,auStack_144 + 7);
  hw_io_read32(*(undefined4 *)(iVar4 + 0xa797a0),0x820c069c,&stack0xfffffedc);
  if (0 < DebugLevel) {
    printk("\nBSSGrp[%d]:\n",uVar5);
  }
  iVar7 = 1;
  iVar6 = 0;
  do {
    if (DebugLevel < 1) {
      if (iVar6 != 3) goto LAB_0018b4b4;
LAB_0018b54c:
      if (0 < DebugLevel) {
        printk(&_LC12);
      }
    }
    else {
      printk("0x%08X ",auStack_144[iVar6 + 1]);
      if (iVar6 == 3) goto LAB_0018b54c;
LAB_0018b4b4:
      if (iVar7 == 8) break;
    }
    iVar6 = iVar6 + 1;
    iVar7 = iVar7 + 1;
  } while( true );
  uVar5 = uVar5 + 1;
  if (uVar5 == 0x10) {
    return 1;
  }
  goto LAB_0018b3b8;
}


// module: mt7915.ko
// function: mt7915_rxv_dump_show_rpt @ 0x17afec
// size: 548 bytes
//

undefined4 mt7915_rxv_dump_show_rpt(int param_1)

{
  char cVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int local_30;
  uint local_2c [2];
  
  iVar4 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  local_30 = 0;
  local_2c[0] = 0;
  iVar4 = (((uint)*(byte *)(iVar4 + 0x218) * 0x10 + 0x24 & 0xff) +
          (*(byte *)(iVar4 + 0x215) + 6 & 0xff) + (uint)(byte)(*(char *)(iVar4 + 0x216) + 6)) * 4;
  iVar5 = os_alloc_mem(param_1,&local_30,iVar4);
  if (iVar5 == 0) {
    bVar2 = *(byte *)(param_1 + 0xa7c21c);
    bVar3 = *(byte *)(param_1 + 0xa7c21d);
    uVar9 = (uint)bVar2 - (uint)*(byte *)(param_1 + 0xa7c21e);
    cVar1 = (char)uVar9;
    iVar5 = local_30;
    while (local_30 = iVar5, (int)cVar1 < (int)(uint)bVar2) {
      uVar9 = uVar9 & 0xff;
      uVar10 = uVar9;
      if (cVar1 < 0) {
        uVar10 = uVar9 + bVar3 & 0xff;
      }
      mt7915_rxv_dump_rxv_content_compose(param_1,uVar10,iVar5,local_2c);
      uVar8 = local_2c[0] >> 2;
      if ((local_2c[0] & 3) != 0) {
        uVar8 = uVar8 + 1;
      }
      if (DebugLevel < 1) {
        if (uVar8 != 0) {
LAB_0017b0e4:
          uVar10 = 0;
          iVar7 = DebugLevel;
          do {
            if (((0 < iVar7) &&
                (printk("DW[%04d]: 0x%08X  ",uVar10,*(undefined4 *)(iVar5 + uVar10 * 4)),
                iVar7 = DebugLevel, (uVar10 & 3) == 3)) && (0 < DebugLevel)) {
              printk(&_LC43);
              iVar7 = DebugLevel;
            }
            uVar10 = uVar10 + 1;
          } while (uVar10 < uVar8);
          goto LAB_0017b0fc;
        }
      }
      else {
        printk("entry_idx: %d\n",uVar10);
        iVar7 = DebugLevel;
        if (uVar8 != 0) goto LAB_0017b0e4;
LAB_0017b0fc:
        if (0 < iVar7) {
          printk(&_LC43);
        }
      }
      os_zero_mem(local_30,iVar4);
      uVar9 = uVar9 + 1;
      iVar5 = local_30;
      cVar1 = (char)uVar9;
    }
    os_free_mem(iVar5);
    uVar6 = 0;
  }
  else if (DebugLevel < 0) {
    uVar6 = 1;
  }
  else {
    printk("%s(): allocate memory fail.\n","mt7915_rxv_dump_show_rpt");
    uVar6 = 1;
  }
  return uVar6;
}


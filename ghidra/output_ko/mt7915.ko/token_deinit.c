// module: mt7915.ko
// function: token_deinit @ 0x1d47ec
// size: 608 bytes
//

undefined4 token_deinit(undefined4 *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  byte *pbVar4;
  uint uVar5;
  uint uVar6;
  int *piVar7;
  int iVar8;
  
  pbVar4 = (byte *)*param_1;
  if (pbVar4 == (byte *)0x0) {
    uVar1 = 0xffffffff;
  }
  else {
    uVar2 = (uint)*pbVar4;
    piVar7 = *(int **)(pbVar4 + 0x160);
    if (uVar2 != 0) {
      uVar5 = 0;
      do {
        while (pbVar4[uVar5 * 0xa8 + 4] != 1) {
          uVar5 = uVar5 + 1 & 0xff;
          if (uVar2 <= uVar5) goto LAB_001d491c;
        }
        if (0 < DebugLevel) {
          printk("%s(): %p,%p\n","token_tx_queue_destroy",pbVar4 + uVar5 * 0xa8 + 4,
                 pbVar4 + uVar5 * 0xa8 + 4);
        }
        uVar2 = 0;
        _raw_spin_lock_bh(pbVar4 + uVar5 * 0xa8 + 8);
        pbVar4[uVar5 * 0xa8 + 4] = 0;
        _raw_spin_unlock_bh(pbVar4 + uVar5 * 0xa8 + 8);
        if (*(int *)(pbVar4 + uVar5 * 0xa8 + 0x1c) != 0) {
          do {
            iVar8 = *(int *)(pbVar4 + uVar5 * 0xa8 + 0x28);
            iVar3 = iVar8 + uVar2 * 0x20;
            if (*(int *)(iVar8 + uVar2 * 0x20) != 0) {
              linux_pci_unmap_single
                        (*(undefined4 *)(*piVar7 + 0xc),*(undefined4 *)(iVar3 + 4),
                         *(undefined4 *)(iVar3 + 8),0xff00);
              RTMPFreeNdisPacket(*(undefined4 *)(pbVar4 + 0x160),
                                 *(undefined4 *)(iVar8 + uVar2 * 0x20));
            }
            uVar2 = uVar2 + 1;
          } while (uVar2 < *(uint *)(pbVar4 + uVar5 * 0xa8 + 0x1c));
        }
        uVar6 = uVar5 + 1 & 0xff;
        os_free_mem(*(undefined4 *)(pbVar4 + uVar5 * 0xa8 + 0x24));
        os_free_mem(*(undefined4 *)(pbVar4 + uVar5 * 0xa8 + 0x28));
        uVar2 = (uint)*pbVar4;
        piVar7 = *(int **)(pbVar4 + 0x160);
        uVar5 = uVar6;
      } while (uVar6 < uVar2);
    }
LAB_001d491c:
    if ((*(int *)(pbVar4 + 0x158) != 0) && (*(int *)(pbVar4 + 0x15c) != 0)) {
      uVar2 = 0;
      do {
        iVar3 = *(int *)(pbVar4 + 0x154);
        iVar8 = iVar3 + uVar2 * 0x20;
        linux_pci_unmap_single
                  (*(undefined4 *)(*piVar7 + 0xc),*(undefined4 *)(iVar8 + 0xc),
                   *(undefined4 *)(iVar8 + 4),0xff01);
        if (((*(int *)(iVar8 + 4) + 0x3fU & 0xffffffe0) + 0xc0 & 0xffff) < 0x1001) {
          if (*(int *)(iVar3 + uVar2 * 0x20) != 0) {
            g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + -1;
            uVar5 = *(int *)(iVar3 + uVar2 * 0x20) + 0x40000000U >> 0xc;
            iVar3 = mem_map + uVar5 * 0x20;
            if ((*(uint *)(mem_map + uVar5 * 0x20) & 0x8000) != 0) {
              iVar3 = *(int *)(iVar3 + 0x1c);
            }
            put_page(iVar3);
          }
          iVar3 = *(int *)(pbVar4 + 0x158);
        }
        else {
          os_free_mem(*(undefined4 *)(iVar3 + uVar2 * 0x20));
          iVar3 = *(int *)(pbVar4 + 0x158);
        }
      } while ((iVar3 != 0) && (uVar2 = uVar2 + 1, uVar2 < *(uint *)(pbVar4 + 0x15c)));
    }
    os_free_mem(*(undefined4 *)(pbVar4 + 0x154));
    os_free_mem(pbVar4);
    uVar1 = 0;
    *param_1 = 0;
  }
  return uVar1;
}


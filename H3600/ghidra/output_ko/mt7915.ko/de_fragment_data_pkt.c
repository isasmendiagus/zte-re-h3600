// module: mt7915.ko
// function: de_fragment_data_pkt @ 0xc9f28
// size: 1268 bytes
//

void de_fragment_data_pkt(int param_1,int param_2)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  void *pvVar6;
  uint __n;
  uint uVar7;
  size_t __n_00;
  uint uVar8;
  void *pvVar9;
  void *__src;
  void *__dest;
  bool bVar10;
  
  pvVar6 = *(void **)(param_2 + 0x1c);
  pvVar9 = *(void **)(param_2 + 0x3c);
  __n = (uint)*(ushort *)(param_2 + 0x40);
  __src = *(void **)(param_2 + 0x14);
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  __n_00 = (size_t)*(byte *)(iVar3 + 1);
  iVar3 = hc_get_hif_type(*(undefined4 *)(param_1 + 0xa797a0));
  uVar7 = (uint)*(byte *)(param_2 + 0x22);
  uVar8 = (int)pvVar9 - *(int *)(param_2 + 0x1c);
  if (iVar3 == 2) {
    __n_00 = 0;
  }
  if (uVar7 == 0) {
    if ((*(byte *)((int)pvVar6 + 1) & 4) == 0) {
      if (*(int *)(&DAT_002963b0 + param_1) != 0) goto LAB_000ca0ac;
    }
    else if (*(int *)(&DAT_002963b0 + param_1) != 0) {
      __dest = *(void **)(*(int *)(&DAT_002963b0 + param_1) + 0xcc);
      if ((*(uint *)(param_2 + 0x44) & 0x40000) == 0) {
        *(uint *)(&DAT_002963b4 + param_1) = __n + (uVar8 & 0xff) + __n_00;
        pvVar9 = memmove(__dest,__src,__n_00);
        memmove((void *)((int)pvVar9 + __n_00),pvVar6,*(int *)(&DAT_002963b4 + param_1) - __n_00);
        (&DAT_002963c0)[param_1] = 0;
      }
      else {
        *(uint *)(&DAT_002963b4 + param_1) = __n + __n_00;
        pvVar6 = memmove(__dest,__src,__n_00);
        memmove((void *)((int)pvVar6 + __n_00),pvVar9,*(size_t *)(&DAT_002963b4 + param_1));
        (&DAT_002963c0)[param_1] = 1;
      }
      *(undefined2 *)(&DAT_002963b8 + param_1) = *(undefined2 *)(param_2 + 0x24);
      bVar1 = *(byte *)(param_2 + 0x22);
      *(ushort *)(&DAT_002963ba + param_1) = (ushort)bVar1;
      *(undefined2 *)(&DAT_002963c2 + param_1) = *(undefined2 *)(param_2 + 0x4e);
      if ((*(byte *)(param_2 + 0x72) & 0xfffffff7) - 2 < 3) {
        (&DAT_002963c4)[param_1] = 1;
        (&DAT_002963c5)[param_1] = *(undefined1 *)(param_2 + 0x72);
        uVar5 = *(undefined4 *)(param_2 + 0x7c);
        *(undefined4 *)(&DAT_002963c8 + param_1) = *(undefined4 *)(param_2 + 0x78);
        *(undefined4 *)(&DAT_002963cc + param_1) = uVar5;
      }
      if (bVar1 != 0) {
        printk(&_LC80,0x10fd);
        dump_stack();
      }
      goto LAB_000ca0ac;
    }
    if (3 < DebugLevel) {
      printk("ERR: pAd->FragFrame.pFragPacket is NULL.\n");
    }
  }
  else {
    sVar2 = *(short *)(param_2 + 0x24);
    if (((sVar2 == *(short *)(&DAT_002963b8 + param_1)) &&
        (uVar7 == *(ushort *)(&DAT_002963ba + param_1) + 1)) &&
       (((&DAT_002963c4)[param_1] == '\0' ||
        (((&DAT_002963c5)[param_1] != *(char *)(param_2 + 0x72) ||
         (*(int *)(param_2 + 0x7c) ==
          *(int *)(&DAT_002963cc + param_1) +
          (uint)(0xfffffffe < *(uint *)(&DAT_002963c8 + param_1)) &&
          *(int *)(param_2 + 0x78) == *(uint *)(&DAT_002963c8 + param_1) + 1)))))) {
      iVar3 = *(int *)(&DAT_002963b4 + param_1);
      if (__n_00 + 0x92a < __n + iVar3) {
        bVar10 = -1 < DebugLevel;
        *(undefined4 *)(&DAT_002963b4 + param_1) = 0;
        *(undefined2 *)(&DAT_002963b8 + param_1) = 0;
        *(undefined4 *)(&DAT_002963bc + param_1) = 0;
        (&DAT_002963c5)[param_1] = 0;
        *(undefined2 *)(&DAT_002963ba + param_1) = 0;
        *(undefined2 *)(&DAT_002963c2 + param_1) = 0;
        *(undefined4 *)(&DAT_002963c8 + param_1) = 0;
        *(undefined4 *)(&DAT_002963cc + param_1) = 0;
        (&DAT_002963c4)[param_1] = 0;
        if (bVar10) {
          printk("Fragment frame is too large, it exeeds the maximum frame size.\n");
        }
      }
      else {
        iVar4 = memcmp(pvVar9,&SNAP_802_1H,6);
        if (iVar4 == 0) {
          if (-1 < DebugLevel) {
            printk("Find another LLC at Middle or End fragment(SN=%d, Frag=%d)\n",sVar2,uVar7);
          }
        }
        else {
          memmove((void *)(*(int *)(*(int *)(&DAT_002963b0 + param_1) + 0xcc) + iVar3),pvVar9,__n);
          *(uint *)(&DAT_002963b4 + param_1) = __n + *(int *)(&DAT_002963b4 + param_1);
          *(ushort *)(&DAT_002963ba + param_1) = (ushort)*(byte *)(param_2 + 0x22);
          uVar5 = *(undefined4 *)(param_2 + 0x7c);
          *(undefined4 *)(&DAT_002963c8 + param_1) = *(undefined4 *)(param_2 + 0x78);
          *(undefined4 *)(&DAT_002963cc + param_1) = uVar5;
          bVar1 = *(byte *)((int)pvVar6 + 1);
          if ((bVar1 & 4) == 0) {
            RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0x38));
            *(uint *)(param_2 + 0x38) = bVar1 & 4;
            iVar3 = RTMP_AllocateFragPacketBuffer(param_1,0xf00);
            if (iVar3 == 0) {
              *(undefined4 *)(&DAT_002963b4 + param_1) = 0;
              *(undefined2 *)(&DAT_002963b8 + param_1) = 0;
              *(undefined2 *)(&DAT_002963ba + param_1) = 0;
              *(undefined4 *)(&DAT_002963bc + param_1) = 0;
              (&DAT_002963c5)[param_1] = 0;
              *(undefined2 *)(&DAT_002963c2 + param_1) = 0;
              *(undefined4 *)(&DAT_002963c8 + param_1) = 0;
              *(undefined4 *)(&DAT_002963cc + param_1) = 0;
              (&DAT_002963c4)[param_1] = 0;
              return;
            }
            iVar4 = *(int *)(&DAT_002963b0 + param_1);
            *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)(iVar4 + 0xcc);
            if ((&DAT_002963c0)[param_1] == '\0') {
              uVar8 = uVar8 & 0xff;
              *(size_t *)(param_2 + 0x3c) = *(int *)(iVar4 + 0xcc) + __n_00 + uVar8;
              *(short *)(param_2 + 0x40) =
                   ((short)*(undefined4 *)(&DAT_002963b4 + param_1) - (short)uVar8) - (short)__n_00;
            }
            else {
              *(size_t *)(param_2 + 0x3c) = *(int *)(iVar4 + 0xcc) + __n_00;
              *(short *)(param_2 + 0x40) =
                   (short)*(undefined4 *)(&DAT_002963b4 + param_1) - (short)__n_00;
            }
            *(int *)(param_2 + 0x38) = iVar4;
            if ((&DAT_002963c0)[param_1] != '\0') {
              *(undefined4 *)(iVar4 + 0xcc) = *(undefined4 *)(param_2 + 0x3c);
              *(uint *)(iVar4 + 100) = (uint)*(ushort *)(param_2 + 0x40);
              *(uint *)(param_2 + 0x44) = *(uint *)(param_2 + 0x44) | 0x40000;
              (&DAT_002963c0)[param_1] = 0;
            }
            *(int *)(&DAT_002963b0 + param_1) = iVar3;
            return;
          }
        }
      }
    }
    else if (2 < DebugLevel) {
      printk("Fragment is not the same SN or out of FN order, %d,%d,%llu - %d,%d,%llu\n",sVar2,uVar7
             ,uVar7,*(undefined4 *)(param_2 + 0x78),*(undefined4 *)(param_2 + 0x7c),
             *(short *)(&DAT_002963b8 + param_1),*(undefined2 *)(&DAT_002963ba + param_1),
             *(undefined4 *)(&DAT_002963c8 + param_1),*(undefined4 *)(&DAT_002963cc + param_1));
    }
  }
LAB_000ca0ac:
  RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0x38));
  *(undefined4 *)(param_2 + 0x38) = 0;
  return;
}


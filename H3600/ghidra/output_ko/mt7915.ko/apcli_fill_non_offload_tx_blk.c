// module: mt7915.ko
// function: apcli_fill_non_offload_tx_blk @ 0x67c2c
// size: 1848 bytes
//

undefined1 apcli_fill_non_offload_tx_blk(int param_1,int param_2,int param_3)

{
  byte bVar1;
  char cVar2;
  undefined1 uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  bool bVar13;
  undefined *local_34;
  
  iVar11 = *(int *)(param_3 + 0xc);
  iVar12 = *(int *)(param_2 + 0x904);
  *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar11 + 0xcc);
  *(undefined4 *)(param_3 + 0x28) = *(undefined4 *)(iVar11 + 100);
  *(undefined2 *)(param_3 + 0x1e) = *(undefined2 *)(iVar11 + 0x42);
  uVar3 = HcGetWmmIdx();
  *(undefined1 *)(param_3 + 0x20) = uVar3;
  uVar3 = *(undefined1 *)(iVar11 + 0x2a);
  *(undefined4 *)(param_3 + 0x30) = *(undefined4 *)(param_3 + 0x24);
  *(undefined1 *)(param_3 + 0x60) = 0;
  *(undefined1 *)(param_3 + 0x1c) = uVar3;
  *(undefined4 *)(param_3 + 0x78) = 0;
  uVar4 = hc_get_asic_cap(*(undefined4 *)(param_1 + 0xa797a0));
  if ((uVar4 & 0x40) == 0) {
LAB_00067cb0:
    uVar4 = *(uint *)(param_3 + 0x18);
  }
  else {
    bVar1 = *(byte *)(param_3 + 5);
    bVar13 = 3 < bVar1;
    if (bVar1 != 4) {
      bVar13 = bVar1 != 1;
    }
    if (bVar13 && (bVar1 != 4 && bVar1 != 2)) goto LAB_00067cb0;
    uVar4 = *(uint *)(param_3 + 0x18) | 0x800000;
    *(uint *)(param_3 + 0x18) = uVar4;
  }
  if (*(char *)(*(int *)(param_3 + 0xc) + 0x2e) == '\0') {
    uVar4 = uVar4 & 0xfffffeff;
  }
  else {
    uVar4 = uVar4 | 0x100;
  }
  *(uint *)(param_3 + 0x18) = uVar4;
  if (**(int **)(param_3 + 8) == 0x400) {
    *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x80000;
    *(int *)(param_3 + 0x50) = param_1 + 0xa1ddc;
    *(undefined4 *)(param_3 + 0x14) = 0;
    *(byte *)(param_1 + 0xa1ddd) = *(byte *)(param_1 + 0xa1ddd) & 0x1f | 0x20;
    **(byte **)(param_3 + 0x50) = **(byte **)(param_3 + 0x50) & 0xc0;
    uVar4 = *(uint *)(param_3 + 0x18) & 0xffffffcd;
    *(uint *)(param_3 + 0x18) = uVar4;
    if (*(char *)(iVar11 + 0x2f) != '\0') {
      *(uint *)(param_3 + 0x18) = uVar4 | 0x40;
    }
    goto LAB_00067dc8;
  }
  uVar4 = (uint)*(ushort *)(param_3 + 0x1e);
  iVar6 = uVar4 * 0x14c0;
  iVar10 = param_1 + iVar6 + 0xa1d20;
  *(int *)(param_3 + 0x50) = param_1 + iVar6 + 0xa1ddc;
  *(int *)(param_3 + 0x14) = iVar10;
  if (iVar10 == 0) {
    if (3 < DebugLevel) {
      printk("%s():Err!! pMacEntry is NULL!!\n","apcli_fill_non_offload_tx_blk");
    }
  }
  else {
    *(undefined4 *)(param_3 + 0x78) = *(undefined4 *)(param_1 + iVar6 + 0xa1e14);
  }
  if (*(char *)(param_1 + (uint)*(byte *)(param_3 + 1) + 0x79511c) == '\0') {
    uVar5 = *(uint *)(param_3 + 0x18) | 2;
  }
  else {
    uVar5 = *(uint *)(param_3 + 0x18) & 0xfffffffd;
  }
  *(uint *)(param_3 + 0x18) = uVar5;
  if (*(char *)(param_1 + 0x286285) == '\x01') {
    iVar6 = uVar4 * 0x14c0 + param_1;
    if (*(char *)(iVar6 + 0xa1e08) == '\0') {
      if (iVar10 == 0) {
        return 0;
      }
      iVar7 = *(int *)(iVar6 + 0xa1d20);
      if (iVar7 == 2 || iVar7 == 0x40001) {
        cVar2 = *(char *)(param_3 + 5);
        bVar13 = cVar2 != '\0';
        if (cVar2 != '\x01') {
          bVar13 = cVar2 != '\x06';
        }
        if (bVar13 && (cVar2 != '\x01' && cVar2 != '\a')) {
          iVar7 = *(int *)(iVar6 + 0xa281c);
          if (((iVar7 == 0) || (*(char *)(iVar7 + 5) != '\x02')) ||
             ((&DAT_0036790d)[param_1] == '\0')) {
            iVar6 = uVar4 * 0x14c0 + param_1;
            iVar7 = MATEngineTxHandle(param_1,iVar11,*(undefined1 *)(iVar6 + 0xa1e04));
            local_34 = &DAT_0036db73 + param_1 + (uint)*(byte *)(iVar6 + 0xa1e04) * 0x2137b0;
LAB_0006803c:
            if (iVar7 == 0) {
              iVar7 = iVar11;
              if ((*(byte *)(iVar11 + 0x72) & 1) != 0) goto LAB_0006826c;
            }
            else {
              RTMPFreeNdisPacket(param_1,iVar11);
              *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar7 + 0xcc);
              uVar8 = *(undefined4 *)(iVar7 + 100);
              *(int *)(param_3 + 0xc) = iVar7;
              *(undefined4 *)(param_3 + 0x28) = uVar8;
            }
LAB_00068078:
            iVar11 = iVar7;
            if (local_34 != (undefined *)0x0) {
              memmove((void *)(*(int *)(iVar7 + 0xcc) + 6),local_34,6);
            }
          }
          else {
            *(undefined *)(param_1 + 0x794b40) = (&DAT_0036790d)[param_1];
            if ((&DAT_00367910)[param_1] != '\x01') {
              iVar7 = MATEngineTxHandle(param_1,iVar11,*(undefined1 *)(iVar7 + 2));
              local_34 = (undefined *)(*(int *)(iVar6 + 0xa281c) + 0x83);
              goto LAB_0006803c;
            }
            if ((*(byte *)(iVar11 + 0x72) & 1) != 0) {
              local_34 = (undefined *)0x0;
LAB_0006826c:
              iVar7 = iVar11;
              if ((*(uint *)(*(int *)(iVar11 + 0xc4) + 0x20) & 0xffff) != 1) {
                iVar7 = skb_copy(iVar11,0x20);
                g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
                RTMPFreeNdisPacket(param_1,iVar11);
                *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(iVar7 + 0xcc);
                uVar8 = *(undefined4 *)(iVar7 + 100);
                *(int *)(param_3 + 0xc) = iVar7;
                *(undefined4 *)(param_3 + 0x28) = uVar8;
              }
              goto LAB_00068078;
            }
          }
          uVar8 = GetStaCfgByWdev(param_1,*(undefined4 *)(uVar4 * 0x14c0 + param_1 + 0xa1d28));
          uVar5 = *(uint *)(param_3 + 0x18) | 0x200;
          *(uint *)(param_3 + 0x18) = uVar5;
          *(undefined4 *)(param_3 + 0x74) = uVar8;
          goto LAB_00067ed0;
        }
      }
      if (iVar7 != 0x20001) {
        return 0;
      }
    }
    else {
      *(int *)(param_3 + 0x14) = iVar10;
      bVar1 = *(byte *)(iVar6 + 0xa1e04);
      uVar5 = uVar5 | 0x8000000;
      *(uint *)(param_3 + 0x18) = uVar5;
      *(undefined **)(param_3 + 0x74) = &DAT_0036db58 + param_1 + (uint)bVar1 * 0x2137b0;
    }
LAB_00067ed0:
    if (((*(uint *)(param_1 + 0x795124) & 0x100) != 0) &&
       ((*(uint *)(uVar4 * 0x14c0 + param_1 + 0xa1dd4) & 1) != 0)) {
      uVar5 = uVar5 | 0x10;
      *(uint *)(param_3 + 0x18) = uVar5;
    }
  }
  if (*(char *)(param_3 + 5) == '\x02') {
    if (((*(byte *)(iVar11 + 0x30) & 0x4b) == 0) && ((*(byte *)(iVar11 + 0x4e) & 2) == 0)) {
      if (*(char *)(param_1 + 0x286285) == '\x01') {
LAB_00068104:
        if ((*(ushort *)(uVar4 * 0x14c0 + param_1 + 0xa1dde) & 0xe03f) == 0) goto LAB_00068124;
      }
      goto LAB_00067f24;
    }
    if ((iVar10 == 0) || (*(char *)(uVar4 * 0x14c0 + param_1 + 0xa2883) == '\0')) {
LAB_00068124:
      *(uint *)(param_3 + 0x18) = uVar5 | 0x80000;
      *(int *)(param_3 + 0x50) = param_1 + 0xa1ddc;
      if (*(int *)(param_3 + 0x14) == 0) {
        if (3 < DebugLevel) {
          printk("%s():Err!! pTxBlk->pMacEntry is NULL!!\n","apcli_fill_non_offload_tx_blk");
          goto LAB_00067f24;
        }
        if (iVar10 != 0) goto LAB_00067f2c;
      }
      else {
        if ((((0x3f < *(byte *)(*(int *)(param_3 + 0x14) + 0xbf)) &&
             (uVar9 = *(uint *)(uVar4 * 0x14c0 + param_1 + 0xa1dd4), (uVar9 & 0x100000) != 0)) &&
            (*(char *)(param_1 + 0x79507d) == '\x01')) && ((uVar9 & 0x200) != 0)) {
          *(uint *)(param_3 + 0x18) = uVar5 & 0xffffffef | 0x80000;
        }
LAB_00067f24:
        if (iVar10 != 0) goto LAB_00067f2c;
        if (3 < DebugLevel) {
          printk("%s():Err!! pMacEntry is NULL!!\n","apcli_fill_non_offload_tx_blk");
        }
      }
    }
    else {
      if (*(char *)(param_1 + 0x286285) == '\x01') goto LAB_00068104;
LAB_00067f2c:
      iVar6 = uVar4 * 0x14c0 + param_1;
      if ((*(byte *)(iVar6 + 0xa1ddd) < 0x40) && ((*(uint *)(iVar6 + 0xa1dd4) & 4) != 0)) {
        *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 4;
      }
    }
    if (*(char *)(iVar11 + 0x2f) != '\0') {
      *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x40;
    }
    if (*(char *)(iVar11 + 0x33) != '\0') {
      *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x800;
    }
  }
  else if (*(char *)(param_3 + 5) == '\x05') {
    *(uint *)(param_3 + 0x18) = uVar5 | 0x20;
  }
  if (iVar10 == 0) {
    if (3 < DebugLevel) {
      printk("%s():Err!! pMacEntry is NULL!!\n","apcli_fill_non_offload_tx_blk");
    }
  }
  else {
    iVar11 = uVar4 * 0x14c0 + param_1;
    *(int *)(iVar11 + 0xa2894) = *(int *)(iVar11 + 0xa2894) + 1;
    iVar11 = *(int *)(iVar11 + 0xa281c);
    if ((iVar11 != 0) && (*(char *)(iVar11 + 5) == '\x02')) {
      *(undefined4 *)(iVar11 + 0x4148) = 0;
    }
  }
LAB_00067dc8:
  *(uint *)(param_1 + 0xa39f9c) = (uint)**(ushort **)(param_3 + 0x50);
  (**(code **)(iVar12 + 0x80))(param_1,param_2,param_3);
  return 1;
}


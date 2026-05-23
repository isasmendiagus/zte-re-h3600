// module: mt7915.ko
// function: MT_ATEComposePkt @ 0x2864fc
// size: 1392 bytes
//

undefined4 MT_ATEComposePkt(int param_1,undefined1 *param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  byte *pbVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined1 *__dest;
  undefined1 *puVar10;
  undefined1 local_2b;
  undefined1 local_2a;
  undefined1 local_29 [5];
  
  iVar1 = net_ad_wrap_service();
  iVar9 = param_3 * 0xd18;
  iVar1 = iVar1 + iVar9;
  pbVar2 = (byte *)hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar8 = (uint)*pbVar2;
  if (param_2 == (undefined1 *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s: NULL buf, band_idx:%u\n","MT_ATEComposePkt",param_3);
    }
    return 1;
  }
  *(undefined4 *)(iVar1 + 0x10f4) = 0;
  *(undefined4 *)(iVar1 + 0x10fc) = 0;
  *(undefined1 *)(iVar1 + 0x1104) = 0;
  *(undefined1 *)(iVar1 + 0x1105) = 0;
  *(undefined1 *)(iVar1 + 0x1106) = 0;
  *(undefined4 *)(iVar1 + 0x1100) = 0;
  if (*(int *)(iVar1 + 0x10f0) != 0) {
    local_2b = 0;
    local_2a = 0;
    local_29[0] = 0;
    iVar5 = mt_ate_get_txlen_by_pkt_tx_time(param_1,param_3);
    iVar3 = net_ad_wrap_service(param_1);
    iVar3 = *(int *)(iVar3 + iVar9 + 0x6dc);
    iVar7 = net_ad_wrap_service(param_1);
    if (iVar5 != 0) {
      iVar3 = iVar5;
    }
    uVar8 = (uint)*(ushort *)(iVar7 + iVar9 + 0x6d6);
    if ((iVar5 == 0) && (-1 < DebugLevel)) {
      printk("%s: Can\'t get txlen by pkt tx time\n","MT_ATEComposePkt");
    }
    uVar4 = mt_ate_get_hlen_by_pkt_tx_time(param_1,param_3,iVar3,&local_2b,&local_2a,local_29);
    if ((uVar4 == 0) && (uVar4 = uVar8, -1 < DebugLevel)) {
      printk("%s: Can\'t get hdrlen by pkt tx time\n","MT_ATEComposePkt");
    }
    *(int *)(iVar1 + 0x10f4) = iVar5;
    *(uint *)(iVar1 + 0x10fc) = uVar4;
    *(undefined1 *)(iVar1 + 0x1104) = local_2b;
    *(undefined1 *)(iVar1 + 0x1105) = local_2a;
    *(undefined1 *)(iVar1 + 0x1106) = local_29[0];
    uVar6 = MT_ATEGenBurstPkt(param_1,param_2,param_3);
    return uVar6;
  }
  if (2 < DebugLevel) {
    printk("%s(wcid:%d)\n","MT_ATEComposePkt",*(undefined2 *)(param_1 + 0xa3b008));
  }
  iVar9 = net_ad_wrap_service(param_1);
  iVar3 = net_ad_wrap_service(param_1);
  iVar3 = *(int *)(iVar3 + param_3 * 0xd18 + 0x6dc);
  if (iVar3 == 0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s: TX length can\'t be 0!!\n","MT_ATEComposePkt");
    return 1;
  }
  iVar5 = mt_ate_get_hlen_by_pkt_tx_time
                    (param_1,param_3,iVar3,iVar1 + 0x1104,iVar1 + 0x1105,iVar1 + 0x1106);
  *(int *)(iVar1 + 0x10fc) = iVar5;
  __dest = param_2 + uVar8;
  __memzero(param_2,0x33ff);
  memmove(__dest,(void *)(iVar9 + param_3 * 0xd18 + 0x511),*(size_t *)(iVar1 + 0x10fc));
  FUN_0027c254(param_1,__dest,param_3,param_4);
  uVar6 = FUN_0027c998(param_1,__dest + iVar5,iVar3 - *(int *)(iVar1 + 0x10fc),param_3);
  if ((*(uint *)(param_1 + 0xa39ffc) & 0x40) == 0) goto LAB_002867bc;
  if (0 < DebugLevel) {
    printk("[TXCONTENT DUMP START]\n");
  }
  asic_dump_tmac_info(param_1,param_2);
  puVar10 = param_2;
  if (DebugLevel < 1) {
    iVar9 = DebugLevel;
    if (uVar8 != 0) {
LAB_00286770:
      do {
        if (0 < iVar9) {
          printk(&_LC203,*puVar10);
          iVar9 = DebugLevel;
        }
        puVar10 = puVar10 + 1;
      } while (puVar10 != __dest);
      goto LAB_00286784;
    }
LAB_0028678c:
    iVar7 = *(int *)(iVar1 + 0x10fc);
    if (iVar3 == iVar7) goto LAB_002867bc;
LAB_00286798:
    uVar8 = 0;
    do {
      if (3 < iVar9) {
        printk(&_LC211,(__dest + iVar5)[uVar8]);
        iVar7 = *(int *)(iVar1 + 0x10fc);
        iVar9 = DebugLevel;
      }
      uVar8 = uVar8 + 1;
    } while (uVar8 < (uint)(iVar3 - iVar7));
  }
  else {
    printk("[TXD RAW]: ");
    iVar9 = DebugLevel;
    if (uVar8 != 0) goto LAB_00286770;
LAB_00286784:
    if (iVar9 < 1) goto LAB_0028678c;
    printk("\nADDR1: %02x:%02x:%02x:%02x:%02x:%02x\n",__dest[4],__dest[5],__dest[6],__dest[7],
           __dest[8],__dest[9]);
    if (0 < DebugLevel) {
      printk("ADDR2: %02x:%02x:%02x:%02x:%02x:%02x\n",__dest[10],__dest[0xb],__dest[0xc],__dest[0xd]
             ,__dest[0xe],__dest[0xf]);
      iVar9 = DebugLevel;
      if (0 < DebugLevel) {
        printk("ADDR3: %02x:%02x:%02x:%02x:%02x:%02x\n",__dest[0x10],__dest[0x11],__dest[0x12],
               __dest[0x13],__dest[0x14],__dest[0x15]);
        if (DebugLevel < 1) goto LAB_00286a58;
        printk("FC: %04x\n",*(undefined2 *)(param_2 + uVar8));
        iVar9 = DebugLevel;
        if (0 < DebugLevel) {
          printk("\tFrom DS: %x\n",((uint)(byte)__dest[1] << 0x1e) >> 0x1f);
          goto LAB_00286a18;
        }
      }
      goto LAB_0028678c;
    }
LAB_00286a18:
    if (0 < DebugLevel) {
      printk("\tTo DS: %x\n",__dest[1] & 1);
      iVar9 = DebugLevel;
      if (DebugLevel < 1) goto LAB_0028678c;
      printk("[CONTENT RAW]: ");
    }
LAB_00286a58:
    iVar7 = *(int *)(iVar1 + 0x10fc);
    iVar9 = DebugLevel;
    if (iVar7 != iVar3) goto LAB_00286798;
  }
  if (0 < iVar9) {
    printk("\n[TXCONTENT DUMP END]\n");
  }
LAB_002867bc:
  iVar1 = net_ad_wrap_service(param_1);
  *(undefined4 *)(param_3 * 0xd18 + iVar1 + 0x4ec) = 0;
  return uVar6;
}


// module: mt7915.ko
// function: mt_ate_ampdu_frame @ 0x285c68
// size: 984 bytes
//

undefined4 mt_ate_ampdu_frame(int param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  uint uVar5;
  int extraout_r1;
  uint uVar6;
  undefined4 uVar7;
  undefined1 *__dest;
  undefined1 *puVar8;
  size_t __n;
  
  iVar2 = net_ad_wrap_service();
  iVar2 = iVar2 + param_3 * 0xd18;
  pbVar3 = (byte *)hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar6 = (uint)*pbVar3;
  iVar4 = net_ad_wrap_service(param_1);
  uVar7 = *(undefined4 *)(iVar2 + 0x10f4);
  if (*(byte *)(iVar4 + param_3 * 0xd18 + 0x1135) < 4) {
    iVar4 = 0xf9c;
  }
  else {
    iVar4 = 0x19c8;
  }
  *(int *)(iVar2 + 0x10f8) = iVar4;
  uVar5 = __aeabi_uidiv(uVar7,iVar4);
  uVar5 = uVar5 & 0xff;
  __aeabi_uidivmod(uVar7,iVar4);
  iVar1 = DebugLevel;
  __n = *(size_t *)(iVar2 + 0x10fc);
  if (extraout_r1 != 0) {
    uVar5 = uVar5 + 1 & 0xff;
  }
  *(uint *)(iVar2 + 0x1100) = uVar5;
  if (2 < iVar1) {
    printk("%s(wcid:%d, txlen/hlen/buf=%d/%d/%p, pkt_tx_len/pkt_msdu_len/pkt_ampdu_cnt=%d/%d/%d)\n",
           "mt_ate_ampdu_frame",*(undefined2 *)(param_1 + 0xa3b008),iVar4,__n,param_2,uVar7,iVar4,
           uVar5);
  }
  __memzero(param_2,0x33ff);
  iVar2 = net_ad_wrap_service(param_1);
  uVar5 = iVar4 - __n;
  __dest = param_2 + uVar6;
  memmove(__dest,(void *)(param_3 * 0xd18 + iVar2 + 0x511),__n);
  FUN_0027c254(param_1,__dest,param_3,0);
  uVar7 = FUN_0027c998(param_1,__dest + __n,uVar5,param_3);
  if ((*(uint *)(param_1 + 0xa39ffc) & 0x40) == 0) goto LAB_00285e28;
  if (0 < DebugLevel) {
    printk("[TXCONTENT DUMP START]\n");
  }
  asic_dump_tmac_info(param_1,param_2);
  puVar8 = param_2;
  if (DebugLevel < 1) {
    iVar2 = DebugLevel;
    if (uVar6 != 0) {
LAB_00285de4:
      do {
        if (0 < iVar2) {
          printk(&_LC203,*puVar8);
          iVar2 = DebugLevel;
        }
        puVar8 = puVar8 + 1;
      } while (puVar8 != __dest);
      goto LAB_00285df8;
    }
LAB_00285e00:
    if (uVar5 == 0) goto LAB_00285e28;
LAB_00285e08:
    uVar6 = 0;
    do {
      if (3 < iVar2) {
        printk(&_LC211,(__dest + __n)[uVar6]);
        iVar2 = DebugLevel;
      }
      uVar6 = uVar6 + 1;
    } while (uVar6 < uVar5);
  }
  else {
    printk("[TXD RAW]: ");
    iVar2 = DebugLevel;
    if (uVar6 != 0) goto LAB_00285de4;
LAB_00285df8:
    if (iVar2 < 1) goto LAB_00285e00;
    printk("\nADDR1: %02x:%02x:%02x:%02x:%02x:%02x\n",__dest[4],__dest[5],__dest[6],__dest[7],
           __dest[8],__dest[9]);
    if (0 < DebugLevel) {
      printk("ADDR2: %02x:%02x:%02x:%02x:%02x:%02x\n",__dest[10],__dest[0xb],__dest[0xc],__dest[0xd]
             ,__dest[0xe],__dest[0xf]);
      iVar2 = DebugLevel;
      if (0 < DebugLevel) {
        printk("ADDR3: %02x:%02x:%02x:%02x:%02x:%02x\n",__dest[0x10],__dest[0x11],__dest[0x12],
               __dest[0x13],__dest[0x14],__dest[0x15]);
        if (DebugLevel < 1) goto LAB_00285ff0;
        printk("FC: %04x\n",*(undefined2 *)(param_2 + uVar6));
        iVar2 = DebugLevel;
        if (0 < DebugLevel) {
          printk("\tFrom DS: %x\n",((uint)(byte)__dest[1] << 0x1e) >> 0x1f);
          goto LAB_00285fb0;
        }
      }
      goto LAB_00285e00;
    }
LAB_00285fb0:
    if (0 < DebugLevel) {
      printk("\tTo DS: %x\n",__dest[1] & 1);
      iVar2 = DebugLevel;
      if (DebugLevel < 1) goto LAB_00285e00;
      printk("[CONTENT RAW]: ");
    }
LAB_00285ff0:
    iVar2 = DebugLevel;
    if (uVar5 != 0) goto LAB_00285e08;
  }
  if (0 < iVar2) {
    printk("\n[TXCONTENT DUMP END]\n");
  }
LAB_00285e28:
  iVar2 = net_ad_wrap_service(param_1);
  *(undefined4 *)(param_3 * 0xd18 + iVar2 + 0x4ec) = 0;
  return uVar7;
}


// module: mt7915.ko
// function: mt_ate_non_ampdu_frame @ 0x286044
// size: 932 bytes
//

undefined4 mt_ate_non_ampdu_frame(int param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  byte *pbVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  int iVar5;
  uint uVar6;
  undefined1 *__dest;
  uint uVar7;
  size_t __n;
  
  iVar1 = net_ad_wrap_service();
  iVar1 = param_3 * 0xd18 + iVar1;
  pbVar2 = (byte *)hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar5 = *(int *)(iVar1 + 0x10f8);
  __n = *(size_t *)(iVar1 + 0x10fc);
  uVar7 = (uint)*pbVar2;
  if (2 < DebugLevel) {
    printk("%s(wcid:%d, txlen/hlen/buf=%d/%d/%p, pkt_tx_len/pkt_msdu_len=%d/%d)\n",
           "mt_ate_non_ampdu_frame",*(undefined2 *)(param_1 + 0xa3b008),iVar5,__n,param_2,
           *(undefined4 *)(iVar1 + 0x10f4),iVar5);
  }
  __memzero(param_2,0x33ff);
  __dest = param_2 + uVar7;
  iVar1 = net_ad_wrap_service(param_1);
  uVar6 = iVar5 - __n;
  memmove(__dest,(void *)(param_3 * 0xd18 + iVar1 + 0x511),__n);
  FUN_0027c254(param_1,__dest,param_3,0);
  uVar3 = FUN_0027c998(param_1,__dest + __n,uVar6,param_3);
  if ((*(uint *)(param_1 + 0xa39ffc) & 0x40) == 0) goto LAB_0028619c;
  if (0 < DebugLevel) {
    printk("[TXCONTENT DUMP START]\n");
  }
  asic_dump_tmac_info(param_1,param_2);
  puVar4 = param_2;
  if (DebugLevel < 1) {
    iVar1 = DebugLevel;
    if (uVar7 != 0) {
LAB_00286158:
      do {
        if (0 < iVar1) {
          printk(&_LC203,*puVar4);
          iVar1 = DebugLevel;
        }
        puVar4 = puVar4 + 1;
      } while (puVar4 != __dest);
      goto LAB_0028616c;
    }
LAB_00286174:
    if (uVar6 == 0) goto LAB_0028619c;
LAB_0028617c:
    uVar7 = 0;
    do {
      if (3 < iVar1) {
        printk(&_LC211,(__dest + __n)[uVar7]);
        iVar1 = DebugLevel;
      }
      uVar7 = uVar7 + 1;
    } while (uVar7 < uVar6);
  }
  else {
    printk("[TXD RAW]: ");
    iVar1 = DebugLevel;
    if (uVar7 != 0) goto LAB_00286158;
LAB_0028616c:
    if (iVar1 < 1) goto LAB_00286174;
    printk("\nADDR1: %02x:%02x:%02x:%02x:%02x:%02x\n",__dest[4],__dest[5],__dest[6],__dest[7],
           __dest[8],__dest[9]);
    if (0 < DebugLevel) {
      printk("ADDR2: %02x:%02x:%02x:%02x:%02x:%02x\n",__dest[10],__dest[0xb],__dest[0xc],__dest[0xd]
             ,__dest[0xe],__dest[0xf]);
      iVar1 = DebugLevel;
      if (0 < DebugLevel) {
        printk("ADDR3: %02x:%02x:%02x:%02x:%02x:%02x\n",__dest[0x10],__dest[0x11],__dest[0x12],
               __dest[0x13],__dest[0x14],__dest[0x15]);
        if (DebugLevel < 1) goto LAB_00286394;
        printk("FC: %04x\n",*(undefined2 *)(param_2 + uVar7));
        iVar1 = DebugLevel;
        if (0 < DebugLevel) {
          printk("\tFrom DS: %x\n",((uint)(byte)__dest[1] << 0x1e) >> 0x1f);
          goto LAB_00286354;
        }
      }
      goto LAB_00286174;
    }
LAB_00286354:
    if (0 < DebugLevel) {
      printk("\tTo DS: %x\n",__dest[1] & 1);
      iVar1 = DebugLevel;
      if (DebugLevel < 1) goto LAB_00286174;
      printk("[CONTENT RAW]: ");
    }
LAB_00286394:
    iVar1 = DebugLevel;
    if (uVar6 != 0) goto LAB_0028617c;
  }
  if (0 < iVar1) {
    printk("\n[TXCONTENT DUMP END]\n");
  }
LAB_0028619c:
  iVar1 = net_ad_wrap_service(param_1);
  *(undefined4 *)(param_3 * 0xd18 + iVar1 + 0x4ec) = 0;
  return uVar3;
}


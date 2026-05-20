// module: wlan_debug_module.ko
// function: periodic_send_pkt @ 0x10020
// size: 676 bytes
//

void periodic_send_pkt(void)

{
  int iVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint *puVar6;
  undefined2 *puVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint *puVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  bool bVar19;
  bool bVar20;
  
  iVar4 = dev_get_by_name(&init_net,g_wlan_debug_trp_xmitdev);
  if (iVar4 == 0) {
    printk("###########get wlan0 net_device fail!!!!!!!!!!!!!!");
    return;
  }
  iVar15 = *(int *)(iVar4 + 300);
  if (0 < g_pkts_per_cycle) {
    iVar14 = 0;
    do {
      while( true ) {
        iVar1 = g_wlan_debug_trp_pktlen;
        iVar11 = __alloc_skb(g_wlan_debug_trp_pktlen + 0x4a,0,0,0xffffffff);
        if (iVar11 != 0) break;
        iVar14 = iVar14 + 1;
        printk("###########alloc skb fail!!!!!!!!!!!!!!");
        if (g_pkts_per_cycle <= iVar14) goto LAB_00010270;
      }
      *(int *)(iVar11 + 0x18) = iVar4;
      *(int *)(iVar11 + 0xcc) = *(int *)(iVar11 + 0xcc) + 0x20;
      *(int *)(iVar11 + 0xc0) = *(int *)(iVar11 + 0xc0) + 0x20;
      puVar5 = (undefined4 *)skb_push(iVar11,0xe);
      puVar6 = (uint *)skb_put(iVar11,0x14);
      *(short *)(iVar11 + 0xa8) = (short)puVar6 - (short)*(undefined4 *)(iVar11 + 200);
      puVar7 = (undefined2 *)skb_put(iVar11,8);
      *(short *)(iVar11 + 0xa6) = (short)puVar7 - (short)*(undefined4 *)(iVar11 + 200);
      skb_put(iVar11,iVar1);
      uVar2 = g_wlan_debug_trp_dstmac._4_2_;
      *puVar5 = (undefined4)g_wlan_debug_trp_dstmac;
      uVar3 = (undefined4)g_wlan_debug_trp_srcmac;
      *(undefined2 *)(puVar5 + 1) = uVar2;
      *(undefined2 *)(puVar5 + 3) = 8;
      uVar2 = g_wlan_debug_trp_srcmac._4_2_;
      *(undefined4 *)((int)puVar5 + 6) = uVar3;
      *(undefined2 *)((int)puVar5 + 10) = uVar2;
      puVar7[2] = (ushort)((iVar1 + 8U & 0xff) << 8) | (ushort)(iVar1 + 8U >> 8) & 0xff;
      *puVar7 = 0x31d4;
      puVar7[1] = 0x3930;
      puVar7[3] = 0;
      *(ushort *)((int)puVar6 + 2) =
           (ushort)((iVar1 + 0x1cU & 0xff) << 8) | (ushort)(iVar1 + 0x1cU >> 8) & 0xff;
      uVar8 = g_wlan_debug_trp_dstip;
      *(undefined1 *)puVar6 = 0x45;
      *(undefined1 *)(puVar6 + 2) = 0x20;
      *(undefined1 *)((int)puVar6 + 1) = 0;
      puVar6[3] = 0x2b01a8c0;
      *(undefined2 *)(puVar6 + 1) = 0;
      *(undefined2 *)((int)puVar6 + 6) = 0;
      *(undefined2 *)((int)puVar6 + 10) = 0;
      *(undefined1 *)((int)puVar6 + 9) = 0x11;
      puVar6[4] = uVar8 << 0x18 | (uVar8 >> 8 & 0xff) << 0x10 | (uVar8 >> 0x10 & 0xff) << 8 |
                  uVar8 >> 0x18;
      uVar8 = *puVar6;
      uVar16 = puVar6[1];
      uVar13 = 0;
      uVar9 = uVar8 + uVar16;
      uVar17 = puVar6[2];
      uVar10 = uVar9 + uVar17 + (uint)CARRY4(uVar8,uVar16);
      uVar18 = puVar6[3];
      puVar12 = puVar6 + 4;
      bVar19 = CARRY4(uVar9,uVar17) || CARRY4(uVar9 + uVar17,(uint)CARRY4(uVar8,uVar16));
      while( true ) {
        bVar20 = CARRY4(uVar10,uVar18) || CARRY4(uVar10 + uVar18,(uint)bVar19);
        uVar10 = uVar10 + uVar18 + (uint)bVar19;
        uVar18 = *puVar12;
        if ((uVar13 & 0xf) == 0) break;
        uVar13 = uVar13 - 1;
        puVar12 = puVar12 + 1;
        bVar19 = bVar20;
      }
      uVar8 = uVar10 + uVar18 + (uint)bVar20 +
              (uint)(CARRY4(uVar10,uVar18) || CARRY4(uVar10 + uVar18,(uint)bVar20));
      *(ushort *)((int)puVar6 + 10) = ~(ushort)(uVar8 + (uVar8 >> 0x10 | uVar8 * 0x10000) >> 0x10);
      iVar14 = iVar14 + 1;
      *(undefined2 *)(iVar11 + 0xa4) = 8;
      *(int *)(iVar11 + 0x18) = iVar4;
      *(byte *)(iVar11 + 0x74) = *(byte *)(iVar11 + 0x74) & 0xf8;
      *(short *)(iVar11 + 0xaa) = *(short *)(iVar11 + 0xa8) + -0xe;
      (**(code **)(iVar15 + 0x10))(iVar11,iVar4);
    } while (iVar14 < g_pkts_per_cycle);
  }
LAB_00010270:
  disableIRQinterrupts();
  iVar15 = coproc_movefrom_Privileged_only_Thread_and_Process_ID();
  *(int *)(iVar15 + *(int *)(iVar4 + 0x280)) = *(int *)(iVar15 + *(int *)(iVar4 + 0x280)) + -1;
  mod_timer(g_dev_xmit_timer,jiffies + 1);
  return;
}


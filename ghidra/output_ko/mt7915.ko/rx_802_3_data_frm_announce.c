// module: mt7915.ko
// function: rx_802_3_data_frm_announce @ 0xcc828
// size: 316 bytes
//

void rx_802_3_data_frm_announce(undefined4 param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined1 *puVar1;
  
  if ((((uint)(*(byte **)(param_3 + 0x1c) != (byte *)0x0) & *(uint *)(param_3 + 0x44) >> 0x14) == 0)
     || ((**(byte **)(param_3 + 0x1c) & 0xc) != 8)) {
    if ((*(uint *)(param_3 + 0x44) & 1) == 0) {
      indicate_802_3_pkt();
      return;
    }
    indicate_ampdu_pkt(param_1,param_3,*(undefined1 *)(param_4 + 0xc));
    return;
  }
  if (DebugLevel < 4) {
    if (*(int *)(param_3 + 0x28) != 0) goto LAB_000cc8a8;
  }
  else {
    printk("%s: CM,\twcid=%d\n","rx_802_3_data_frm_announce",*(undefined2 *)(param_3 + 0x4e));
    puVar1 = *(undefined1 **)(param_3 + 0x28);
    if (puVar1 != (undefined1 *)0x0) {
      if (DebugLevel < 4) goto LAB_000cc8a8;
      printk("Addr1=%02x:%02x:%02x:%02x:%02x:%02x\n",*puVar1,puVar1[1],puVar1[2],puVar1[3],puVar1[4]
             ,puVar1[5]);
    }
  }
  puVar1 = *(undefined1 **)(param_3 + 0x2c);
  if ((puVar1 != (undefined1 *)0x0) && (3 < DebugLevel)) {
    printk("Addr2=%02x:%02x:%02x:%02x:%02x:%02x\n",*puVar1,puVar1[1],puVar1[2],puVar1[3],puVar1[4],
           puVar1[5]);
  }
LAB_000cc8a8:
  RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0x38));
  return;
}


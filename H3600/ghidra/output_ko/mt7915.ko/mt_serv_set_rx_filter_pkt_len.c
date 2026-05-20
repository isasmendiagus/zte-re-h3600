// module: mt7915.ko
// function: mt_serv_set_rx_filter_pkt_len @ 0x25220c
// size: 96 bytes
//

int mt_serv_set_rx_filter_pkt_len(undefined4 *param_1)

{
  int iVar1;
  uint uVar2;
  
  uVar2 = (uint)*(byte *)(param_1 + 0x133);
  iVar1 = (**(code **)(param_1[0x7c4] + 0x38))
                    (*param_1,*(undefined1 *)((int)param_1 + uVar2 * 0xd18 + 0x110b),uVar2,
                     param_1[uVar2 * 0x346 + 0x443]);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_set_rx_filter_pkt_len",iVar1);
  }
  return iVar1;
}


// module: mt7915.ko
// function: mt_serv_set_tx_pkt_with_ibf @ 0x252ed8
// size: 524 bytes
//

undefined4
mt_serv_set_tx_pkt_with_ibf
          (undefined4 *param_1,undefined1 param_2,int param_3,int param_4,char param_5)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  undefined1 local_25;
  char local_24;
  char local_23;
  char local_22;
  char local_21;
  
  uVar3 = (uint)*(byte *)(param_1 + 0x133);
  *(undefined1 *)(param_1 + uVar3 * 0x346 + 0x144) = param_2;
  if (param_4 == 0) {
    cVar1 = *(char *)((int)param_1 + uVar3 * 0xd18 + 0x11ce);
    if (cVar1 == '\0') {
      mt_serv_stop_rx();
      *(undefined1 *)((int)param_1 + uVar3 * 0xd18 + 0x11cd) = 0;
      *(undefined1 *)(param_1 + uVar3 * 0x346 + 0x473) = 0;
      mt_serv_stop_tx(param_1);
      if (param_3 == 0) {
        param_3 = -1;
      }
      param_1[uVar3 * 0x346 + 0x446] = param_3;
      if (param_5 != '\0') {
        local_25 = 1;
        local_24 = cVar1;
        local_23 = cVar1;
        local_22 = cVar1;
        local_21 = cVar1;
        mt_ad_set_txbf_tx_apply(*param_1,&local_25);
        mt_serv_submit_tx(param_1);
      }
      mt_serv_start_tx(param_1);
      printk("%s : None BF Tx!!!!!\n","mt_serv_set_tx_pkt_with_ibf");
      return 0;
    }
    net_ad_set_txbf_profile_tag_read(*param_1,2,1);
    iVar2 = param_1[0x7c4];
    if (*(code **)(iVar2 + 0x1a0) != (code *)0x0) {
      (**(code **)(iVar2 + 0x1a0))(*param_1,1);
      iVar2 = param_1[0x7c4];
    }
    if (*(code **)(iVar2 + 0x19c) != (code *)0x0) {
      (**(code **)(iVar2 + 0x19c))(*param_1,2);
    }
    *(undefined1 *)((int)param_1 + uVar3 * 0xd18 + 0x11ce) = 0;
    printk("%s : fgEBfEverEnabled is enabled and None BF Tx!\n","mt_serv_set_tx_pkt_with_ibf");
  }
  else {
    mt_serv_stop_rx();
    net_ad_set_txbf_profile_tag_read(*param_1,2,1);
    if (*(code **)(param_1[0x7c4] + 0x1a0) != (code *)0x0) {
      (**(code **)(param_1[0x7c4] + 0x1a0))(*param_1,0);
    }
    if (*(code **)(param_1[0x7c4] + 0x19c) != (code *)0x0) {
      (**(code **)(param_1[0x7c4] + 0x19c))(*param_1,2);
    }
    *(undefined1 *)((int)param_1 + uVar3 * 0xd18 + 0x11cd) = 1;
    *(undefined1 *)(param_1 + uVar3 * 0x346 + 0x473) = 1;
    *(undefined1 *)((int)param_1 + uVar3 * 0xd18 + 0x11ce) = 1;
    mt_serv_stop_tx(param_1);
    if (param_3 == 0) {
      param_3 = -1;
    }
    param_1[uVar3 * 0x346 + 0x446] = param_3;
    if (param_5 != '\0') {
      local_25 = 1;
      local_23 = '\x01';
      local_21 = '\x01';
      local_24 = '\0';
      local_22 = '\0';
      mt_ad_set_txbf_tx_apply(*param_1,&local_25);
      mt_serv_submit_tx(param_1);
    }
    mt_serv_start_tx(param_1);
    printk("%s : BF Tx!!!!!\n","mt_serv_set_tx_pkt_with_ibf");
  }
  return 0;
}


// module: mt7915.ko
// function: mt_agent_set_txbf_dut_init_proc @ 0x24e8c0
// size: 860 bytes
//

undefined4 mt_agent_set_txbf_dut_init_proc(undefined4 *param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  char cVar6;
  undefined4 local_54 [2];
  uint local_4c;
  undefined1 auStack_46 [6];
  char acStack_40 [28];
  
  uVar3 = (uint)*(byte *)(param_1 + 0x133);
  puVar5 = (undefined4 *)param_1[0x7c4];
  uVar4 = *param_1;
  local_54[0] = param_2;
  iVar2 = _kstrtol(param_2,10,&local_4c);
  if (iVar2 == 0) {
    printk("%s: cmd ptr = %p\n","mt_agent_set_txbf_dut_init_proc",local_54);
    uVar1 = local_4c;
    snprintf(acStack_40,0x18,"00:%.2x:%.2x:%.2x:%.2x:%.2x",0x11,0x11,0x11,0x11,0x11);
    mt_agent_set_txbf_da(param_1,acStack_40);
    printk("%s: mt_agent_set_txbf_da()!!\n","mt_agent_set_txbf_dut_init_proc");
    snprintf(acStack_40,0x18,"00:%.2x:%.2x:%.2x:%.2x:%.2x",0x22,0x22,0x22,0x22,0x22);
    mt_agent_set_txbf_sa(param_1,auStack_46,acStack_40);
    printk("%s: mt_serv_set_device_info()!!\n","mt_agent_set_txbf_dut_init_proc");
    snprintf(acStack_40,0x18,"00:%.2x:%.2x:%.2x:%.2x:%.2x",0x22,0x22,0x22,0x22,0x22);
    mt_agent_set_txbf_bssid(param_1,acStack_40);
    mt_agent_set_bss_info(param_1,acStack_40);
    printk("%s: mt_agent_set_bss_info()!!\n","mt_agent_set_txbf_dut_init_proc");
    *(undefined1 *)((int)param_1 + uVar3 * 0xd18 + 0x1135) = 2;
    mt_agent_set_bw(param_1,&_LC112);
    *(undefined1 *)(param_1 + uVar3 * 0x346 + 0x44f) = 0;
    param_1[uVar3 * 0x346 + 0x43d] = 900;
    *(undefined1 *)(param_1 + uVar3 * 0x346 + 0x473) = 1;
    *(undefined1 *)((int)param_1 + uVar3 * 0xd18 + 0x11cd) = 1;
    printk("%s: Set txmode, mcs, bw, sgi, ibf and ebf!!\n","mt_agent_set_txbf_dut_init_proc");
    if ((uVar1 & 1) == 0) {
      cVar6 = *(char *)(param_1 + uVar3 * 0x346 + 0x44a);
      if (cVar6 == '\x02') {
        mt_agent_set_txant(param_1,&_LC114);
        mt_agent_set_rxant(param_1,&_LC114);
        *(undefined1 *)(param_1 + uVar3 * 0x346 + 0x44e) = 0xf;
      }
      else if (cVar6 == '\x03') {
        mt_agent_set_txant(param_1,&_LC116);
        mt_agent_set_rxant(param_1,&_LC116);
        *(undefined1 *)(param_1 + uVar3 * 0x346 + 0x44e) = 0x17;
      }
      else {
        mt_agent_set_txant(param_1,&_LC117);
        mt_agent_set_rxant(param_1,&_LC117);
        *(undefined1 *)(param_1 + uVar3 * 0x346 + 0x44e) = 0x1f;
      }
    }
    else {
      if (uVar3 == 0) {
        mt_agent_set_txant(param_1,&_LC114);
        mt_agent_set_rxant(param_1,&_LC114);
      }
      else {
        mt_agent_set_txant(param_1,&_LC115);
        mt_agent_set_rxant(param_1,&_LC115);
      }
      cVar6 = '\0';
      *(undefined1 *)(param_1 + uVar3 * 0x346 + 0x44e) = 0xf;
    }
    *(undefined1 *)((int)param_1 + uVar3 * 0xd18 + 0x11ce) = 0;
    printk("%s: Set tx path = %d\n!!\n","mt_agent_set_txbf_dut_init_proc",cVar6);
    iVar2 = mt_serv_submit_tx(param_1);
    if (iVar2 == 0) {
      printk("%s: mt_serv_submit_tx()!!\n","mt_agent_set_txbf_dut_init_proc");
      if ((code *)*puVar5 == (code *)0x0) {
        uVar4 = 0x205;
      }
      else {
        uVar4 = (*(code *)*puVar5)(uVar4,1,1,uVar3);
        printk("%s: op_set_tr_mac()!!\n","mt_agent_set_txbf_dut_init_proc");
        if ((local_4c & 0x10) == 0) {
          uVar4 = mt_serv_set_ibf_inst_cal_init(param_1);
        }
        printk("%s: mt_serv_set_ibf_inst_cal_init()!!\n","mt_agent_set_txbf_dut_init_proc");
      }
    }
    else {
      uVar4 = 0x100;
    }
  }
  else {
    uVar4 = 0x104;
  }
  return uVar4;
}


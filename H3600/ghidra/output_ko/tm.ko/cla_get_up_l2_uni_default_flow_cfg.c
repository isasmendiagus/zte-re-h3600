// module: tm.ko
// function: cla_get_up_l2_uni_default_flow_cfg @ 0x1210c
// size: 428 bytes
//

undefined4 cla_get_up_l2_uni_default_flow_cfg(uint param_1,uint *param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint local_24;
  uint local_20;
  uint local_1c [2];
  
  local_24 = 0;
  local_20 = 0;
  local_1c[0] = 0;
  if (6 < g_tm_debug_level) {
    printk("[TM][cla_get_up_l2_uni_default_flow_cfg]input: uni_id = %d\n",param_1);
  }
  if (param_1 < 8) {
    iVar3 = tmOnuRegRead(0x17,&local_24,param_1,&claRegTable);
    iVar4 = tmOnuRegRead(0x18,&local_20,param_1,&claRegTable);
    iVar5 = tmOnuRegRead(0x19,local_1c,param_1,&claRegTable);
    if ((iVar4 == 0 && iVar3 == 0) && iVar5 == 0) {
      *param_2 = local_24 >> 0x1f;
      uVar1 = g_tm_debug_level;
      param_2[1] = (local_24 << 1) >> 0x1e;
      param_2[4] = (local_24 << 0xf) >> 0x1b | (local_1c[0] & 1) << 5;
      param_2[3] = (local_24 << 3) >> 0x14;
      param_2[5] = (local_24 << 0x14) >> 0x1d;
      param_2[6] = local_24 & 0x1ff;
      param_2[2] = local_20 & 1;
      if ((uVar1 < 7) ||
         (printk("[TM][cla_get_up_l2_uni_default_flow_cfg]output:\n"), g_tm_debug_level < 7)) {
        return 0;
      }
      printk("del_en = %d, pkt_change_len = %d, gemport_valid = %d, gemport_id/default_uni_port = %d, tcontid_llid = %d, queue_id = %d, flow_id = %d\n"
             ,*param_2,param_2[1],param_2[2],param_2[3],param_2[4],param_2[5],param_2[6]);
      uVar2 = 0;
    }
    else if (g_tm_debug_level == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      printk("[TM][cla_get_up_l2_uni_default_flow_cfg]reg read failed\n");
      uVar2 = 0xffffffff;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar2 = 1;
  }
  else {
    printk("[TM][cla_get_up_l2_uni_default_flow_cfg]input invalid parameter!\n");
    uVar2 = 1;
  }
  return uVar2;
}


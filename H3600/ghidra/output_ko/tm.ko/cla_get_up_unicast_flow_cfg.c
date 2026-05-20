// module: tm.ko
// function: cla_get_up_unicast_flow_cfg @ 0x13524
// size: 348 bytes
//

undefined4 cla_get_up_unicast_flow_cfg(uint *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  uint local_24;
  uint local_20;
  uint local_1c [2];
  
  local_24 = 0;
  local_20 = 0;
  local_1c[0] = 0;
  iVar2 = tmOnuRegRead(0x2e,&local_24,0,&claRegTable);
  iVar3 = tmOnuRegRead(0x2f,&local_20,0,&claRegTable);
  iVar4 = tmOnuRegRead(0x30,local_1c,0,&claRegTable);
  if ((iVar3 == 0 && iVar2 == 0) && iVar4 == 0) {
    *param_1 = local_24 >> 0x1f;
    uVar1 = g_tm_debug_level;
    param_1[1] = (local_24 << 1) >> 0x1e;
    param_1[4] = (local_24 << 0xf) >> 0x1b | (local_1c[0] & 1) << 5;
    param_1[3] = (local_24 << 3) >> 0x14;
    param_1[5] = (local_24 << 0x14) >> 0x1d;
    param_1[6] = local_24 & 0x1ff;
    param_1[2] = local_20 & 1;
    if ((uVar1 < 7) || (printk("[TM][cla_get_up_unicast_flow_cfg]output:\n"), g_tm_debug_level < 7))
    {
      return 0;
    }
    printk("del_en = %d, pkt_change_len = %d, gemport_valid = %d, gemport_id/default_uni_port = %d, tcontid_llid = %d, queue_id = %d, flow_id = %d\n"
           ,*param_1,param_1[1],param_1[2],param_1[3],param_1[4],param_1[5],param_1[6]);
    uVar5 = 0;
  }
  else if (g_tm_debug_level == 0) {
    uVar5 = 0xffffffff;
  }
  else {
    printk("[TM][cla_get_up_unicast_flow_cfg]reg read failed\n");
    uVar5 = 0xffffffff;
  }
  return uVar5;
}


// module: tm.ko
// function: cla_get_dn_l3_default_flow_cfg @ 0x12a90
// size: 344 bytes
//

uint cla_get_dn_l3_default_flow_cfg(uint *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  iVar2 = tmOnuRegRead(0x21,&local_28,0,&claRegTable);
  iVar3 = tmOnuRegRead(0x22,&local_24,0,&claRegTable);
  iVar4 = tmOnuRegRead(0x23,&local_20,0,&claRegTable);
  iVar5 = tmOnuRegRead(0x24,&local_1c,0,&claRegTable);
  if (((iVar3 == 0 && iVar2 == 0) && iVar4 == 0) && iVar5 == 0) {
    *param_1 = local_28 >> 0x1f;
    uVar1 = g_tm_debug_level;
    param_1[1] = (local_28 << 1) >> 0x1e;
    param_1[5] = (local_28 << 0xf) >> 0x1b | (local_20 & 1) << 5;
    uVar6 = local_28;
    if (uVar1 < 7) {
      uVar6 = 0;
    }
    param_1[4] = (local_28 << 3) >> 0x14;
    param_1[6] = (local_28 << 0x14) >> 0x1d;
    param_1[7] = local_28 & 0x1ff;
    param_1[2] = local_1c & 1;
    param_1[3] = local_24 & 1;
    if (6 < uVar1) {
      printk(
            "[TM][cla_get_dn_l3_default_flow_cfg]output: del_en = %d, pkt_change_len = %d, da_known = %d, gemport_valid = %d, gemport_id = %d, tcontid_llid=%d, queue_id = %d, flow_id = %d\n"
            );
      uVar6 = 0;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar6 = 0xffffffff;
  }
  else {
    printk("[TM][cla_get_dn_l3_default_flow_cfg]reg read failed\n");
    uVar6 = 0xffffffff;
  }
  return uVar6;
}


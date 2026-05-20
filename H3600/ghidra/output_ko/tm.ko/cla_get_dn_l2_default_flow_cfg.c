// module: tm.ko
// function: cla_get_dn_l2_default_flow_cfg @ 0x1247c
// size: 356 bytes
//

uint cla_get_dn_l2_default_flow_cfg(uint *param_1)

{
  uint uVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  uint uVar6;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  cVar2 = tmOnuRegRead(0x1a,&local_28,0,&claRegTable);
  cVar3 = tmOnuRegRead(0x1b,&local_24,0,&claRegTable);
  cVar4 = tmOnuRegRead(0x1c,&local_20,0,&claRegTable);
  cVar5 = tmOnuRegRead(0x1d,&local_1c,0,&claRegTable);
  if (((cVar2 == '\0' && cVar3 == '\0') && cVar4 == '\0') && cVar5 == '\0') {
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
            "[TM][cla_get_dn_l2_default_flow_cfg]output: del_en = %d, pkt_change_len = %d, da_known = %d, gemport_valid = %d, gemport_id = %d, tcontid_llid=%d, queue_id = %d, flow_id = %d\n"
            );
      uVar6 = 0;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar6 = 0xffffffff;
  }
  else {
    printk("[TM][cla_get_dn_l2_default_flow_cfg]reg read failed\n");
    uVar6 = 0xffffffff;
  }
  return uVar6;
}


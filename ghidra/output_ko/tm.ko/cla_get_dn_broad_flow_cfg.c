// module: tm.ko
// function: cla_get_dn_broad_flow_cfg @ 0x13250
// size: 324 bytes
//

uint cla_get_dn_broad_flow_cfg(uint *param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint local_20;
  uint local_1c;
  uint local_18;
  uint local_14;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  iVar2 = tmOnuRegRead(0x2a,&local_20,0,&claRegTable);
  iVar3 = tmOnuRegRead(0x2b,&local_1c,0,&claRegTable);
  iVar4 = tmOnuRegRead(0x2c,&local_18,0,&claRegTable);
  iVar5 = tmOnuRegRead(0x2d,&local_14,0,&claRegTable);
  if (((iVar3 == 0 && iVar2 == 0) && iVar4 == 0) && iVar5 == 0) {
    *param_1 = local_14 & 1;
    uVar1 = g_tm_debug_level;
    uVar7 = (local_20 << 0xf) >> 0x1b;
    param_1[2] = (local_20 << 3) >> 0x14;
    uVar6 = uVar7;
    if (uVar1 < 7) {
      uVar6 = 0;
    }
    param_1[3] = uVar7 | (local_18 & 1) << 5;
    param_1[4] = (local_20 << 0x14) >> 0x1d;
    param_1[5] = local_20 & 0x1ff;
    param_1[1] = local_1c & 1;
    if (6 < uVar1) {
      printk(
            "[TM][cla_get_dn_broad_flow_cfg]output:da_known = %d, gemport_valid = %d, gemport_id = %d, tcontid_llid = %d, queue_id = %d, flow_id = %d\n"
            );
      uVar6 = 0;
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar6 = 0xffffffff;
  }
  else {
    printk("[TM][cla_get_dn_broad_flow_cfg]reg read failed\n");
    uVar6 = 0xffffffff;
  }
  return uVar6;
}


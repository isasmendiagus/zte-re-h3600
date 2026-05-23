// module: tm.ko
// function: cla_get_dn_mirror_cfg @ 0x13d58
// size: 184 bytes
//

undefined4 cla_get_dn_mirror_cfg(uint *param_1)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_14 [2];
  
  local_14[0] = 0;
  iVar2 = tmOnuRegRead(0x39,local_14,0,&claRegTable);
  if (iVar2 == 0) {
    *param_1 = (local_14[0] << 9) >> 0x1f;
    uVar1 = g_tm_debug_level;
    param_1[1] = (local_14[0] << 10) >> 0x1b;
    param_1[2] = (local_14[0] << 0x14) >> 0x1d;
    param_1[3] = local_14[0] & 0x1ff;
    uVar3 = 0;
    if (6 < uVar1) {
      printk(
            "[TM][cla_get_dn_mirror_cfg]output: da_known = %d, uni_port = %d, queue_id = %d, flow_id = %d\n"
            );
    }
  }
  else if (g_tm_debug_level == 0) {
    uVar3 = 0xffffffff;
  }
  else {
    printk("[TM][cla_get_dn_mirror_cfg]reg read failed\n");
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


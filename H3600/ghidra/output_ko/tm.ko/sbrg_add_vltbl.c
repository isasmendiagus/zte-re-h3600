// module: tm.ko
// function: sbrg_add_vltbl @ 0x1d748
// size: 464 bytes
//

undefined4 sbrg_add_vltbl(uint param_1,uint param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  bool bVar4;
  uint local_1c [2];
  
  bVar4 = 2 < param_2;
  bVar3 = param_2 == 3;
  if (param_2 < 4) {
    bVar4 = 6 < param_1;
    bVar3 = param_1 == 7;
  }
  local_1c[0] = 0;
  if (0xfff < param_3 || bVar4 && !bVar3) {
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_add_vltbl]input invalid parameter!\n");
      return 1;
    }
    return 1;
  }
  if (6 < g_tm_debug_level) {
    printk("[TM][sbrg_add_vltbl]input:port_id = %d,attri = %d,vlan_id = %d\n",param_1,param_2,
           param_3);
  }
  iVar1 = sbrg_set_indreg_cmd(0,1,4,param_3);
  if (iVar1 == 0) {
    iVar1 = sbrg_access_timeout("sbrg_add_vltbl");
    if ((iVar1 == 0) && (iVar1 = tmOnuRegRead(0x4c,local_1c,0,&sbragRegTable), iVar1 == 0)) {
      uVar2 = param_1 * 2 + 1;
      uVar2 = local_1c[0] & ~(3 << (uVar2 & 0xff)) | param_2 << (uVar2 & 0xff);
      if ((uVar2 & 0x1fffe) == 0) {
        uVar2 = 0;
      }
      else {
        uVar2 = uVar2 | 1;
      }
      iVar1 = sbrg_set_indreg_cmd(0,0,4,param_3);
      if (iVar1 != 0) goto LAB_0001d7b4;
      iVar1 = sbrg_access_timeout("sbrg_add_vltbl");
      if (iVar1 == 0) {
        iVar1 = tmOnuRegWrite(0x4c,uVar2,0,&sbragRegTable);
        if (iVar1 == 0) {
          return 0;
        }
        if (g_tm_debug_level == 0) {
          return 0xffffffff;
        }
        printk("[TM][sbrg_add_vltbl]reg write failed!\n");
        return 0xffffffff;
      }
    }
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_add_vltbl] reg read failed\n");
      return 0xffffffff;
    }
  }
  else {
LAB_0001d7b4:
    if (g_tm_debug_level != 0) {
      printk("[TM][sbrg_add_vltbl] reg write failed\n");
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}


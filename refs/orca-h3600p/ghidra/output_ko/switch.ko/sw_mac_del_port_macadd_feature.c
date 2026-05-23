// module: switch.ko
// function: sw_mac_del_port_macadd_feature @ 0x15428
// size: 496 bytes
//

undefined4 sw_mac_del_port_macadd_feature(uint *param_1)

{
  uint uVar1;
  code cVar2;
  int iVar3;
  undefined4 local_42;
  undefined2 local_3e;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  uint local_30;
  undefined4 local_2c;
  
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  __memzero(&local_42,6);
  local_3e = (undefined2)param_1[1];
  local_42 = *param_1;
  cVar2 = tm_set_p2pmode[param_1[3]];
  if (2 < g_switch_debug_level) {
    printk("[%s] input:\n%s = %2x:%2x:%2x:%2x:%2x:%2x\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n%s = %d\n"
           ,"sw_mac_del_port_macadd_feature","MacEntry.mac",(char)*param_1,
           *(undefined1 *)((int)param_1 + 1),*(undefined1 *)((int)param_1 + 2),
           *(undefined1 *)((int)param_1 + 3),(char)param_1[1],*(undefined1 *)((int)param_1 + 5),
           "MacEntry.vid",param_1[2],"MacEntry.port",(uint)(byte)cVar2,
           "MacEntry.status(0-dyn 1-static)",param_1[4],"MacEntry.smac_ctrl",(char)param_1[5],
           "MacEntry.dmac_ctrl",*(undefined1 *)((int)param_1 + 0x15));
  }
  if ((local_42 & 1) == 0) {
    __memzero(&local_3c,0x14);
    local_30 = param_1[2];
    uVar1 = 1 << (uint)(byte)cVar2;
    local_2c = CONCAT31(local_2c._1_3_,(char)uVar1);
    local_34 = CONCAT13((undefined1)local_42,
                        CONCAT12(local_42._1_1_,CONCAT11(local_42._2_1_,local_42._3_1_)));
    local_38 = CONCAT22(CONCAT11((undefined1)local_3e,local_3e._1_1_),(short)param_1[5]);
    if (2 < g_switch_debug_level) {
      printk("%s = 0x%x\n","MacEntry.port_mask",uVar1 & 0xff);
    }
    if (param_1[4] == 0) {
      local_3c = 0xe;
    }
    else {
      local_3c = 0xf;
    }
    iVar3 = tm_mactable_delete_set(&local_3c);
    if (iVar3 != 0) {
      printk("%s %d failed!\n","sw_mac_del_port_macadd_feature",0x27b);
      return 0xffffffff;
    }
  }
  return 0;
}


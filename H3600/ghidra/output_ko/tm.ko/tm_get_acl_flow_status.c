// module: tm.ko
// function: tm_get_acl_flow_status @ 0x5ec7c
// size: 180 bytes
//

undefined4 tm_get_acl_flow_status(int param_1,undefined4 *param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 local_14 [2];
  
  local_14[0] = 0;
  if (param_2 != (undefined4 *)0x0) {
    if ((*(uint *)(param_1 + 0xc) & 0x1000000) == 0) {
      uVar2 = *(uint *)(param_1 + 8);
      if ((uVar2 & 0x10000) != 0) {
        uVar2 = (uVar2 & 0xffff) + 0x400;
      }
    }
    else {
      uVar2 = (*(uint *)(param_1 + 4) & 0x1ff) + 0x400;
    }
    iVar1 = cla_get_acl_aging_table(uVar2,local_14);
    if (iVar1 == 0) {
      if (TM_CLA_DEBUG != 0) {
        printk("tm_get_acl_flow_status =%d, ruleAddr=%x\n ",local_14[0],uVar2);
      }
      iVar1 = cla_set_acl_aging_table(uVar2,0);
      if (iVar1 == 0) {
        *param_2 = local_14[0];
        return 0;
      }
    }
  }
  return 0xfffffff4;
}


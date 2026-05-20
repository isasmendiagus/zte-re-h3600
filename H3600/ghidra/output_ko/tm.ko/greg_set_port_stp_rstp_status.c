// module: tm.ko
// function: greg_set_port_stp_rstp_status @ 0x32970
// size: 296 bytes
//

undefined4 greg_set_port_stp_rstp_status(uint param_1,uint param_2)

{
  int iVar1;
  int local_14 [2];
  
  local_14[0] = 0;
  if (param_1 < 7) {
    iVar1 = greg_get_port_sel_stp_rstp(param_1,local_14);
    if (iVar1 != 0) {
      if (g_tm_debug_level != 0) {
        printk("[TM][greg_set_port_stp_rstp_status] GREG_READ_REG( failed,ret= %d!\n");
        return 0xffffffff;
      }
      return 0xffffffff;
    }
    if (local_14[0] == 0) {
      if (param_2 < 5) {
LAB_000329f4:
        iVar1 = tmOnuRegWrite(param_1 + 0x2b & 0xff,param_2,0,&gregRegTable);
        if (iVar1 == 0) {
          return 0;
        }
        if (g_tm_debug_level != 0) {
          printk("[TM][greg_set_port_stp_rstp_status] GREG_WRITE_REG( failed,ret= %d!\n");
        }
        return 0xffffffff;
      }
    }
    else if ((local_14[0] != 1) || (param_2 - 1 < 4 && param_2 != 2)) goto LAB_000329f4;
  }
  if (g_tm_debug_level != 0) {
    printk("[TM][greg_set_port_stp_rstp_status] input invalid parameter,port= %d!\n",param_1);
  }
  return 1;
}


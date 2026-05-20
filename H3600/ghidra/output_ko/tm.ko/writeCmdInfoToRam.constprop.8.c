// module: tm.ko
// function: writeCmdInfoToRam.constprop.8 @ 0x58c30
// size: 236 bytes
//

undefined4 writeCmdInfoToRam_constprop_8(undefined1 *param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  if (param_3 == -1 || param_1 == (undefined1 *)0x0) {
    return 0xfffffff4;
  }
  if (param_2 != 0) {
    iVar1 = param_3;
    while( true ) {
      if (1 < g_tm_debug_level) {
        printk("l_tmpAddr:%0x,m_dat_type:%0x,m_last_cmd:%0x,tcp_checksum_up:%0x,ip_checksum_up:%0x,m_cmd:%0x,m_data:%0x\n"
               ,iVar1,*param_1,param_1[1],param_1[2],param_1[3],*(undefined4 *)(param_1 + 4),
               *(undefined2 *)(param_1 + 8));
      }
      iVar2 = iVar1 + 1;
      iVar1 = pp_pm_set_cmd_ram_info
                        (iVar1,*param_1,param_1[1],param_1[2],param_1[3],
                         *(undefined4 *)(param_1 + 4),*(undefined2 *)(param_1 + 8));
      if (iVar1 != 0) break;
      param_1 = param_1 + 0xc;
      iVar1 = iVar2;
      if (iVar2 == param_3 + param_2) {
        return 0;
      }
    }
    printk("uopc set cmd ram failed!\n");
    return 0xfffffff4;
  }
  return 0;
}


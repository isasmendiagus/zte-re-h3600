// module: mt7915.ko
// function: mt_cmd_get_rdd_ipi_hist_rsp @ 0x1ac0d0
// size: 64 bytes
//

void mt_cmd_get_rdd_ipi_hist_rsp(int param_1,void *param_2)

{
  undefined1 *__dest;
  
  __dest = *(undefined1 **)(param_1 + 0xc);
  os_move_mem(__dest,param_2,0x34);
  if (DebugLevel < 3) {
    return;
  }
  printk("%s, ipi_hist_idx: 0x%x\n","mt_cmd_get_rdd_ipi_hist_rsp",*__dest);
  return;
}


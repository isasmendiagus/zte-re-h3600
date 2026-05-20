// module: mt7915.ko
// function: mt_serv_log_on_off @ 0x252074
// size: 304 bytes
//

int mt_serv_log_on_off(undefined4 *param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1[0x7c4] + 0x18))
                    (*param_1,param_1 + (param_2 + -1) * 6 + 0x7d3,param_2,param_3,param_4);
  if (iVar1 != 0) {
    printk("%s: err=0x%08x\n","mt_serv_log_on_off",iVar1);
  }
  printk("%s: log_type=0x%08x\n","mt_serv_log_on_off",param_2);
  if (param_2 == 2) {
    printk("%s: log_ctrl=0x%08x\n","mt_serv_log_on_off",param_3);
    if (param_3 == 0) {
      param_1[0x7d2] = param_1[0x7d2] & 0xfffffffb;
      return iVar1;
    }
    if (param_3 == 1) {
      param_1[0x7d2] = param_1[0x7d2] | 4;
      *(undefined1 *)(param_1 + 0x7da) = 0;
      *(undefined1 *)((int)param_1 + 0x1f6b) = 0;
      param_1[0x7db] = 0;
      printk("%s: log_cb->idx=0x%08x\n","mt_serv_log_on_off",0);
      return iVar1;
    }
  }
  printk("%s log type %d not supported\n","mt_serv_log_on_off",param_2);
  return 0x204;
}


// module: mt7915.ko
// function: ZTE_set_pkt_retry_ctrl @ 0x15ade0
// size: 512 bytes
//

undefined4 ZTE_set_pkt_retry_ctrl(int *param_1,int param_2)

{
  uint uVar1;
  int local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_38 = 0;
  uVar1 = *(uint *)(*param_1 + 0x3c);
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_3c = 0;
  if (param_2 == 0) {
    if (2 < DebugLevel) {
      printk("%s param is null, show info\n","ZTE_set_pkt_retry_ctrl");
    }
    ZTE_show_pkt_ctrl(param_1,0);
    return 1;
  }
  FUN_00156018(param_2,&local_3c,&local_38);
  if (local_3c == 3) {
    if (local_38 < 2) {
      uVar1 = uVar1 & 0xff;
      if (local_38 == 0) {
        *(undefined1 *)((int)param_1 + uVar1 * 0x5834 + 0x2bca46) = 0;
        FUN_00156234(param_1 + uVar1 * 0x160d + 0xaf291);
        return 1;
      }
      if (local_34 < 0x1f) {
        if (local_30 < 0x100) {
          *(undefined1 *)((int)param_1 + uVar1 * 0x5834 + 0x2bca46) = 1;
          FUN_00156234(param_1 + uVar1 * 0x160d + 0xaf291);
          param_1[uVar1 * 0x160d + 0xaf294] = local_34;
          param_1[uVar1 * 0x160d + 0xaf295] = local_30;
          return 1;
        }
        if (-1 < DebugLevel) {
          printk("param=%d value not invalid(%d~%d)\n",local_30,0,0xff);
          return 0xffffffea;
        }
      }
      else if (-1 < DebugLevel) {
        printk("param=%d value not invalid(%d~%d)\n",local_34,0,0x1e);
        return 0xffffffea;
      }
    }
    else if (-1 < DebugLevel) {
      printk("param=%d value not invalid(%d~%d)\n",local_38,0,1);
      return 0xffffffea;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s param error\n","ZTE_set_pkt_retry_ctrl");
    return 0xffffffea;
  }
  return 0xffffffea;
}


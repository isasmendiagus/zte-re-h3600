// module: mt7915.ko
// function: ZTE_set_pkt_power_ctrl @ 0x15b540
// size: 432 bytes
//

undefined4 ZTE_set_pkt_power_ctrl(int *param_1,int param_2)

{
  uint uVar1;
  int local_3c;
  uint local_38;
  uint local_34;
  undefined4 local_30;
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
      printk("%s param is null, show info\n","ZTE_set_pkt_power_ctrl");
    }
    ZTE_show_pkt_ctrl(param_1,0);
    return 1;
  }
  FUN_00156018(param_2,&local_3c,&local_38);
  if (local_3c == 2) {
    if (local_38 < 2) {
      uVar1 = uVar1 & 0xff;
      if (local_38 == 0) {
        *(undefined1 *)((int)param_1 + uVar1 * 0x5834 + 0x2bca49) = 0;
        FUN_00156234(param_1 + uVar1 * 0x160d + 0xaf291);
        return 1;
      }
      if (local_34 < 0x40) {
        *(undefined1 *)((int)param_1 + uVar1 * 0x5834 + 0x2bca49) = 1;
        FUN_00156234(param_1 + uVar1 * 0x160d + 0xaf291);
        param_1[uVar1 * 0x160d + 0xaf29e] = local_34;
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("param=%d value not invalid(%d~%d)\n",local_34,0,0x3f);
        return 0xffffffea;
      }
    }
    else if (-1 < DebugLevel) {
      printk("param=%d value not invalid(%d~%d)\n",local_38,0,1);
      return 0xffffffea;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s param error\n","ZTE_set_pkt_power_ctrl");
    return 0xffffffea;
  }
  return 0xffffffea;
}


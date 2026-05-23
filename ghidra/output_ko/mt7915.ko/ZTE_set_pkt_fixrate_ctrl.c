// module: mt7915.ko
// function: ZTE_set_pkt_fixrate_ctrl @ 0x15afe4
// size: 956 bytes
//

undefined4 ZTE_set_pkt_fixrate_ctrl(int *param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  int local_4c;
  uint local_48;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_48 = 0;
  uVar2 = *(uint *)(*param_1 + 0x3c);
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_4c = 0;
  if (param_2 == 0) {
    if (2 < DebugLevel) {
      printk("%s param is null, show info\n","ZTE_set_pkt_fixrate_ctrl");
    }
    ZTE_show_pkt_ctrl(param_1,0);
    return 1;
  }
  FUN_00156018(param_2,&local_4c,&local_48);
  if (local_4c != 8) {
    if (DebugLevel < 0) {
      return 0xffffffea;
    }
    printk("%s param error\n","ZTE_set_pkt_fixrate_ctrl");
    return 0xffffffea;
  }
  if (1 < local_48) {
    if (DebugLevel < 0) {
      return 0xffffffea;
    }
    printk("param=%d value not invalid(%d~%d)\n",local_48,0,1);
    return 0xffffffea;
  }
  uVar2 = uVar2 & 0xff;
  if (local_48 == 0) {
    *(undefined1 *)((int)param_1 + uVar2 * 0x5834 + 0x2bca47) = 0;
    FUN_00156234(param_1 + uVar2 * 0x160d + 0xaf291);
    return 1;
  }
  if (0xb < local_44) {
    if (DebugLevel < 0) {
      return 0xffffffea;
    }
    printk("param=%d value not invalid(%d~%d)\n",local_44,0,0xb);
    return 0xffffffea;
  }
  if (3 < local_40) {
    if (DebugLevel < 0) {
      return 0xffffffea;
    }
    printk("param=%d value not invalid(%d~%d)\n",local_40,0,3);
    return 0xffffffea;
  }
  switch(local_44) {
  case 0:
    uVar1 = local_3c;
    if (local_3c < 4) break;
    goto LAB_0015b25c;
  case 1:
    if (7 < local_3c) {
      if (DebugLevel < 0) {
        return 0xffffffea;
      }
      printk("param=%d value not invalid(%d~%d)\n",local_3c,0,7);
      return 0xffffffea;
    }
    break;
  case 2:
    if (0xf < local_3c) {
      if (DebugLevel < 0) {
        return 0xffffffea;
      }
      printk("param=%d value not invalid(%d~%d)\n",local_3c,0,0xf);
      return 0xffffffea;
    }
    break;
  default:
    if (0xb < local_3c) {
      if (DebugLevel < 0) {
        return 0xffffffea;
      }
      printk("param=%d value not invalid(%d~%d)\n",local_3c,0,0xb);
      return 0xffffffea;
    }
    break;
  case 4:
    if (9 < local_3c) {
      if (DebugLevel < 0) {
        return 0xffffffea;
      }
      printk("param=%d value not invalid(%d~%d)\n",local_3c,0,9);
      return 0xffffffea;
    }
  }
  uVar1 = local_38;
  if ((local_38 < 4) && (uVar1 = local_34, local_34 < 4)) {
    uVar1 = local_30;
    if ((local_30 < 2) && (uVar1 = local_2c, local_2c < 2)) {
      *(undefined1 *)((int)param_1 + uVar2 * 0x5834 + 0x2bca47) = 1;
      FUN_00156234(param_1 + uVar2 * 0x160d + 0xaf291);
      param_1[uVar2 * 0x160d + 0xaf296] = local_44;
      param_1[uVar2 * 0x160d + 0xaf299] = local_40;
      param_1[uVar2 * 0x160d + 0xaf29b] = local_38;
      param_1[uVar2 * 0x160d + 0xaf29c] = local_3c;
      param_1[uVar2 * 0x160d + 0xaf297] = local_30;
      param_1[uVar2 * 0x160d + 0xaf298] = local_34;
      param_1[uVar2 * 0x160d + 0xaf29a] = local_2c;
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("param=%d value not invalid(%d~%d)\n",uVar1,0,1);
      return 0xffffffea;
    }
  }
  else {
LAB_0015b25c:
    if (-1 < DebugLevel) {
      printk("param=%d value not invalid(%d~%d)\n",uVar1,0,3);
      return 0xffffffea;
    }
  }
  return 0xffffffea;
}


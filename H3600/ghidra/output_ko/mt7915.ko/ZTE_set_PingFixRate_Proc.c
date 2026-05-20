// module: mt7915.ko
// function: ZTE_set_PingFixRate_Proc @ 0x15c310
// size: 952 bytes
//

undefined4 ZTE_set_PingFixRate_Proc(int *param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_2c = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_44 = 0;
  get_wdev_by_ioctl_idx_and_iftype
            (param_1,*(undefined4 *)(*param_1 + 0x3c),*(undefined4 *)(*param_1 + 0x38));
  iVar1 = HcGetBandByWdev();
  if (param_2 == 0) {
    if (2 < DebugLevel) {
      printk("%s param is null, show info\n","ZTE_set_PingFixRate_Proc");
    }
    ZTE_show_PingFixRate(param_1,0);
    return 1;
  }
  FUN_00156018(param_2,&local_44,&local_40);
  if (local_44 == 6) {
    if (1 < local_40) {
      if (DebugLevel < 0) {
        return 0xffffffea;
      }
      printk("param=%d value not invalid(%d~%d)\n",local_40,0,1);
      return 0xffffffea;
    }
    if (local_40 == 0) {
      *(undefined1 *)(param_1 + (int)("MtCmdSetFreqOffset" + iVar1 * 9 + 1)) = 0;
      return 1;
    }
    if (0xb < local_3c) {
      if (DebugLevel < 0) {
        return 0xffffffea;
      }
      printk("param=%d value not invalid(%d~%d)\n",local_3c,0,0xb);
      return 0xffffffea;
    }
    switch(local_3c) {
    case 0:
      if (3 < local_38) {
        if (DebugLevel < 0) {
          return 0xffffffea;
        }
        printk("param=%d value not invalid(%d~%d)\n",local_38,0,3);
        return 0xffffffea;
      }
      break;
    case 1:
      if (7 < local_38) {
        uVar2 = local_38;
        if (DebugLevel < 0) {
          return 0xffffffea;
        }
        goto LAB_0015c534;
      }
      break;
    case 2:
      if (0xf < local_38) {
        if (DebugLevel < 0) {
          return 0xffffffea;
        }
        printk("param=%d value not invalid(%d~%d)\n",local_38,0,0xf);
        return 0xffffffea;
      }
      break;
    default:
      if (0xb < local_38) {
        if (DebugLevel < 0) {
          return 0xffffffea;
        }
        printk("param=%d value not invalid(%d~%d)\n",local_38,0,0xb);
        return 0xffffffea;
      }
      break;
    case 4:
      if (9 < local_38) {
        if (DebugLevel < 0) {
          return 0xffffffea;
        }
        printk("param=%d value not invalid(%d~%d)\n",local_38,0,9);
        return 0xffffffea;
      }
    }
    if (local_34 < 0x1f) {
      if (local_30 < 8) {
        if (local_2c < 2) {
          param_1[(int)("MtCmdSetFreqOffset" + iVar1 * 9 + 2)] = local_3c;
          *(undefined1 *)(param_1 + (int)("MtCmdSetFreqOffset" + iVar1 * 9 + 1)) = 1;
          param_1[(int)("MtCmdSetFreqOffset" + iVar1 * 9 + 3)] = local_38;
          param_1[(int)("MtCmdSetFreqOffset" + iVar1 * 9 + 4)] = local_34;
          param_1[(int)("MtCmdSetFreqOffset" + iVar1 * 9 + 5)] = local_30;
          param_1[(int)("MtCmdSetFreqOffset" + iVar1 * 9 + 6)] = local_2c;
          return 1;
        }
        if (-1 < DebugLevel) {
          printk("param=%d value not invalid(%d~%d)\n",local_2c,0,1);
          return 0xffffffea;
        }
      }
      else {
        uVar2 = local_30;
        if (-1 < DebugLevel) {
LAB_0015c534:
          printk("param=%d value not invalid(%d~%d)\n",uVar2,0,7);
          return 0xffffffea;
        }
      }
    }
    else if (-1 < DebugLevel) {
      printk("param=%d value not invalid(%d~%d)\n",local_34,0,0x1e);
      return 0xffffffea;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s param error\n","ZTE_set_PingFixRate_Proc");
    return 0xffffffea;
  }
  return 0xffffffea;
}


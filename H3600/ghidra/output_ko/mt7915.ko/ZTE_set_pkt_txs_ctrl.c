// module: mt7915.ko
// function: ZTE_set_pkt_txs_ctrl @ 0x15b770
// size: 476 bytes
//

undefined4 ZTE_set_pkt_txs_ctrl(int *param_1,char *param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int local_44;
  uint local_40;
  uint local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_40 = 0;
  uVar3 = *(uint *)(*param_1 + 0x3c);
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_44 = 0;
  if (param_2 == (char *)0x0) {
    if (2 < DebugLevel) {
      printk("%s param is null, show info\n","ZTE_set_pkt_txs_ctrl");
    }
    ZTE_show_pkt_ctrl(param_1,0);
    return 1;
  }
  iVar1 = strcmp(param_2,"clear");
  if (iVar1 == 0) {
    if (2 < DebugLevel) {
      printk("%s clear data\n","ZTE_set_pkt_txs_ctrl");
    }
    ZTE_clear_pkt_stat(param_1,param_2);
    return 1;
  }
  FUN_00156018(param_2,&local_44,&local_40);
  if (local_44 == 2) {
    uVar2 = local_40;
    if (local_40 < 2) {
      uVar3 = uVar3 & 0xff;
      iVar1 = uVar3 * 0x5834;
      if (local_40 == 0) {
        *(undefined1 *)((int)param_1 + iVar1 + 0x2bca4a) = 0;
        *(undefined1 *)((int)param_1 + iVar1 + 0x2bca4b) = 0;
        FUN_00156234(param_1 + uVar3 * 0x160d + 0xaf291);
        return 1;
      }
      uVar2 = local_3c;
      if (local_3c < 2) {
        *(char *)((int)param_1 + iVar1 + 0x2bca4b) = (char)local_3c;
        *(undefined1 *)((int)param_1 + iVar1 + 0x2bca4a) = 1;
        FUN_00156234(param_1 + uVar3 * 0x160d + 0xaf291);
        return 1;
      }
    }
    if (-1 < DebugLevel) {
      printk("param=%d value not invalid(%d~%d)\n",uVar2,0,1);
      return 0xffffffea;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s param error\n","ZTE_set_pkt_txs_ctrl");
    return 0xffffffea;
  }
  return 0xffffffea;
}


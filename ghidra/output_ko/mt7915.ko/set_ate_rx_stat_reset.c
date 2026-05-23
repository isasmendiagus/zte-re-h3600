// module: mt7915.ko
// function: set_ate_rx_stat_reset @ 0x264478
// size: 600 bytes
//

undefined4 set_ate_rx_stat_reset(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: invalid argument (no argument)\n","set_ate_rx_stat_reset");
      return 0;
    }
  }
  else {
    uVar1 = simple_strtol(param_2,0,10);
    uVar1 = uVar1 & 0xff;
    if (uVar1 < 2) {
      if (0 < DebugLevel) {
        printk("%s: band_idx: %d\n","set_ate_rx_stat_reset",uVar1);
      }
      chip_get_rx_stat_band(param_1,uVar1,0,&local_38);
      chip_get_rx_stat_comm(param_1,uVar1,0,&local_54);
      iVar2 = MtCmdSetPhyCounter(param_1,0,uVar1);
      if ((iVar2 == 0) && (iVar2 = MtCmdSetPhyCounter(param_1,1,uVar1), iVar2 == 0)) {
        iVar2 = uVar1 * 0x168;
        puVar6 = (undefined4 *)(param_1 + iVar2 + 0xa7bfd0);
        puVar3 = (undefined4 *)(param_1 + iVar2 + 0xa7bf80);
        puVar4 = (undefined4 *)(param_1 + iVar2 + 0xa7bfe0);
        puVar5 = (undefined4 *)(param_1 + iVar2 + 0xa7bff0);
        iVar2 = 0;
        do {
          iVar2 = iVar2 + 1;
          puVar6 = puVar6 + 1;
          *puVar6 = 0;
          puVar3 = puVar3 + 1;
          *puVar3 = 0xffffff92;
          puVar4 = puVar4 + 1;
          *puVar4 = 0xffffff92;
          puVar5 = puVar5 + 1;
          *puVar5 = 0xffffff92;
        } while (iVar2 != 4);
        param_1 = param_1 + uVar1 * 0x18;
        *(undefined4 *)(param_1 + 0xa7bf10) = 0;
        *(undefined4 *)(param_1 + 0xa7bf18) = 0;
        *(undefined4 *)(param_1 + 0xa7bf1c) = 0;
        *(undefined4 *)(param_1 + 0xa7bf20) = 0;
        *(undefined4 *)(param_1 + 0xa7bf14) = 0;
        *(undefined4 *)(param_1 + 0xa7bf24) = 0;
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: error status(%d) for fw command.\n","set_ate_rx_stat_reset");
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s: invalid band index(%d).\n","set_ate_rx_stat_reset",uVar1);
      return 0;
    }
  }
  return 0;
}


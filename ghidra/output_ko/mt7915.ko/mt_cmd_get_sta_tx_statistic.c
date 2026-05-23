// module: mt7915.ko
// function: mt_cmd_get_sta_tx_statistic @ 0x1b5bc0
// size: 300 bytes
//

int mt_cmd_get_sta_tx_statistic
              (undefined4 param_1,int param_2,undefined1 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 local_54;
  undefined1 local_50;
  undefined1 local_4f;
  byte local_4e;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 local_24;
  
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  os_zero_mem(&local_54,0xc);
  if (3 < DebugLevel) {
    printk("%s: wcid=%d\n","mt_cmd_get_sta_tx_statistic",param_2);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0xc);
  if (iVar1 == 0) {
    iVar1 = 3;
  }
  else {
    local_48 = CONCAT13(0x30,CONCAT12(0xed,(undefined2)local_48));
    local_34 = local_48;
    uStack_30 = local_44;
    uStack_2c = local_40;
    uStack_28 = local_3c;
    local_24 = local_38;
    AndesInitCmdMsg(iVar1,local_48,local_44,local_40,local_3c,local_38);
    local_4e = (byte)((uint)(param_2 << 0x16) >> 0x1e);
    local_50 = (undefined1)param_2;
    local_54 = param_4;
    local_4f = param_3;
    AndesAppendCmdMsg(iVar1,&local_54,0xc);
    iVar1 = chip_cmd_tx(param_1,iVar1);
    if (iVar1 == 0) {
      return 0;
    }
  }
  if (0 < DebugLevel) {
    printk("%s:(ret = %d)\n","mt_cmd_get_sta_tx_statistic",iVar1);
  }
  return iVar1;
}


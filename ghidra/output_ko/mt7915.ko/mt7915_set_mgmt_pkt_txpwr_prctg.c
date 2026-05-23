// module: mt7915.ko
// function: mt7915_set_mgmt_pkt_txpwr_prctg @ 0x1796e4
// size: 244 bytes
//

void mt7915_set_mgmt_pkt_txpwr_prctg(undefined4 param_1,int param_2,int param_3)

{
  undefined1 uVar1;
  
  if (param_2 != 0) {
    if (2 < DebugLevel) {
      printk("%s: [TxdPwrOffset]: %d\n","mt7915_set_mgmt_pkt_txpwr_prctg",
             *(undefined1 *)(param_2 + 0x93c));
    }
    if (param_3 - 0x5bU < 9) {
      uVar1 = 0;
    }
    else if (param_3 - 0x3dU < 0x1e) {
      uVar1 = 0xfe;
    }
    else if (param_3 - 0x1fU < 0x1e) {
      uVar1 = 0xfa;
    }
    else if (param_3 - 0x10U < 0xf) {
      uVar1 = 0xf4;
    }
    else if (param_3 - 10U < 6) {
      uVar1 = 0xee;
    }
    else if (param_3 - 1U < 9) {
      uVar1 = 0xe8;
    }
    else {
      uVar1 = 0;
    }
    *(undefined1 *)(param_2 + 0x93c) = uVar1;
    UpdateBeaconHandler(param_1,param_2,6);
    UpdateBeaconHandler(param_1,param_2,5);
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("%s: wdev NULL\n","mt7915_set_mgmt_pkt_txpwr_prctg");
  return;
}


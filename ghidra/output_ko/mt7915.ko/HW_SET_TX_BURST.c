// module: mt7915.ko
// function: HW_SET_TX_BURST @ 0xb18e0
// size: 172 bytes
//

void HW_SET_TX_BURST(undefined4 param_1,int param_2,undefined1 param_3,undefined1 param_4,
                    undefined2 param_5,undefined1 param_6)

{
  int local_1c;
  undefined1 local_18;
  undefined1 local_17;
  undefined2 local_16;
  undefined1 local_14;
  
  if ((param_2 != 0) && (txop_dynamic_adjust_en != 0)) {
    local_16 = param_5;
    local_14 = param_6;
    local_1c = param_2;
    local_18 = param_4;
    local_17 = param_3;
    if (2 < DebugLevel) {
      printk("<caller: %pS>\n -%s: enable=%x, ac_type=%x, prio=%x, txop=%x\n");
    }
    FUN_000b0a74(param_1,0,0x12,0xc,&local_1c);
  }
  return;
}


// module: mt7915.ko
// function: hw_set_tx_burst @ 0xaf8b0
// size: 120 bytes
//

void hw_set_tx_burst(undefined4 param_1,int param_2,undefined1 param_3,undefined1 param_4,
                    undefined2 param_5,undefined1 param_6)

{
  int local_1c;
  undefined1 local_18;
  undefined1 local_17;
  undefined2 local_16;
  undefined1 local_14;
  
  if (param_2 != 0) {
    local_16 = param_5;
    local_14 = param_6;
    local_1c = param_2;
    local_18 = param_4;
    local_17 = param_3;
    if (2 < DebugLevel) {
      printk("<caller: %pS>\n -%s: prio=%x, level=%x, enable=%x\n");
    }
    FUN_000ae92c(param_1,&local_1c);
  }
  return;
}


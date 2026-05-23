// module: mt7915.ko
// function: hqa_muru_set_ul_tx_trigger @ 0x23f468
// size: 244 bytes
//

undefined4 hqa_muru_set_ul_tx_trigger(undefined4 param_1,int param_2)

{
  char cVar1;
  undefined4 uVar2;
  char *pcVar3;
  
  if (param_2 == 0) {
    uVar2 = 0;
    if (DebugLevel < 0) {
      return 0;
    }
    printk("%s: Argument is NULL\n","hqa_muru_set_ul_tx_trigger");
  }
  else {
    cVar1 = os_str_toul(param_2,0,10);
    if (0 < DebugLevel) {
      pcVar3 = "Enable";
      if (cVar1 != '\x01') {
        pcVar3 = "Disable";
      }
      printk("%s: MU %s %u\n","hqa_muru_set_ul_tx_trigger",pcVar3,cVar1);
    }
    uVar2 = wifi_test_muru_ul_tx_trigger(param_1,cVar1);
  }
  if (0 < DebugLevel) {
    printk("%s: CMD %s\n","hqa_muru_set_ul_tx_trigger");
  }
  return uVar2;
}


// module: mt7915.ko
// function: set_ate_pkt_tx_time @ 0x263d20
// size: 156 bytes
//

bool set_ate_pkt_tx_time(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  if (param_2 != 0) {
    if (0 < DebugLevel) {
      printk("%s: Pkt Tx time=%sus\n","set_ate_pkt_tx_time",param_2);
    }
    uVar1 = simple_strtol(param_2,0,10);
    iVar2 = (**(code **)(iVar2 + 0x60))(param_1,uVar1);
    return iVar2 == 0;
  }
  if (DebugLevel < 0) {
    return false;
  }
  printk("%s: No parameters!!\n","set_ate_pkt_tx_time");
  return false;
}


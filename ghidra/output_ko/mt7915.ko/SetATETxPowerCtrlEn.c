// module: mt7915.ko
// function: SetATETxPowerCtrlEn @ 0x26cb80
// size: 112 bytes
//

undefined4 SetATETxPowerCtrlEn(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  uVar1 = simple_strtol(param_2,0,10);
  if (0 < DebugLevel) {
    printk("%s: fgTxPowerCtrlEn: %d\n","SetATETxPowerCtrlEn",uVar1);
  }
  (**(code **)(iVar2 + 0xe4))(param_1,5,uVar1);
  return 1;
}


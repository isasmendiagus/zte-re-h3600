// module: mt7915.ko
// function: set_ate_duty_cycle @ 0x263c48
// size: 212 bytes
//

undefined4 set_ate_duty_cycle(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0xa39fd4);
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: No parameters!!\n","set_ate_duty_cycle",param_3,DebugLevel,param_4);
      return 0;
    }
  }
  else {
    if (0 < DebugLevel) {
      printk("%s: Duty cycle=%s%%\n","set_ate_duty_cycle",param_2,DebugLevel,param_4);
    }
    uVar1 = simple_strtol(param_2,0,10);
    if ((uVar1 < 0x65) && (iVar2 = (**(code **)(iVar2 + 0x5c))(param_1,uVar1), iVar2 == 0)) {
      return 1;
    }
    if (-1 < DebugLevel) {
      printk("%s: Unexpected input!!\n","set_ate_duty_cycle");
    }
  }
  return 0;
}


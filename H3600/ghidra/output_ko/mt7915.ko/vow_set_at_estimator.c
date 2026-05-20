// module: mt7915.ko
// function: vow_set_at_estimator @ 0x41f58
// size: 304 bytes
//

undefined4 vow_set_at_estimator(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined2 local_74;
  undefined2 local_72;
  undefined1 local_5c;
  undefined2 local_5a;
  
  __memzero(&local_74,100);
  local_72 = (undefined2)param_2;
  local_74 = 1;
  if (param_2 == 1) {
    local_5c = *(undefined1 *)(param_1 + 0xa7a2fc);
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, val = 0x%x)\n","vow_set_at_estimator",1,1,local_5c);
    }
  }
  else if (param_2 == 2) {
    local_5a = *(undefined2 *)(param_1 + 0xa7a2fe);
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, val = 0x%x)\n","vow_set_at_estimator",1,2,local_5a);
    }
  }
  else if (2 < DebugLevel) {
    printk("%s:(No such command = 0x%x)\n","vow_set_at_estimator",param_2);
  }
  uVar1 = MtCmdSetVoWModuleCtrl(param_1,&local_74);
  if (2 < DebugLevel) {
    printk("%s:(ret = %d), sizeof %zu\n","vow_set_at_estimator",uVar1,100);
  }
  return uVar1;
}


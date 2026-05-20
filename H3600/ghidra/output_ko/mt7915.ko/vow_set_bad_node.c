// module: mt7915.ko
// function: vow_set_bad_node @ 0x42200
// size: 444 bytes
//

undefined4 vow_set_bad_node(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  undefined1 auStack_74 [2];
  undefined2 local_72;
  undefined1 local_5c;
  undefined2 local_5a;
  undefined1 local_58;
  undefined1 local_57;
  
  __memzero(auStack_74,100);
  local_72 = (undefined2)param_2;
  switch(param_2) {
  case 1:
    local_5c = *(undefined1 *)(param_1 + 0xa7a300);
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, val = 0x%x)\n","vow_set_bad_node",2,1,local_5c);
    }
    break;
  case 2:
    local_5a = *(undefined2 *)(param_1 + 0xa7a302);
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, val = 0x%x)\n","vow_set_bad_node",2,2,local_5a);
    }
    break;
  case 3:
    local_58 = (undefined1)*(undefined2 *)(param_1 + 0xa7a304);
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, val = 0x%x)\n","vow_set_bad_node",2,3,
             *(undefined2 *)(param_1 + 0xa7a304));
    }
    break;
  case 4:
    local_57 = (undefined1)*(undefined2 *)(param_1 + 0xa7a306);
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, val = 0x%x)\n","vow_set_bad_node",2,4,
             *(undefined2 *)(param_1 + 0xa7a306));
    }
    break;
  default:
    if (2 < DebugLevel) {
      printk("%s:(No such command = 0x%x)\n","vow_set_bad_node",param_2);
    }
  }
  uVar1 = MtCmdSetVoWModuleCtrl(param_1,auStack_74);
  if (2 < DebugLevel) {
    printk("%s:(ret = %d), sizeof %zu\n","vow_set_bad_node",uVar1,100);
  }
  return uVar1;
}


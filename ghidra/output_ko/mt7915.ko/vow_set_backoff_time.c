// module: mt7915.ko
// function: vow_set_backoff_time @ 0x41a70
// size: 764 bytes
//

undefined4 vow_set_backoff_time(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 local_5c;
  undefined2 local_5a;
  undefined2 local_3c;
  undefined2 local_3a;
  undefined2 local_38;
  undefined2 local_36;
  undefined1 local_34;
  undefined1 local_33;
  
  __memzero(&local_5c,0x44);
  local_34 = (undefined1)param_2;
  local_5c = 3;
  local_5a = 3;
  switch(param_2) {
  case 0:
  case 1:
  case 2:
  case 3:
    iVar2 = param_1 + param_2 * 8;
    local_3a = *(undefined2 *)(iVar2 + 0xa797e6);
    local_3c = *(undefined2 *)(param_1 + (param_2 + 0x14f2fc) * 8 + 4);
    local_38 = *(undefined2 *)(iVar2 + 0xa797e8);
    local_36 = *(undefined2 *)(iVar2 + 0xa797ea);
    local_33 = 0xf;
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, group = 0x%x, BK = 0x%x, BE = 0x%x, VI = 0x%x, VO = 0x%x)\n"
             ,"vow_set_backoff_time",3,3,param_2,local_3c,local_3a,local_38,local_36);
    }
    break;
  case 4:
    local_38 = *(undefined2 *)(param_1 + 0xa79810);
    local_3c = *(undefined2 *)(param_1 + 0xa7980c);
    local_36 = *(undefined2 *)(param_1 + 0xa79812);
    local_3a = *(undefined2 *)(param_1 + 0xa7980e);
    local_33 = 0xf;
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, group = 0x%x, BK = 0x%x, BE = 0x%x, VI = 0x%x, VO = 0x%x)\n"
             ,"vow_set_backoff_time",3,3,4,local_3c,local_3a,local_38,local_36);
    }
    break;
  case 5:
    local_3c = *(undefined2 *)(param_1 + 0xa79804);
    local_3a = *(undefined2 *)(param_1 + 0xa79806);
    local_36 = *(undefined2 *)(param_1 + 0xa7980a);
    local_38 = *(undefined2 *)(param_1 + 0xa79808);
    local_33 = 0xf;
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, group = 0x%x, BK = 0x%x, BE = 0x%x, VI = 0x%x, VO = 0x%x)\n"
             ,"vow_set_backoff_time",3,3,5,local_3c,local_3a,local_38,local_36);
    }
    break;
  case 6:
    local_3c = *(undefined2 *)(param_1 + 0xa79814);
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, group = 0x%x, backoff time = 0x%x)\n",
             "vow_set_backoff_time",3,3,6,local_3c);
    }
    break;
  case 7:
    local_3c = *(undefined2 *)(param_1 + 0xa797de);
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, group = 0x%x, backoff time = 0x%x)\n",
             "vow_set_backoff_time",3,3,7,local_3c);
    }
    break;
  default:
    if (2 < DebugLevel) {
      printk("%s:(No such command = 0x%x)\n","vow_set_backoff_time",param_2);
    }
  }
  uVar1 = MtCmdSetVoWRxAirtimeCtrl(param_1,&local_5c);
  if (2 < DebugLevel) {
    printk("%s:(ret = %d), sizeof %zu\n","vow_set_backoff_time",uVar1,0x44);
  }
  return uVar1;
}


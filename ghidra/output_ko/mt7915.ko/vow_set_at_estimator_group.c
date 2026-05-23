// module: mt7915.ko
// function: vow_set_at_estimator_group @ 0x4208c
// size: 368 bytes
//

undefined4 vow_set_at_estimator_group(int param_1,int param_2,uint param_3)

{
  byte bVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  undefined2 local_7c;
  undefined2 local_7a;
  uint local_60;
  ushort auStack_5c [16];
  ushort auStack_3c [16];
  undefined1 local_1c;
  undefined1 local_1b;
  
  __memzero(&local_7c,100);
  local_7a = (undefined2)param_2;
  local_7c = 1;
  if (param_2 == 3) {
    iVar4 = param_1 + param_3 * 0x1c;
    bVar1 = *(byte *)(iVar4 + 0xa7982d);
    bVar2 = *(byte *)(iVar4 + 0xa7982c);
    local_60 = local_60 | 1 << (param_3 & 0xff);
    auStack_5c[param_3] = (ushort)bVar1;
    auStack_3c[param_3] = (ushort)bVar2;
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, group %d, val = 0x%x/0x%x)\n",
             "vow_set_at_estimator_group",1,3,param_3,bVar1,bVar2);
    }
  }
  else if (param_2 == 4) {
    local_1b = *(undefined1 *)(param_1 + param_3 * 0x1c + 0xa79840);
    local_1c = (undefined1)param_3;
    if (2 < DebugLevel) {
      printk("%s:(cmd = 0x%x, subcmd = 0x%x, group %d, val = 0x%x)\n","vow_set_at_estimator_group",1
             ,4,param_3,local_1b);
    }
  }
  else if (2 < DebugLevel) {
    printk("%s:(No such command = 0x%x)\n","vow_set_at_estimator_group",param_2);
  }
  uVar3 = MtCmdSetVoWModuleCtrl(param_1,&local_7c);
  if (2 < DebugLevel) {
    printk("%s:(ret = %d), sizeof %zu\n","vow_set_at_estimator_group",uVar3,100);
  }
  return uVar3;
}


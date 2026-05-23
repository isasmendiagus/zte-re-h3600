// module: mt7915.ko
// function: vow_set_wmm_selection @ 0x418ec
// size: 192 bytes
//

undefined4 vow_set_wmm_selection(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined2 local_54;
  undefined2 local_52;
  undefined1 local_38;
  undefined1 local_37;
  
  __memzero(&local_54,0x44);
  local_37 = *(undefined1 *)(param_1 + param_2 + 0xa797e0);
  local_38 = (undefined1)param_2;
  local_54 = 2;
  local_52 = 3;
  if (2 < DebugLevel) {
    printk("%s:(cmd = 0x%x, subcmd = 0x%x, OM = 0x%x, Map = 0x%x)\n","vow_set_wmm_selection",param_2
           ,3,param_2,local_37);
  }
  uVar1 = MtCmdSetVoWRxAirtimeCtrl(param_1,&local_54);
  if (2 < DebugLevel) {
    printk("%s:(ret = %d), sizeof %zu\n","vow_set_wmm_selection",uVar1,0x44);
  }
  return uVar1;
}


// module: mt7915.ko
// function: vow_set_mbss2wmm_map @ 0x419b0
// size: 188 bytes
//

undefined4 vow_set_mbss2wmm_map(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined2 local_54;
  undefined2 local_52;
  undefined1 local_34;
  undefined1 local_33;
  
  __memzero(&local_54,0x44);
  local_33 = *(undefined1 *)(param_1 + param_2 + 0xa79816);
  local_34 = (undefined1)param_2;
  local_54 = 2;
  local_52 = 4;
  if (2 < DebugLevel) {
    printk("%s:(cmd = 0x%x, subcmd = 0x%x, bss_idx = 0x%x, Map = 0x%x)\n","vow_set_mbss2wmm_map",2,4
           ,param_2,local_33);
  }
  uVar1 = MtCmdSetVoWRxAirtimeCtrl(param_1,&local_54);
  if (2 < DebugLevel) {
    printk("%s:(ret = %d), sizeof %zu\n","vow_set_mbss2wmm_map",uVar1,0x44);
  }
  return uVar1;
}


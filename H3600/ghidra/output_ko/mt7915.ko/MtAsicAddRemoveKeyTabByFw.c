// module: mt7915.ko
// function: MtAsicAddRemoveKeyTabByFw @ 0x198c48
// size: 180 bytes
//

void MtAsicAddRemoveKeyTabByFw(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 local_18;
  undefined4 local_14 [2];
  
  local_18 = 0;
  local_14[0] = 0;
  if (2 < DebugLevel) {
    printk("%s:, wcid=%d, Operation=%d, Direction=%d\n","MtAsicAddRemoveKeyTabByFw",
           *(undefined2 *)(param_2 + 3),*param_2,param_2[1]);
  }
  iVar1 = chip_fill_key_install_cmd
                    (*(undefined4 *)(param_1 + 0xa797a0),param_2,0,&local_18,local_14);
  if (iVar1 != 0) {
    return;
  }
  CmdExtWtblUpdate(param_1,*(undefined2 *)(param_2 + 3),2,local_18,local_14[0]);
  os_free_mem(local_18);
  return;
}


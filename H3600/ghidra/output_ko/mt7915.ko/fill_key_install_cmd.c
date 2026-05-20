// module: mt7915.ko
// function: fill_key_install_cmd @ 0x1c6690
// size: 264 bytes
//

undefined4 fill_key_install_cmd(undefined4 *param_1,int param_2,int *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  undefined1 uVar2;
  undefined1 *puVar3;
  
  if (*param_3 == 0) {
    os_alloc_mem(0,param_3,0x2c);
    if (*param_3 != 0) {
      os_zero_mem(*param_3,0x2c);
      puVar3 = (undefined1 *)*param_3;
      *param_4 = 0x2c;
      if (2 < DebugLevel) {
        printk("%s:, wcid=%d, Operation=%d, Direction=%d\n","fill_key_install_cmd",
               *(undefined2 *)(param_1 + 3),*param_1,param_1[1]);
      }
      if (param_2 == 0) {
        puVar3[1] = 0;
        uVar2 = 7;
      }
      else {
        uVar2 = 0xc;
        puVar3[1] = 0;
      }
      *puVar3 = uVar2;
      puVar3[3] = 0;
      puVar3[2] = 0x2c;
      uVar1 = fill_wtbl_key_info_struc(param_1,puVar3);
      return uVar1;
    }
    if (-1 < DebugLevel) {
      printk("%s: cmd alloc fail\n","fill_key_install_cmd");
    }
  }
  return 1;
}


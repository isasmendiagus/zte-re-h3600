// module: mt7915.ko
// function: fill_key_install_cmd_v2 @ 0x1c679c
// size: 228 bytes
//

undefined4 fill_key_install_cmd_v2(int param_1,undefined4 param_2,int *param_3,int *param_4)

{
  undefined4 uVar1;
  uint uVar2;
  undefined1 *puVar3;
  int iVar4;
  
  if (*param_3 != 0) {
    return 1;
  }
  uVar2 = *(uint *)(param_1 + 8);
  if ((uVar2 & 0x1e) == 0) {
    if ((uVar2 & 0x1e0) == 0) {
      iVar4 = 8;
    }
    else {
      iVar4 = 0x2c;
    }
  }
  else {
    iVar4 = 0x2c;
  }
  if (((uVar2 & 0x600) != 0) || (((uVar2 & 0x20) != 0 && (*(char *)(param_1 + 0x60) == ' ')))) {
    iVar4 = iVar4 + 0x24;
  }
  os_alloc_mem(0,param_3,iVar4);
  if (*param_3 != 0) {
    os_zero_mem(*param_3,iVar4);
    puVar3 = (undefined1 *)*param_3;
    *param_4 = iVar4;
    *(short *)(puVar3 + 2) = (short)iVar4;
    *puVar3 = 0x11;
    puVar3[1] = 0;
    uVar1 = fill_wtbl_key_info_struc_v2(param_1,puVar3,0,param_4);
    return uVar1;
  }
  if (-1 < DebugLevel) {
    printk("%s: cmd alloc fail\n","fill_key_install_cmd_v2");
  }
  return 1;
}


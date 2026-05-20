// module: mt7915.ko
// function: set_vow_bn_fallback_th @ 0x47b44
// size: 204 bytes
//

undefined4 set_vow_bn_fallback_th(int param_1,char *param_2)

{
  int iVar1;
  undefined4 local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar1 = sscanf(param_2,"%u",local_14);
  if (iVar1 != 0) {
    *(short *)(param_1 + 0xa7a304) = (short)local_14[0];
    iVar1 = vow_set_bad_node(param_1,3);
    if (DebugLevel < 0) {
      if (iVar1 == 0) {
        return 1;
      }
    }
    else {
      printk("%s: period %u.\n","set_vow_bn_fallback_th",local_14[0]);
      if (iVar1 == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: set command failed.\n","set_vow_bn_fallback_th");
      }
    }
  }
  return 0;
}


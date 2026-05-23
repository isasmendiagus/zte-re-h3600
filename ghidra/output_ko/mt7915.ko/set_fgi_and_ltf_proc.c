// module: mt7915.ko
// function: set_fgi_and_ltf_proc @ 0x2fc68
// size: 320 bytes
//

undefined4 set_fgi_and_ltf_proc(int *param_1,char *param_2)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  int local_1c [2];
  
  iVar4 = *param_1;
  local_1c[0] = 0;
  if (0 < DebugLevel) {
    printk("%s:: enter\n","set_fgi_and_ltf_proc");
  }
  iVar4 = get_wdev_by_ioctl_idx_and_iftype
                    (param_1,*(undefined4 *)(iVar4 + 0x3c),*(undefined4 *)(iVar4 + 0x38));
  if (iVar4 != 0) {
    if (param_2 != (char *)0x0) {
      iVar3 = sscanf(param_2,"%u",local_1c);
      iVar1 = DebugLevel;
      if ((local_1c[0] != 0xc80 &&
           (local_1c[0] != 0x640 && (local_1c[0] != 800 && local_1c[0] != 0))) || (iVar3 != 1)) {
        if (0 < DebugLevel) {
          printk("%s():Wrong parameters!!!\n","set_fgi_and_ltf_proc");
          return 0xffffffff;
        }
        return 0xffffffff;
      }
      uVar2 = 1;
      if (local_1c[0] == 0) {
        uVar2 = 0;
      }
      else if (local_1c[0] != 800) {
        if (local_1c[0] == 0x640) {
          uVar2 = 2;
        }
        else {
          uVar2 = 3;
        }
      }
      *(undefined1 *)(iVar4 + 0x405c) = uVar2;
      if (0 < iVar1) {
        printk("%s(): set target_gi(%d)\n","set_fgi_and_ltf_proc");
      }
    }
    return 1;
  }
  return 0xfffffff2;
}


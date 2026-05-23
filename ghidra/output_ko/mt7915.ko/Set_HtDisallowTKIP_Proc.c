// module: mt7915.ko
// function: Set_HtDisallowTKIP_Proc @ 0xddeb8
// size: 136 bytes
//

undefined4 Set_HtDisallowTKIP_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  if (iVar2 == 1) {
    *(undefined1 *)(param_1 + 0x795984) = 1;
    if (iVar1 < 3) {
      return 1;
    }
    pcVar3 = "enabled";
  }
  else {
    *(undefined1 *)(param_1 + 0x795984) = 0;
    if (iVar1 < 3) {
      return 1;
    }
    pcVar3 = "disabled";
  }
  printk("Set_HtDisallowTKIP_Proc ::%s\n",pcVar3);
  return 1;
}


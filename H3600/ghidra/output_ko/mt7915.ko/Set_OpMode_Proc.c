// module: mt7915.ko
// function: Set_OpMode_Proc @ 0xe04cc
// size: 216 bytes
//

undefined4 Set_OpMode_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  if ((*(uint *)(param_1 + 0xa39f84) & 2) != 0) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk("Can not switch operate mode on interface up !!\n");
    return 0;
  }
  if (iVar2 == 0) {
    *(undefined1 *)(param_1 + 0x286285) = 0;
    if (iVar1 < 3) {
      return 1;
    }
    pcVar3 = "STA Mode";
  }
  else {
    if (iVar2 != 1) {
      return 0;
    }
    *(undefined1 *)(param_1 + 0x286285) = 1;
    if (iVar1 < 3) {
      return 1;
    }
    pcVar3 = "AP Mode";
  }
  printk("Set_OpMode_Proc::(OpMode=%s)\n",pcVar3);
  return 1;
}


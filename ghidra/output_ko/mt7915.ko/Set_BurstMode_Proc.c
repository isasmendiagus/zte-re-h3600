// module: mt7915.ko
// function: Set_BurstMode_Proc @ 0xe9b24
// size: 132 bytes
//

undefined4 Set_BurstMode_Proc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  char *pcVar2;
  
  iVar1 = os_str_tol(param_2,0,10,param_4,param_4);
  *(bool *)(param_1 + 0x795951) = iVar1 == 1;
  AsicSetRalinkBurstMode(param_1);
  if (2 < DebugLevel) {
    pcVar2 = "enabled";
    if (*(char *)(param_1 + 0x795951) != '\x01') {
      pcVar2 = "disabled";
    }
    printk("Set_BurstMode_Proc ::%s\n",pcVar2);
  }
  return 1;
}


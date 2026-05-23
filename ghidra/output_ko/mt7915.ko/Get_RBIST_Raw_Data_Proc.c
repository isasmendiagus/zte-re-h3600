// module: mt7915.ko
// function: Get_RBIST_Raw_Data_Proc @ 0xeb160
// size: 252 bytes
//

undefined4 Get_RBIST_Raw_Data_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  code *pcVar3;
  
  iVar1 = simple_strtol(param_2,0,10);
  if (iVar1 == 0) {
    iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    pcVar3 = *(code **)(iVar1 + 400);
  }
  else {
    if (iVar1 != 1) {
      if (DebugLevel < 0) {
        return 1;
      }
      printk("%s: Not support for %d this selection !!\n","Get_RBIST_Raw_Data_Proc");
      uVar2 = 2;
      goto LAB_000eb1bc;
    }
    iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
    pcVar3 = *(code **)(iVar1 + 0x1a8);
  }
  if (pcVar3 == (code *)0x0) {
    if (DebugLevel < 0) {
      return 1;
    }
    printk("%s : The function is not hooked !!\n","Get_RBIST_Raw_Data_Proc");
    uVar2 = 2;
  }
  else {
    uVar2 = (*pcVar3)(param_1);
  }
LAB_000eb1bc:
  if (0 < DebugLevel) {
    printk("%s:(Status = %d)\n","Get_RBIST_Raw_Data_Proc",uVar2);
  }
  return 1;
}


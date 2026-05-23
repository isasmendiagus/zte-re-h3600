// module: mt7915.ko
// function: show_swqinfo @ 0xe2f20
// size: 92 bytes
//

undefined4 show_swqinfo(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  code *pcVar1;
  int iVar2;
  
  iVar2 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  pcVar1 = *(code **)(iVar2 + 0x14);
  if (pcVar1 != (code *)0x0) {
    if (0 < DebugLevel) {
      printk("%s: show_swqinfo\n","show_swqinfo",pcVar1,DebugLevel,param_4);
      pcVar1 = *(code **)(iVar2 + 0x14);
    }
    (*pcVar1)(param_1);
  }
  return 1;
}


// module: mt7915.ko
// function: bbp_set_bw @ 0x171e1c
// size: 132 bytes
//

int bbp_set_bw(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  code *pcVar3;
  
  if ((*(int *)("Get_RBIST_IQ_Data_Proc" + param_1) != 0) &&
     (pcVar3 = *(code **)(*(int *)("Get_RBIST_IQ_Data_Proc" + param_1) + 0x18),
     pcVar3 != (code *)0x0)) {
    iVar1 = (*pcVar3)();
    if ((iVar1 == 1) && (2 < DebugLevel)) {
      uVar2 = get_bw_str(param_2);
      printk("%s(): Set PhyBW as %sHz.l\n","bbp_set_bw",uVar2);
    }
    return iVar1;
  }
  return 0;
}


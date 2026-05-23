// module: mt7915.ko
// function: Set_CpuUtilEn_Proc @ 0x2fc00
// size: 104 bytes
//

undefined4 Set_CpuUtilEn_Proc(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (param_2 == 0) {
    return 0;
  }
  uVar2 = os_str_toul(param_2,0,10);
  if (*(code **)(iVar1 + 0xac) != (code *)0x0) {
    (**(code **)(iVar1 + 0xac))(param_1,uVar2);
    return 1;
  }
  return 1;
}


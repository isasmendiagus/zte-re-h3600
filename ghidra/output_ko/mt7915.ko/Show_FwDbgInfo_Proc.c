// module: mt7915.ko
// function: Show_FwDbgInfo_Proc @ 0x2fbcc
// size: 52 bytes
//

undefined4 Show_FwDbgInfo_Proc(int param_1)

{
  int iVar1;
  
  iVar1 = hc_get_chip_dbg(*(undefined4 *)(param_1 + 0xa797a0));
  if (*(code **)(iVar1 + 0xa8) != (code *)0x0) {
    (**(code **)(iVar1 + 0xa8))(param_1);
  }
  return 1;
}


// module: mt7915.ko
// function: ChkExceptionType @ 0x192d28
// size: 92 bytes
//

/* WARNING: Removing unreachable block (ram,0x00192d78) */

undefined4 ChkExceptionType(int param_1)

{
  undefined **ppuVar1;
  
  ppuVar1 = (undefined **)0x219848;
  if ("Get_RBIST_IQ_Data_Proc"[param_1 + 0x14] != '\x01') {
    ppuVar1 = &PTR_caseD_4_0021a870;
  }
  hw_io_read32(*(undefined4 *)(param_1 + 0xa797a0),ppuVar1);
  return 0;
}


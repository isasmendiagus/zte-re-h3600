// FUN_c0015444 @ c0015444

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_c0015444(void)

{
  uint uVar1;
  
  FUN_c0014c50();
  if ((_DAT_c069e9a0 & 1) == 0) {
    return;
  }
  uVar1 = coproc_movefrom_Auxiliary_Control();
  coproc_moveto_Auxiliary_Control(uVar1 | 0xe);
  InstructionSynchronizationBarrier(0xf);
  return;
}


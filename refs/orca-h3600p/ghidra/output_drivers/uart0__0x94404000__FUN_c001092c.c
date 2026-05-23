// peripheral: uart0 (0x94404000)
// LE32 ref at 0xc0010940
// function: FUN_c001092c @ 0xc001092c
// total LE32 refs to this addr: 2
//

void FUN_c001092c(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  
  uVar1 = DAT_c0010944;
  *param_1 = DAT_c0010940;
  *param_2 = uVar1;
  return;
}


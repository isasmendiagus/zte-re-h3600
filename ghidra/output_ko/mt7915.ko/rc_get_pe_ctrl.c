// module: mt7915.ko
// function: rc_get_pe_ctrl @ 0xabfa8
// size: 40 bytes
//

int rc_get_pe_ctrl(int param_1)

{
  int iVar1;
  
  if (**(byte **)(param_1 + 4) < 2) {
    iVar1 = (uint)**(byte **)(param_1 + 4) * 0x354 + *(int *)(param_1 + 0x18) + 0x16ac;
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}


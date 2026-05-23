// module: mt7915.ko
// function: mt_ate_fill_empty_allocation @ 0x28cb28
// size: 40 bytes
//

undefined4 mt_ate_fill_empty_allocation(int param_1)

{
  char *pcVar1;
  
  pcVar1 = (char *)(param_1 + -1);
  do {
    pcVar1 = pcVar1 + 1;
    if (*pcVar1 == -1) {
      *pcVar1 = 'q';
    }
  } while (pcVar1 != (char *)(param_1 + 7));
  return 0;
}


// module: mt7915.ko
// function: MATEngineExit @ 0x79fe0
// size: 104 bytes
//

undefined4 MATEngineExit(int param_1)

{
  int *piVar1;
  char *pcVar2;
  
  if (*(int *)(param_1 + 0x794b28) != 2) {
    pcVar2 = "";
    do {
      piVar1 = (int *)(pcVar2 + 4);
      pcVar2 = pcVar2 + 8;
      if (*(code **)(*piVar1 + 0xc) != (code *)0x0) {
        (**(code **)(*piVar1 + 0xc))(param_1 + 0x794b28);
      }
    } while (pcVar2 != "IPMacTable_init");
    *(undefined4 *)(param_1 + 0x794b28) = 2;
  }
  return 1;
}


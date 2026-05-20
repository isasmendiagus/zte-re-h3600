// module: mt7915.ko
// function: check_scs_glo @ 0x172c1c
// size: 144 bytes
//

void check_scs_glo(int param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *extraout_r1;
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  
  puVar4 = param_2 + 4;
  puVar2 = param_2;
  puVar3 = (undefined4 *)(param_1 + 0x794cac);
  do {
    *puVar3 = *puVar2;
    iVar1 = puVar2[1];
    *(bool *)(puVar3 + 1) = iVar1 != 0x6c;
    if ((iVar1 != 0x6c) && (-1 < DebugLevel)) {
      printk(&_LC40,param_2);
      param_2 = (undefined4 *)0x6c;
      if (-1 < DebugLevel) {
        printk("Drive Size = %d, FW Size = %d",0x6c,puVar2[1],DebugLevel,param_4);
        param_2 = extraout_r1;
      }
    }
    puVar2 = puVar2 + 2;
    puVar3 = puVar3 + 2;
  } while (puVar2 != puVar4);
  return;
}


// module: mt7915.ko
// function: HdevObjAdd @ 0xae304
// size: 136 bytes
//

void HdevObjAdd(int param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = *(int **)(param_1 + 0x10);
  iVar2 = *piVar1;
  *(int **)(param_2 + 0x18) = piVar1;
  *(int *)(param_2 + 0x14) = iVar2;
  *(int *)(*piVar1 + 4) = param_2 + 0x14;
  *piVar1 = param_2 + 0x14;
  *(int *)(param_2 + 8) = param_1;
  *(int *)(param_2 + 0xc) = param_2 + 0xc;
  *(int *)(param_2 + 0x10) = param_2 + 0xc;
  *(char *)(param_1 + 0x14) = *(char *)(param_1 + 0x14) + '\x01';
  if ((*(char *)(param_2 + 0x1c) != '\0') && (-1 < DebugLevel)) {
    printk("%s(): obj state is not free! need to check!\n","HdevObjAdd");
  }
  *(undefined1 *)(param_2 + 0x1c) = 1;
  return;
}


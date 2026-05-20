// module: mt7915.ko
// function: SrProfileSREnable @ 0x16b75c
// size: 232 bytes
//

undefined4 SrProfileSREnable(int param_1,undefined4 param_2)

{
  undefined1 uVar1;
  int iVar2;
  char cVar3;
  undefined1 *puVar4;
  
  iVar2 = rstrtok(param_2,&_LC34);
  if (iVar2 == 0) {
    return 0;
  }
  puVar4 = (undefined1 *)(param_1 + 0x795b16);
  cVar3 = '\x01';
  do {
    if (*(int *)(param_1 + 0x795050) == 0) {
      uVar1 = simple_strtol(iVar2,0,10);
      *(undefined1 *)(param_1 + 0x795b16) = uVar1;
LAB_0016b7ec:
      iVar2 = rstrtok(0,&_LC34);
      if (iVar2 == 0) {
        return 0;
      }
      if (cVar3 == '\x03') {
        return 2;
      }
    }
    else {
      if (*(int *)(param_1 + 0x795050) != 3) {
        uVar1 = simple_strtol(iVar2,0,10);
        *puVar4 = uVar1;
        goto LAB_0016b7ec;
      }
      if (cVar3 != '\x01') {
        uVar1 = simple_strtol(iVar2,0,10);
        *(undefined1 *)(param_1 + 0x795b16) = uVar1;
        goto LAB_0016b7ec;
      }
      uVar1 = simple_strtol(iVar2,0,10);
      *(undefined1 *)(param_1 + 0x795b17) = uVar1;
      iVar2 = rstrtok(0,&_LC34);
      if (iVar2 == 0) {
        return 0;
      }
    }
    cVar3 = cVar3 + '\x01';
    puVar4 = puVar4 + 1;
  } while( true );
}


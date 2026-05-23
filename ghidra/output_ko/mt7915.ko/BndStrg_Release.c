// module: mt7915.ko
// function: BndStrg_Release @ 0x9d378
// size: 216 bytes
//

int BndStrg_Release(int param_1)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  puVar1 = &DAT_0036b924 + param_1;
  iVar3 = 0;
  do {
    BndStrg_SetInfFlags(param_1,puVar1,0);
    if (puVar1[5] == '\x01') {
      iVar3 = BndStrg_Enable(puVar1,0);
    }
    if (*(short *)(&DAT_0036c944 + iVar2 * 0x1094 + param_1) == 0) {
      if (puVar1[4] == '\0') {
        iVar3 = 5;
LAB_0009d3ec:
        if (-1 < DebugLevel) {
          printk("Error in %s(), error code = %d!\n","BndStrg_Release",iVar3);
        }
      }
      else {
        puVar1[4] = 0;
        iVar3 = 0;
      }
    }
    else if (iVar3 != 0) goto LAB_0009d3ec;
    puVar1 = puVar1 + 0x1094;
    if (iVar2 == 1) {
      return iVar3;
    }
    iVar2 = 1;
  } while( true );
}


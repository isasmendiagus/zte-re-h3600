// module: mt7915.ko
// function: init_vie_ctrl @ 0x146354
// size: 164 bytes
//

void init_vie_ctrl(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar5 = 0;
  piVar4 = (int *)(param_1 + 0x3fe8);
  do {
    *piVar4 = iVar5;
    *(undefined1 *)(piVar4 + 1) = 0;
    if (piVar4[2] != 0) {
      iVar1 = piVar4[2];
      iVar3 = 0;
LAB_001463a4:
      do {
        iVar2 = *(int *)(iVar1 + 0xc);
        if (iVar2 == 0) {
          if (*(int *)(iVar1 + 8) != 0) goto LAB_00146384;
        }
        else {
          iVar3 = iVar2;
          if (*(int *)(iVar1 + 8) == 0) {
            *(undefined4 *)(iVar1 + 0xc) = 0;
            os_free_mem(iVar1);
            iVar1 = iVar2;
            goto LAB_001463a4;
          }
LAB_00146384:
          os_free_mem();
          *(undefined4 *)(iVar1 + 8) = 0;
        }
        *(undefined4 *)(iVar1 + 0xc) = 0;
        os_free_mem(iVar1);
        iVar1 = iVar3;
      } while (iVar3 != 0);
    }
    iVar5 = iVar5 + 1;
    piVar4[2] = 0;
    piVar4 = piVar4 + 3;
    if (iVar5 == 7) {
      return;
    }
  } while( true );
}


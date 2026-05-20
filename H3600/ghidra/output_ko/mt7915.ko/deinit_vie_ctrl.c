// module: mt7915.ko
// function: deinit_vie_ctrl @ 0x1463f8
// size: 212 bytes
//

void deinit_vie_ctrl(int param_1)

{
  int iVar1;
  char cVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  puVar3 = (undefined4 *)(param_1 + 0x3fe8);
  do {
    *puVar3 = 0;
    if (puVar3[2] != 0) {
      cVar2 = *(char *)(puVar3 + 1);
      iVar1 = puVar3[2];
joined_r0x0014642c:
      do {
        if (cVar2 == '\0') break;
        iVar5 = *(int *)(iVar1 + 0xc);
        if (iVar5 == 0) {
          iVar5 = iVar4;
          if (*(int *)(iVar1 + 8) != 0) goto LAB_00146434;
        }
        else {
          if (*(int *)(iVar1 + 8) == 0) {
            *(undefined4 *)(iVar1 + 0xc) = 0;
            os_free_mem(iVar1);
            cVar2 = *(char *)(puVar3 + 1) + -1;
            *(char *)(puVar3 + 1) = cVar2;
            iVar1 = iVar5;
            iVar4 = iVar5;
            goto joined_r0x0014642c;
          }
LAB_00146434:
          os_free_mem();
          *(undefined4 *)(iVar1 + 8) = 0;
          iVar4 = iVar5;
        }
        *(undefined4 *)(iVar1 + 0xc) = 0;
        os_free_mem(iVar1);
        cVar2 = *(char *)(puVar3 + 1) + -1;
        *(char *)(puVar3 + 1) = cVar2;
        iVar1 = iVar4;
      } while (iVar4 != 0);
    }
    puVar3[2] = 0;
    puVar3 = puVar3 + 3;
    if (puVar3 == (undefined4 *)(param_1 + 0x403c)) {
      return;
    }
  } while( true );
}


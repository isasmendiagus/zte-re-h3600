// module: plat-zxylzb_9128S.ko
// function: my_dump_vma @ 0x1cd0c
// size: 584 bytes
//

void my_dump_vma(int param_1)

{
  bool bVar1;
  int iVar2;
  char *pcVar3;
  uint uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  char acStack_120 [260];
  
  iVar9 = *(int *)(param_1 + 0x18c);
  iVar8 = *(int *)(param_1 + 4);
  iVar2 = rb_last(iVar9 + 4);
  uVar4 = *(uint *)(iVar8 + 0x1fe4);
  if (uVar4 < *(uint *)(iVar2 + -0x10)) {
    bVar1 = false;
  }
  else if (uVar4 < *(uint *)(iVar2 + -0xc)) {
    bVar1 = true;
  }
  else {
    bVar1 = false;
  }
  iVar2 = rb_first(iVar9 + 4);
  do {
    if (iVar2 == 0) {
      return;
    }
    uVar4 = *(uint *)(iVar2 + 0x18);
    iVar10 = *(int *)(iVar2 + 0x40);
    if ((uVar4 & 1) == 0) {
      uVar5 = 0x2d;
    }
    else {
      uVar5 = 0x72;
    }
    if ((uVar4 & 2) == 0) {
      uVar12 = 0x2d;
    }
    else {
      uVar12 = 0x77;
    }
    if ((uVar4 & 4) == 0) {
      uVar13 = 0x2d;
    }
    else {
      uVar13 = 0x78;
    }
    if ((uVar4 & 0x80) == 0) {
      uVar11 = 0x70;
    }
    else {
      uVar11 = 0x73;
    }
    printk("vma : %.8lx-%.8lx %c%c%c%c ",*(undefined4 *)(iVar2 + -0x10),
           *(undefined4 *)(iVar2 + -0xc),uVar5,uVar12,uVar13,uVar11);
    if (iVar10 == 0) {
      uVar4 = *(uint *)(iVar2 + -0x10);
      if ((*(uint *)(iVar9 + 0x94) < uVar4) || (*(uint *)(iVar2 + -0xc) < *(uint *)(iVar9 + 0x90)))
      {
        uVar6 = *(uint *)(iVar9 + 0x98);
        if ((uVar6 < uVar4) || (*(uint *)(iVar2 + -0xc) < uVar6)) {
          if (((uVar6 ^ uVar4) & 0xf0000000) != 0) goto LAB_0001cf18;
          uVar6 = *(uint *)(iVar8 + 0x1fe4);
          if ((uVar6 < uVar4) || (*(uint *)(iVar2 + -0xc) <= uVar6)) {
            iVar10 = param_1;
            if (!bVar1) {
              iVar10 = *(int *)(param_1 + 0x200);
            }
            for (puVar7 = *(undefined4 **)(iVar10 + 0x208); puVar7 != (undefined4 *)(iVar10 + 0x208)
                ; puVar7 = (undefined4 *)*puVar7) {
              if ((uVar4 <= *(uint *)(puVar7[-0x83] + 0x1fe4)) &&
                 (*(uint *)(puVar7[-0x83] + 0x1fe4) < *(uint *)(iVar2 + -0xc))) {
                if ((int)puVar7[-6] < 0) {
                  pcVar3 = "[stack:child]";
                }
                else {
                  sprintf(acStack_120,"[stack:%d]");
                  pcVar3 = acStack_120;
                }
                goto LAB_0001cf20;
              }
            }
            pcVar3 = "[stack:child]";
          }
          else {
            sprintf(acStack_120,"[stack:%d]",*(undefined4 *)(param_1 + 0x1f8));
            pcVar3 = acStack_120;
          }
        }
        else {
          if (bVar1) {
            uVar5 = *(undefined4 *)(param_1 + 0x1f8);
          }
          else {
            uVar5 = *(undefined4 *)(*(int *)(param_1 + 0x200) + 0x1f8);
          }
          sprintf(acStack_120,"[stack:parent %d]",uVar5);
          pcVar3 = acStack_120;
        }
      }
      else {
        pcVar3 = "[heap]";
      }
    }
    else {
      pcVar3 = (char *)d_path(iVar10 + 8,acStack_120,0x100);
      if (pcVar3 == (char *)0x0) {
LAB_0001cf18:
        pcVar3 = "";
      }
    }
LAB_0001cf20:
    printk(&_LC7,pcVar3);
    iVar2 = rb_next(iVar2);
  } while( true );
}


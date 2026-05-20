// module: mt7915.ko
// function: ExtEventICapUnSolicitIQDataHandler @ 0x1a6fcc
// size: 496 bytes
//

void ExtEventICapUnSolicitIQDataHandler(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = *(int *)(param_1 + 0xa78acc);
  if (2 < DebugLevel) {
    printk("%s----------------->\n","ExtEventICapUnSolicitIQDataHandler");
  }
  uVar2 = *(uint *)(param_2 + 4);
  uVar5 = *(uint *)(param_1 + 0xa78a64);
  if (uVar5 < uVar2) {
    if (DebugLevel < 0) {
      return;
    }
    printk(&_LC41,"ExtEventICapUnSolicitIQDataHandler");
    return;
  }
  iVar8 = DebugLevel;
  if (*(int *)(param_2 + 0xc) != 0) {
    uVar5 = *(uint *)(param_1 + 0xa78a68);
    uVar6 = uVar5 + *(int *)(param_2 + 0x14);
    uVar2 = uVar5;
    if (uVar5 < uVar6) {
      uVar3 = *(uint *)(param_2 + 0x10);
      iVar7 = iVar7 + uVar5 * 0x20;
      iVar8 = 0;
      do {
        if (uVar3 != 0) {
          uVar2 = 0;
          do {
            iVar4 = param_2 + iVar8 * 4;
            iVar1 = uVar2 * 8;
            iVar8 = iVar8 + 2;
            *(undefined4 *)(iVar7 + uVar2 * 8) = *(undefined4 *)(iVar4 + 0x30);
            uVar2 = uVar2 + 1;
            *(undefined4 *)(iVar7 + iVar1 + 4) = *(undefined4 *)(iVar4 + 0x34);
            uVar3 = *(uint *)(param_2 + 0x10);
          } while (uVar2 < uVar3);
        }
        uVar5 = uVar5 + 1;
        iVar7 = iVar7 + 0x20;
        uVar2 = uVar6;
      } while (uVar5 != uVar6);
    }
    *(uint *)(param_1 + 0xa78a68) = uVar2;
    uVar2 = *(uint *)(param_2 + 0xc);
    iVar8 = DebugLevel;
    if (uVar2 != 0) {
      uVar5 = 0;
      do {
        if (2 < iVar8) {
          printk(&_LC60,uVar5,*(undefined4 *)(param_2 + (uVar5 + 0xc) * 4));
          uVar2 = *(uint *)(param_2 + 0xc);
          iVar8 = DebugLevel;
        }
        uVar5 = uVar5 + 1;
      } while (uVar5 < uVar2);
    }
    uVar5 = *(int *)(param_1 + 0xa78a64) + 1;
    *(uint *)(param_1 + 0xa78a64) = uVar5;
    if (*(int *)(param_2 + 0xc) != 0) goto LAB_001a70e0;
    uVar2 = *(uint *)(param_2 + 4);
  }
  if (uVar5 == uVar2) {
    if (0 < iVar8) {
      printk(&_LC54,"ExtEventICapUnSolicitIQDataHandler",uVar5);
    }
    *(undefined4 *)(param_1 + 0xa78a64) = 0;
    *(undefined4 *)(param_1 + 0xa78a68) = 0;
    *(undefined4 *)(param_1 + 0xa78a50) = 0;
    complete(param_1 + 0xa78abc);
    iVar8 = DebugLevel;
  }
LAB_001a70e0:
  if (iVar8 < 3) {
    return;
  }
  printk("%s:(Status = %d)\n","ExtEventICapUnSolicitIQDataHandler",
         *(undefined4 *)(param_1 + 0xa78a50));
  if (DebugLevel < 3) {
    return;
  }
  printk("%s<-----------------\n","ExtEventICapUnSolicitIQDataHandler");
  return;
}


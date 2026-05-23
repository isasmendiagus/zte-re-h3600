// module: mt7915.ko
// function: ap_amsdu_tx @ 0x1c730
// size: 376 bytes
//

void ap_amsdu_tx(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int *piVar1;
  undefined1 uVar2;
  int iVar3;
  code *pcVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = *(int *)(param_2 + 0x904);
  if (*(uint *)(param_3 + 0x48) < 2) {
    printk(&_LC16,0x8be,param_3,*(uint *)(param_3 + 0x48),param_4);
    dump_stack();
  }
  iVar5 = 0;
  do {
    piVar1 = *(int **)(param_3 + 0x40);
    if (piVar1 == (int *)0x0) {
      return;
    }
    while( true ) {
      iVar3 = *piVar1;
      *piVar1 = 0;
      *(int **)(param_3 + 0xc) = piVar1;
      if (iVar3 == 0) {
        *(undefined4 *)(param_3 + 0x44) = 0;
      }
      *(int *)(param_3 + 0x40) = iVar3;
      *(int *)(param_3 + 0x48) = *(int *)(param_3 + 0x48) + -1;
      if (iVar5 == 0) {
        *(undefined1 *)(param_3 + 0x2e) = 1;
      }
      else {
        if (*(byte *)(param_3 + 3) - 1 == iVar5) {
          uVar2 = 3;
        }
        else {
          uVar2 = 2;
        }
        *(undefined1 *)(param_3 + 0x2e) = uVar2;
      }
      iVar3 = fill_tx_blk(param_1,param_2,param_3);
      if (iVar3 != 0) break;
      iVar3 = *(int *)(param_3 + 0x78);
      if (iVar3 == 0) {
        iVar3 = *(int *)(param_3 + 0x74);
        if (iVar3 != 0) {
          *(int *)(iVar3 + 0x213194) = *(int *)(iVar3 + 0x213194) + 1;
        }
      }
      else {
        *(int *)(iVar3 + 0x43fc) = *(int *)(iVar3 + 0x43fc) + 1;
      }
      *(int *)(param_1 + 0x9db94) = *(int *)(param_1 + 0x9db94) + 1;
      RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0xc));
      piVar1 = *(int **)(param_3 + 0x40);
      if (piVar1 == (int *)0x0) {
        return;
      }
    }
    if ((*(uint *)(param_3 + 0x18) & 0x800000) == 0) {
      pcVar4 = *(code **)(iVar6 + 0x40);
    }
    else {
      pcVar4 = *(code **)(iVar6 + 0x44);
    }
    (*pcVar4)(param_1,param_2,param_3);
    FUN_0001bb8c(param_1,param_2,param_3);
    iVar3 = asic_hw_tx(param_1,param_3);
    if (iVar3 != 0) {
      return;
    }
    iVar5 = iVar5 + 1;
    *(char *)(param_3 + 0x2d) = *(char *)(param_3 + 0x2d) + '\x01';
  } while( true );
}


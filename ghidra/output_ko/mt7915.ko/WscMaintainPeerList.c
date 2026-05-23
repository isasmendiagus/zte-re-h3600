// module: mt7915.ko
// function: WscMaintainPeerList @ 0x1ee4d8
// size: 244 bytes
//

/* WARNING: Type propagation algorithm not settling */

void WscMaintainPeerList(undefined4 param_1,int param_2)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  
  _raw_spin_lock_bh(param_2 + 0x2c00);
  iVar3 = jiffies;
  piVar1 = *(int **)(param_2 + 0x2c04);
  do {
    while( true ) {
      while( true ) {
        if (piVar1 == (int *)0x0) {
          _raw_spin_unlock_bh(param_2 + 0x2c00);
          return;
        }
        if ((piVar1[1] + 3000) - iVar3 < 0) break;
        piVar1 = (int *)*piVar1;
      }
      puVar4 = *(undefined4 **)(param_2 + 0x2c04);
      piVar5 = (int *)*piVar1;
      if (puVar4 != (undefined4 *)0x0) break;
LAB_001ee574:
      os_free_mem();
      piVar1 = piVar5;
    }
    if (piVar1 != puVar4) {
      for (puVar2 = (undefined4 *)*puVar4; puVar2 != (undefined4 *)0x0;
          puVar2 = (undefined4 *)*puVar2) {
        if (puVar2 == piVar1) {
          *puVar4 = piVar5;
          if (piVar1 == (int *)*(int *)(param_2 + 0x2c08)) {
            *(undefined4 **)(param_2 + 0x2c08) = puVar4;
          }
          goto LAB_001ee5a4;
        }
        puVar4 = puVar2;
      }
      goto LAB_001ee574;
    }
    *(int **)(param_2 + 0x2c04) = piVar5;
    if (piVar5 == (int *)0x0) {
      *(undefined4 *)(param_2 + 0x2c08) = 0;
    }
LAB_001ee5a4:
    *(char *)(param_2 + 0x2c0c) = *(char *)(param_2 + 0x2c0c) + -1;
    os_free_mem();
    piVar1 = piVar5;
  } while( true );
}


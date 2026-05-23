// module: mt7915.ko
// function: mt7915_rxv_dump_buf_clear @ 0x17ea84
// size: 636 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 mt7915_rxv_dump_buf_clear(int param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  bool bVar10;
  int *local_2c;
  
  if (*(char *)(param_1 + 0xa7c218) == '\0') {
    piVar3 = *(int **)(param_1 + 0xa7c220);
    if (piVar3 == (int *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s(): null pointer for dump entry list.\n","mt7915_rxv_dump_buf_clear");
        return 1;
      }
    }
    else {
      piVar9 = (int *)*piVar3;
      if (piVar3 != piVar9) {
        iVar5 = 0;
        piVar6 = piVar9;
        do {
          piVar6 = (int *)*piVar6;
          iVar5 = iVar5 + 1;
        } while (piVar3 != piVar6);
        if (iVar5 != 0) {
          piVar6 = piVar9;
          local_2c = (int *)*piVar9;
          if (piVar3 != piVar9) {
            do {
              piVar3 = (int *)piVar6[3];
              if ((piVar3 != (int *)0x0) && (piVar9 = (int *)*piVar3, piVar3 != piVar9)) {
                iVar5 = 0;
                piVar7 = piVar9;
                do {
                  piVar7 = (int *)*piVar7;
                  iVar5 = iVar5 + 1;
                } while (piVar3 != piVar7);
                if (iVar5 != 0) {
                  piVar7 = (int *)*piVar9;
                  while (piVar1 = piVar7, piVar3 != piVar9) {
                    piVar7 = (int *)piVar9[4];
                    if ((piVar7 != (int *)0x0) && (piVar4 = (int *)*piVar7, piVar7 != piVar4)) {
                      iVar5 = 0;
                      piVar8 = piVar4;
                      do {
                        piVar8 = (int *)*piVar8;
                        iVar5 = iVar5 + 1;
                      } while (piVar7 != piVar8);
                      if (iVar5 != 0) {
                        piVar8 = (int *)*piVar4;
                        while (piVar2 = piVar8, piVar7 != piVar4) {
                          iVar5 = FUN_0017b214(param_1,piVar4,0);
                          if (iVar5 != 0) goto LAB_0017eba4;
                          piVar8 = (int *)*piVar2;
                          piVar4 = piVar2;
                        }
                        os_free_mem(piVar7);
                        iVar5 = FUN_0017b214(param_1,piVar9,1);
                        if (iVar5 != 0) goto LAB_0017eba4;
                      }
                    }
                    piVar7 = (int *)*piVar1;
                    piVar9 = piVar1;
                  }
                  os_free_mem(piVar3);
                  iVar5 = FUN_0017b214(param_1,piVar6,2);
                  if (iVar5 != 0) {
LAB_0017eba4:
                    if (DebugLevel < 0) {
                      return 1;
                    }
                    printk("%s(): link list remove fail.\n","mt7915_rxv_dump_buf_clear");
                    return 1;
                  }
                }
              }
              piVar9 = *(int **)(param_1 + 0xa7c220);
              bVar10 = local_2c != piVar9;
              piVar6 = local_2c;
              local_2c = (int *)*local_2c;
            } while (bVar10);
          }
          os_free_mem(piVar9);
          *(undefined4 *)(param_1 + 0xa7c220) = 0;
          *(undefined1 *)(param_1 + 0xa7c21a) = 0;
          *(undefined1 *)(param_1 + 0xa7c21b) = 0;
          *(undefined1 *)(param_1 + 0xa7c21c) = 0;
          *(undefined1 *)(param_1 + 0xa7c21d) = 0;
          *(undefined1 *)(param_1 + 0xa7c21e) = 0;
          *(undefined1 *)(param_1 + 0xa7c219) = 0;
          return 0;
        }
      }
      if (-1 < DebugLevel) {
        printk("%s(): no need to clear empty list.\n","mt7915_rxv_dump_buf_clear");
        return 1;
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s(): cannot alloc buf when enable dump process.\n","mt7915_rxv_dump_buf_clear");
  }
  return 1;
}


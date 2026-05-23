// module: mt7915.ko
// function: mt7915_rxv_dump_show_list @ 0x17dd24
// size: 1000 bytes
//

undefined4 mt7915_rxv_dump_show_list(int param_1)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  int *piVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  
  if ((0 < DebugLevel) &&
     (printk("%s(): enable: %d, type_mask: 0x%x, type_num: %d\n","mt7915_rxv_dump_show_list",
             *(undefined1 *)(param_1 + 0xa7c218),*(undefined1 *)(param_1 + 0xa7c21a),
             *(undefined1 *)(param_1 + 0xa7c21b)), 0 < DebugLevel)) {
    printk("%s(): ring_idx: %d, dump_entry_total_num: %d, valid_entry_num: %d\n",
           "mt7915_rxv_dump_show_list",*(undefined1 *)(param_1 + 0xa7c21c),
           *(undefined1 *)(param_1 + 0xa7c21d),*(undefined1 *)(param_1 + 0xa7c21e));
  }
  if (*(char *)(param_1 + 0xa7c218) == '\0') {
    piVar6 = *(int **)(param_1 + 0xa7c220);
    if (piVar6 == (int *)0x0) {
      if (-1 < DebugLevel) {
        printk("%s(): null pointer for dump entry list.\n","mt7915_rxv_dump_show_list");
      }
    }
    else {
      piVar10 = (int *)*piVar6;
      if (piVar6 != piVar10) {
        iVar4 = 0;
        piVar7 = piVar10;
        do {
          piVar7 = (int *)*piVar7;
          iVar4 = iVar4 + 1;
        } while (piVar6 != piVar7);
        if (iVar4 != 0) {
          piVar7 = (int *)*piVar10;
          do {
            piVar1 = piVar7;
            if (piVar6 == piVar10) {
              return 0;
            }
            if (0 < DebugLevel) {
              printk("    entry_idx: %d, type_num: %d\n",*(undefined1 *)(piVar10 + 2),
                     *(undefined1 *)((int)piVar10 + 9));
            }
            piVar10 = (int *)piVar10[3];
            if ((piVar10 != (int *)0x0) && (piVar7 = (int *)*piVar10, piVar10 != piVar7)) {
              iVar4 = 0;
              piVar8 = piVar7;
              do {
                piVar8 = (int *)*piVar8;
                iVar4 = iVar4 + 1;
              } while (piVar10 != piVar8);
              if (iVar4 != 0) {
                piVar8 = (int *)*piVar7;
                while (piVar2 = piVar8, piVar10 != piVar7) {
                  if (0 < DebugLevel) {
                    printk("        type_idx: %d, len: %d, usr_num: %d\n",
                           *(undefined1 *)(piVar7 + 2),*(undefined2 *)((int)piVar7 + 10),
                           *(undefined1 *)(piVar7 + 3));
                  }
                  piVar7 = (int *)piVar7[4];
                  if ((piVar7 != (int *)0x0) && (piVar8 = (int *)*piVar7, piVar7 != piVar8)) {
                    iVar4 = 0;
                    piVar9 = piVar8;
                    do {
                      piVar9 = (int *)*piVar9;
                      iVar4 = iVar4 + 1;
                    } while (piVar7 != piVar9);
                    if (iVar4 != 0) {
                      piVar9 = (int *)*piVar8;
                      while (piVar3 = piVar9, piVar7 != piVar8) {
                        if (DebugLevel < 1) {
                          iVar4 = piVar8[3];
                          uVar13 = ((uint)*(ushort *)((int)piVar8 + 10) << 0x16) >> 0x18;
                          if (iVar4 != 0) {
LAB_0017de78:
                            if (uVar13 != 0) {
LAB_0017de80:
                              uVar11 = 0;
                              uVar12 = 0;
                              iVar5 = DebugLevel;
                              do {
                                if ((((0 < iVar5) &&
                                     (printk("(DW%02d):%08X  ",uVar11,
                                             *(undefined4 *)(iVar4 + uVar11 * 4)),
                                     iVar5 = DebugLevel, (uVar12 & 3) == 3)) && (0 < DebugLevel)) &&
                                   (printk(&_LC43), iVar5 = DebugLevel, 0 < DebugLevel)) {
                                  printk("                ");
                                  iVar5 = DebugLevel;
                                }
                                uVar11 = uVar11 + 1;
                                uVar12 = uVar11 & 0xff;
                              } while (uVar12 < uVar13);
                              goto LAB_0017dea0;
                            }
                          }
                        }
                        else {
                          printk("            user_idx: %d, len: %d\n",*(undefined1 *)(piVar8 + 2),
                                 *(undefined2 *)((int)piVar8 + 10));
                          iVar4 = piVar8[3];
                          uVar13 = ((uint)*(ushort *)((int)piVar8 + 10) << 0x16) >> 0x18;
                          if (iVar4 != 0) {
                            if (DebugLevel < 1) goto LAB_0017de78;
                            printk("                ");
                            iVar5 = DebugLevel;
                            if (uVar13 != 0) goto LAB_0017de80;
LAB_0017dea0:
                            if (0 < iVar5) {
                              printk(&_LC43);
                            }
                          }
                        }
                        piVar9 = (int *)*piVar3;
                        piVar8 = piVar3;
                      }
                    }
                  }
                  piVar8 = (int *)*piVar2;
                  piVar7 = piVar2;
                }
              }
            }
            piVar7 = (int *)*piVar1;
            piVar10 = piVar1;
          } while( true );
        }
      }
      if (-1 < DebugLevel) {
        printk("%s(): empty dump entry list.\n","mt7915_rxv_dump_show_list");
      }
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s(): cannot access list in rxv dumping process.\n","mt7915_rxv_dump_show_list");
  }
  return 1;
}


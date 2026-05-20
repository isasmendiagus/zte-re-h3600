// module: mt7915.ko
// function: mt7915_rxv_dump_buf_alloc @ 0x17e898
// size: 488 bytes
//

undefined4 mt7915_rxv_dump_buf_alloc(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  char cVar6;
  int *piVar7;
  undefined1 auStack_38 [8];
  undefined1 local_30;
  char local_2f;
  int local_2c [2];
  
  if (*(char *)(param_1 + 0xa7c218) == '\0') {
    if (*(int *)(param_1 + 0xa7c220) == 0) {
      iVar2 = os_alloc_mem(param_1,param_1 + 0xa7c220,8);
      if (iVar2 == 0) {
        piVar7 = *(int **)(param_1 + 0xa7c220);
        *piVar7 = (int)piVar7;
        piVar7[1] = (int)piVar7;
        uVar4 = 0;
        cVar6 = '\0';
        do {
          uVar1 = uVar4 & 0xff;
          uVar4 = uVar4 + 1;
          if ((param_2 >> uVar1 & 1) != 0) {
            cVar6 = cVar6 + '\x01';
          }
        } while (uVar4 != 4);
        iVar2 = 0;
        while( true ) {
          os_zero_mem(auStack_38,0x10);
          local_30 = (undefined1)iVar2;
          local_2f = cVar6;
          iVar3 = os_alloc_mem(param_1,local_2c,8);
          iVar2 = iVar2 + 1;
          if (iVar3 != 0) break;
          *(int *)local_2c[0] = local_2c[0];
          *(int *)(local_2c[0] + 4) = local_2c[0];
          iVar3 = FUN_0017ae6c(param_1,piVar7,auStack_38,2);
          if (iVar3 != 0) {
            if (DebugLevel < 0) {
              return 1;
            }
            printk("%s(): link list install fail.\n","mt7915_rxv_dump_buf_alloc");
            return 1;
          }
          if (iVar2 == 10) {
            *(char *)(param_1 + 0xa7c21a) = (char)param_2;
            *(char *)(param_1 + 0xa7c21b) = cVar6;
            *(undefined1 *)(param_1 + 0xa7c21c) = 0;
            piVar5 = (int *)*piVar7;
            cVar6 = '\0';
            if (piVar7 != piVar5) {
              cVar6 = '\0';
              do {
                piVar5 = (int *)*piVar5;
                cVar6 = cVar6 + '\x01';
              } while (piVar7 != piVar5);
            }
            *(char *)(param_1 + 0xa7c21d) = cVar6;
            *(undefined1 *)(param_1 + 0xa7c21e) = 0;
            *(undefined1 *)(param_1 + 0xa7c219) = 1;
            return 0;
          }
        }
      }
      if (-1 < DebugLevel) {
        printk("%s(): allocate memory fail.\n","mt7915_rxv_dump_buf_alloc");
        return 1;
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s(): no need to alloc buf for nonempty list.\n","mt7915_rxv_dump_buf_alloc");
      return 1;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s(): cannot alloc buf when enable dump process.\n","mt7915_rxv_dump_buf_alloc");
    return 1;
  }
  return 1;
}


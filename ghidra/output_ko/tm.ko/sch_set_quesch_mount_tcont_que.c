// module: tm.ko
// function: sch_set_quesch_mount_tcont_que @ 0x3dcd0
// size: 360 bytes
//

int sch_set_quesch_mount_tcont_que(uint param_1,uint *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  
  if (g_tm_debug_level < 7) {
    if (0x27 < param_1) {
      return 1;
    }
    uVar1 = *param_2;
    if (0xff < uVar1) {
      return 1;
    }
  }
  else {
    printk("[TM][sch_set_quesch_mount_tcont_que]input: tcont = %d, que_mask:0x%x:%x:%x:%x\n",param_1
           ,param_2[3],param_2[2],param_2[1],*param_2);
    if ((0x27 < param_1) || (uVar1 = *param_2, 0xff < uVar1)) goto LAB_0003ddbc;
  }
  if (((param_2[1] < 0x100) && (param_2[2] < 0x100)) && (param_2[3] < 0x100)) {
    puVar4 = param_2 + -1;
    uVar3 = 0;
    do {
      puVar4 = puVar4 + 1;
      uVar3 = (uVar3 ^ *puVar4) & 0xff;
    } while (puVar4 != param_2 + 3);
    if (uVar3 != 0xff) {
      if (g_tm_debug_level < 7) {
        return 1;
      }
      printk("[TM][sch_set_quesch_mount_tcont_que]input invalid ena_mask!\n");
      return 1;
    }
    iVar2 = tmOnuRegWrite(0x12,param_2[2] << 0x10 | param_2[1] << 8 | uVar1 | param_2[3] << 0x18,
                          param_1,&SchRegTable);
    if (iVar2 == 0) {
      return 0;
    }
    if (g_tm_debug_level != 0) {
      printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_sch.c",0x4e2);
      return iVar2;
    }
    return iVar2;
  }
LAB_0003ddbc:
  if (6 < g_tm_debug_level) {
    printk("[TM][sch_set_quesch_mount_tcont_que]input invalid tcont!\n");
  }
  return 1;
}


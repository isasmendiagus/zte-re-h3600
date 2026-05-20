// module: tm.ko
// function: sch_get_quesch_mount_tcont_que @ 0x3de38
// size: 292 bytes
//

int sch_get_quesch_mount_tcont_que(uint param_1,undefined4 *param_2)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint *puVar4;
  uint local_14;
  
  local_14 = 0;
  if (g_tm_debug_level < 7) {
    if (param_1 < 0x28) {
LAB_0003de78:
      iVar2 = tmOnuRegRead(0x12,&local_14,param_1,&SchRegTable);
      if (iVar2 != 0) {
        if (g_tm_debug_level == 0) {
          return iVar2;
        }
        printk("ERROR:(%s:%d) reg read fail\n","tm/src/pon_tm_sch.c",0x507);
        return iVar2;
      }
      puVar4 = param_2 + -1;
      uVar3 = 0;
      do {
        uVar1 = uVar3 & 0xff;
        uVar3 = uVar3 + 8;
        puVar4 = puVar4 + 1;
        *puVar4 = local_14 >> uVar1 & 0xff;
      } while (puVar4 != param_2 + 3);
      if (6 < g_tm_debug_level) {
        printk("[TM][sch_get_quesch_mount_tcont_que]output:que_mask = 0x%x:%x:%x:%x\n",param_2[3],
               param_2[2],param_2[1],*param_2);
        return 0;
      }
      return 0;
    }
  }
  else {
    printk("[TM][sch_get_quesch_mount_tcont_que]input: tcont = %d secsch_id = %d\n",param_1);
    if (param_1 < 0x28) goto LAB_0003de78;
    if (6 < g_tm_debug_level) {
      printk("[TM][sch_get_quesch_mount_tcont_que]input invalid parameter!\n");
    }
  }
  return 1;
}


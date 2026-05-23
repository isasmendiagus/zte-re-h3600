// module: tm.ko
// function: tm_tcont_secsch_hang_que_set @ 0x4c09c
// size: 268 bytes
//

undefined4 tm_tcont_secsch_hang_que_set(undefined4 param_1,uint param_2,uint param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  uint local_20 [4];
  
  bVar6 = 2 < param_3;
  bVar5 = param_3 == 3;
  if (param_3 < 4) {
    bVar6 = 6 < param_2;
    bVar5 = param_2 == 7;
  }
  local_20[0] = 0;
  local_20[1] = 0;
  local_20[2] = 0;
  local_20[3] = 0;
  if (bVar6 && !bVar5) {
    printk("[TM][API]tm_tcont_secsch_hang_que_set para invalid: que_id(%d) p_secsch_id(%d)\n");
  }
  iVar1 = sch_get_quesch_mount_tcont_que(param_1,local_20);
  if (iVar1 == 0) {
    if ((local_20[param_3] >> (param_2 & 0xff) & 1) == 0) {
      uVar4 = ~(1 << (param_2 & 0xff));
      uVar3 = 0;
      do {
        if ((uVar3 != param_3) && ((local_20[uVar3] >> (param_2 & 0xff) & 1) != 0)) {
          local_20[uVar3] = local_20[uVar3] & uVar4;
        }
        uVar3 = uVar3 + 1;
      } while (uVar3 != 4);
      local_20[param_3] = local_20[param_3] & uVar4 | 1 << (param_2 & 0xff);
      iVar1 = sch_set_quesch_mount_tcont_que(param_1,local_20);
      if (iVar1 != 0) {
        printk("tm_tcont_que_sch_sp_dwwr_mod_set fail\n");
        return 0xffffffff;
      }
    }
    uVar2 = 0;
  }
  else {
    printk("tm_tcont_secsch_hang_que_set quesch_mount get failed\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}


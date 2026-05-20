// module: tm.ko
// function: tm_tcont_secsch_hang_que_get @ 0x54774
// size: 144 bytes
//

undefined4 tm_tcont_secsch_hang_que_get(undefined4 param_1,uint param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint local_20 [4];
  
  local_20[0] = 0;
  local_20[1] = 0;
  local_20[2] = 0;
  local_20[3] = 0;
  if (7 < param_2) {
    printk("[TM][API]tm_tcont_secsch_hang_que_set para invalid:que_id(%d)\n");
  }
  iVar1 = sch_get_quesch_mount_tcont_que(param_1,local_20);
  iVar2 = 0;
  if (iVar1 == 0) {
    do {
      if ((local_20[iVar2] >> (param_2 & 0xff) & 1) != 0) {
        *param_3 = iVar2;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 != 4);
    uVar3 = 0;
  }
  else {
    printk("tm_tcont_secsch_hang_que_get mount_tcont_que fail\n");
    uVar3 = 0xffffffff;
  }
  return uVar3;
}


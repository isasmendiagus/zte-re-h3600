// module: switch.ko
// function: sw_qos_init @ 0x18918
// size: 228 bytes
//

void sw_qos_init(void)

{
  undefined4 in_r3;
  uint uVar1;
  uint uVar2;
  
  dev_qos_select_queue = sw_qos_select_queue;
  if ((g_pon_work_mode & 0x10) != 0) {
    return;
  }
  qos_global_para_clr();
  uVar2 = (uint)g_tcont_start;
  uVar1 = (uint)g_tcont_size;
  TCONT_QUEUE = 8;
  if (uVar1 <= uVar2) {
    return;
  }
  do {
    tm_tcont_secsch_hang_que_set(uVar2,0,0,uVar1,in_r3);
    tm_tcont_secsch_hang_que_set(uVar2,1,0);
    tm_tcont_secsch_hang_que_set(uVar2,2,0);
    tm_tcont_secsch_hang_que_set(uVar2,3,0);
    tm_tcont_secsch_hang_que_set(uVar2,4,0);
    tm_tcont_secsch_hang_que_set(uVar2,5,0);
    tm_tcont_secsch_hang_que_set(uVar2,6,0);
    tm_tcont_secsch_hang_que_set(uVar2,7,0);
    uVar1 = (uint)g_tcont_size;
    uVar2 = uVar2 + 1;
  } while ((int)uVar2 < (int)uVar1);
  return;
}


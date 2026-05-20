// module: mt7915.ko
// function: expand_pkt_dynamic_page @ 0x1cf190
// size: 292 bytes
//

int expand_pkt_dynamic_page
              (undefined4 param_1,undefined4 param_2,int param_3,size_t param_4,int param_5,
              uint *param_6)

{
  int iVar1;
  uint uVar2;
  int local_1c;
  
  local_1c = 0;
  uVar2 = (param_5 + 0x3fU & 0xffffffe0) + 0xc0;
  if (uVar2 < 0x1001) {
    local_1c = netdev_alloc_frag(uVar2);
    if (local_1c == 0) {
      *param_6 = uVar2;
      goto LAB_001cf274;
    }
    g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + 1;
    *param_6 = uVar2;
LAB_001cf1f0:
    if (param_3 == 0) {
      return local_1c;
    }
    os_move_mem((void *)(local_1c + 0x20),(void *)(param_3 + 0x20),param_4);
  }
  else {
    os_alloc_mem(param_1,&local_1c,uVar2);
    *param_6 = uVar2;
    if (local_1c != 0) goto LAB_001cf1f0;
LAB_001cf274:
    if (param_3 == 0) goto LAB_001cf27c;
  }
  uVar2 = param_3 + 0x40000000U >> 0xc;
  g_stWlanRadioStat._8_4_ = g_stWlanRadioStat._8_4_ + -1;
  iVar1 = mem_map + uVar2 * 0x20;
  if ((*(uint *)(mem_map + uVar2 * 0x20) & 0x8000) != 0) {
    iVar1 = *(int *)(iVar1 + 0x1c);
  }
  put_page(iVar1);
  if (local_1c != 0) {
    return local_1c;
  }
LAB_001cf27c:
  if (1 < DebugLevel) {
    printk("Extend Rx buffer %d size packet failed! drop pkt.\n",param_5);
  }
  return 0;
}


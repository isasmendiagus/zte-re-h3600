// module: mt7915.ko
// function: set_vow_watf_q @ 0x481fc
// size: 592 bytes
//

undefined4 set_vow_watf_q(int param_1,char *param_2)

{
  undefined1 uVar1;
  uint uVar2;
  char *local_1c;
  uint local_18;
  undefined4 local_14 [2];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  if (*(char *)(param_1 + 0xa7a32c) == '\0') {
    return 0;
  }
  uVar2 = sscanf(param_2,"%u-%u",local_14,&local_18);
  if (uVar2 < 2) {
    if (DebugLevel < 0) {
      return 0;
    }
    printk(
          "Wrong format, vow_watf_q=[Level]-[Quantum]\n[Level] should be among 0 to 3 !\n[Quantum] unit is 256us.\n"
          );
    return 0;
  }
  os_alloc_mem(0,&local_1c,0x20);
  if (local_1c == (char *)0x0) {
    return 0;
  }
  uVar1 = (undefined1)local_18;
  switch(local_14[0]) {
  case 0:
    *(undefined1 *)(param_1 + 0xa7a32d) = uVar1;
    snprintf(local_1c,0x20,"%d-%d",0,local_18 & 0xff);
    set_vow_sta_dwrr_quantum(param_1,local_1c);
    if (-1 < DebugLevel) {
      printk("vow_watf_q_lv0 is set to %d\n",*(undefined1 *)(param_1 + 0xa7a32d));
    }
    break;
  case 1:
    *(undefined1 *)(param_1 + 0xa7a32e) = uVar1;
    snprintf(local_1c,0x20,"%d-%d",1,local_18 & 0xff);
    set_vow_sta_dwrr_quantum(param_1,local_1c);
    if (-1 < DebugLevel) {
      printk("vow_watf_q_lv1 is set to %d\n",*(undefined1 *)(param_1 + 0xa7a32e));
    }
    break;
  case 2:
    *(undefined1 *)(param_1 + 0xa7a32f) = uVar1;
    snprintf(local_1c,0x20,"%d-%d",2,local_18 & 0xff);
    set_vow_sta_dwrr_quantum(param_1,local_1c);
    if (-1 < DebugLevel) {
      printk("vow_watf_q_lv2 is set to %d\n",*(undefined1 *)(param_1 + 0xa7a32f));
    }
    break;
  case 3:
    *(undefined1 *)(param_1 + 0xa7a330) = uVar1;
    snprintf(local_1c,0x20,"%d-%d",3,local_18 & 0xff);
    set_vow_sta_dwrr_quantum(param_1,local_1c);
    if (-1 < DebugLevel) {
      printk("vow_watf_q_lv3 is set to %d\n",*(undefined1 *)(param_1 + 0xa7a330));
    }
    break;
  default:
    if (DebugLevel < 0) goto LAB_0004830c;
    printk("vow_watf_q_lv is setting fail.\n");
  }
  if (local_1c == (char *)0x0) {
    return 1;
  }
LAB_0004830c:
  os_free_mem(local_1c);
  return 1;
}


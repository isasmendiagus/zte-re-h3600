// module: mt7915.ko
// function: set_veri_pkt_ctrl_en @ 0x1d70e0
// size: 844 bytes
//

undefined4 set_veri_pkt_ctrl_en(int param_1,char *param_2)

{
  char cVar1;
  char *pcVar2;
  char *__s;
  char *__s_00;
  char *__s_01;
  char *__s_02;
  char *__s_03;
  char *__s_04;
  char *__s_05;
  char *__s_06;
  int iVar3;
  uint uVar4;
  
  if (param_2 != (char *)0x0) {
    pcVar2 = strstr(param_2,"du:");
    __s = strstr(param_2,"na:");
    __s_00 = strstr(param_2,"tm:");
    __s_01 = strstr(param_2,"sn:");
    __s_02 = strstr(param_2,"txs2m:");
    __s_03 = strstr(param_2,"txs2h:");
    __s_04 = strstr(param_2,"pm:");
    __s_05 = strstr(param_2,"life:");
    __s_06 = strstr(param_2,"htc:");
    if (pcVar2 == (char *)0x0) {
      uVar4 = 0;
    }
    else {
      pcVar2 = strchr(pcVar2,0x3a);
      cVar1 = os_str_tol(pcVar2 + 1,0,10);
      if (cVar1 == '\0') {
        uVar4 = 0;
      }
      else {
        uVar4 = 0x10;
      }
    }
    if (__s != (char *)0x0) {
      pcVar2 = strchr(__s,0x3a);
      cVar1 = os_str_tol(pcVar2 + 1,0,10);
      if (cVar1 != '\0') {
        uVar4 = uVar4 | 0x80;
      }
    }
    if (__s_00 != (char *)0x0) {
      pcVar2 = strchr(__s_00,0x3a);
      cVar1 = os_str_tol(pcVar2 + 1,0,10);
      if (cVar1 != '\0') {
        uVar4 = uVar4 | 0x100;
      }
    }
    if (__s_01 != (char *)0x0) {
      pcVar2 = strchr(__s_01,0x3a);
      cVar1 = os_str_tol(pcVar2 + 1,0,10);
      if (cVar1 != '\0') {
        uVar4 = uVar4 | 8;
      }
    }
    if (__s_02 != (char *)0x0) {
      pcVar2 = strchr(__s_02,0x3a);
      cVar1 = os_str_tol(pcVar2 + 1,0,10);
      if (cVar1 != '\0') {
        uVar4 = uVar4 | 0x400;
      }
    }
    if (__s_03 != (char *)0x0) {
      pcVar2 = strchr(__s_03,0x3a);
      cVar1 = os_str_tol(pcVar2 + 1,0,10);
      if (cVar1 != '\0') {
        uVar4 = uVar4 | 0x800;
      }
    }
    if (__s_04 != (char *)0x0) {
      pcVar2 = strchr(__s_04,0x3a);
      cVar1 = os_str_tol(pcVar2 + 1,0,10);
      if (cVar1 != '\0') {
        uVar4 = uVar4 | 4;
      }
    }
    if (__s_05 != (char *)0x0) {
      pcVar2 = strchr(__s_05,0x3a);
      cVar1 = os_str_tol(pcVar2 + 1,0,10);
      if (cVar1 != '\0') {
        uVar4 = uVar4 | 0x1000;
      }
    }
    if (__s_06 != (char *)0x0) {
      pcVar2 = strchr(__s_06,0x3a);
      cVar1 = os_str_tol(pcVar2 + 1,0,10);
      if (cVar1 != '\0') {
        uVar4 = uVar4 | 0x2000;
        *(int *)(param_1 + 0xa7cc68) = *(int *)(param_1 + 0xa7cc68) + 4;
      }
    }
    *(uint *)(param_1 + 0xa7cc58) = uVar4 | *(uint *)(param_1 + 0xa7cc58);
  }
  if (((0 < DebugLevel) && (printk("verify_pkt ctrl_en status:\n"), 0 < DebugLevel)) &&
     (printk("\tdu:\tno_ack:\ttm:\tsn:\ttxs2m:\ttxs2h:\tpm:\thtc:\n"), 0 < DebugLevel)) {
    iVar3 = *(int *)(param_1 + 0xa7cc58);
    printk("\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",(uint)(iVar3 << 0x1b) >> 0x1f,
           (uint)(iVar3 << 0x18) >> 0x1f,(uint)(iVar3 << 0x17) >> 0x1f,(uint)(iVar3 << 0x1c) >> 0x1f
           ,(uint)(iVar3 << 0x15) >> 0x1f,(uint)(iVar3 << 0x14) >> 0x1f,
           (uint)(iVar3 << 0x1d) >> 0x1f,(uint)(iVar3 << 0x12) >> 0x1f);
  }
  return 1;
}


// module: mt7915.ko
// function: WPABuildPairMsg3 @ 0x11f37c
// size: 808 bytes
//

void WPABuildPairMsg3(int param_1,uint *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  char cVar4;
  int local_c4;
  undefined4 local_be;
  undefined2 local_ba;
  uint local_b8;
  undefined2 local_b4;
  undefined2 local_b2;
  undefined4 local_b0;
  undefined4 local_ac;
  uint local_a8;
  undefined2 local_a4;
  undefined1 local_a2;
  undefined1 local_a1;
  undefined1 auStack_a0 [114];
  undefined1 auStack_2e [10];
  
  memset(&local_b0,0,0x88);
  if (2 < DebugLevel) {
    printk("===> %s\n","WPABuildPairMsg3");
  }
  os_alloc_mem(0,&local_c4,0x5dc);
  iVar1 = local_c4;
  if (local_c4 == 0) {
    if (-1 < DebugLevel) {
      printk("!!!%s : no memory!!!\n","WPABuildPairMsg3");
    }
  }
  else {
    __memzero(local_c4,0x5dc);
    uVar3 = 8;
    do {
      uVar3 = uVar3 - 1 & 0xff;
      cVar4 = *(char *)((int)param_2 + uVar3 + 0x390) + '\x01';
      *(char *)((int)param_2 + uVar3 + 0x390) = cVar4;
    } while (uVar3 != 0 && cVar4 == '\0');
    iVar2 = *(int *)(param_3 + 8);
    if (iVar2 != 0) {
      AsicGetTxTsc(param_1,iVar2,iVar2 + 0x3c7);
    }
    os_zero_mem(&local_b0,0x88);
    local_a4 = *(undefined2 *)(param_3 + 0xe0);
    local_a2 = *(undefined1 *)(param_3 + 0xe4);
    local_a8 = param_2[0x52];
    local_a1 = (undefined1)param_2[0x53];
    local_ac = 2;
    local_b0 = 0;
    os_move_mem(auStack_2e,(void *)(param_3 + 0xec),6);
    if (((*param_2 & 0x30000) == 0) && ((char)param_2[0xa1] != '\x02')) {
      os_move_mem(auStack_a0,(void *)((int)param_2 + 0x1ee),0x20);
    }
    else {
      os_move_mem(auStack_a0,(void *)((int)param_2 + 0x206),0x20);
    }
    if (*(short *)(param_3 + 0xe0) == *(short *)(&DAT_002963c2 + param_1)) {
      if (2 < DebugLevel) {
        printk("\n%s: Clear Wcid = %d FragBuffer !!!!!\n","WPABuildPairMsg3");
      }
      *(undefined4 *)(&DAT_002963b4 + param_1) = 0;
      *(undefined2 *)(&DAT_002963b8 + param_1) = 0;
      *(undefined4 *)(&DAT_002963bc + param_1) = 0;
      (&DAT_002963c5)[param_1] = 0;
      *(undefined2 *)(&DAT_002963ba + param_1) = 0;
      *(undefined2 *)(&DAT_002963c2 + param_1) = 0;
      *(undefined4 *)(&DAT_002963c8 + param_1) = 0;
      *(undefined4 *)(&DAT_002963cc + param_1) = 0;
      (&DAT_002963c4)[param_1] = 0;
    }
    WPAInstallKey(param_1,&local_b0,1,1);
    *(undefined1 *)((int)param_2 + 0x39a) = 3;
    WPAConstructEapolMsg(param_3,3,param_2,*(int *)(param_3 + 8) + 0x2c,iVar1);
    local_be = *(undefined4 *)((int)param_2 + 0x32a);
    local_b4 = (undefined2)param_2[0xca];
    local_b8 = param_2[0xc9];
    local_ba = *(undefined2 *)((int)param_2 + 0x32e);
    local_b2 = EAPOL;
    RTMPToWirelessSta(param_1,param_3,&local_be,0xe,iVar1,
                      CONCAT11(*(undefined1 *)(iVar1 + 2),*(undefined1 *)(iVar1 + 3)) + 4,
                      *(char *)(param_1 + (uint)*(ushort *)(param_3 + 0xe0) * 0x620 + 0x2f762) !=
                      '\x01');
    RTMPSetTimer(param_2 + 0xe9,1000);
    os_free_mem(local_c4);
    if (2 < DebugLevel) {
      printk("<=== %s: send Msg3 of 4-way\n","WPABuildPairMsg3");
    }
    __ZTE_STA_Assoc_Process(param_1,7,0,0,0,0,param_3,"WPABuildPairMsg3",0x138b);
  }
  return;
}


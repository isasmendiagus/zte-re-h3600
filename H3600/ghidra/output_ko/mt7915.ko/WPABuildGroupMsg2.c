// module: mt7915.ko
// function: WPABuildGroupMsg2 @ 0x1201f0
// size: 508 bytes
//

void WPABuildGroupMsg2(int param_1,int param_2,int *param_3)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  int local_34;
  undefined4 local_2e;
  undefined2 local_2a;
  undefined4 local_28;
  undefined2 local_24;
  undefined2 local_22;
  
  if (2 < DebugLevel) {
    printk("===> %s\n","WPABuildGroupMsg2");
  }
  os_alloc_mem(0,&local_34,0x5dc);
  iVar3 = local_34;
  if (local_34 == 0) {
    if (-1 < DebugLevel) {
      printk("!!!%s : no memory!!!\n","WPABuildGroupMsg2");
    }
  }
  else {
    __memzero(local_34,0x5dc);
    WPAConstructEapolMsg(param_3,6,param_2,param_2,iVar3);
    if ((((*(char *)(param_1 + 0x286285) == '\x01' && param_3 != (int *)0x0) && (*param_3 == 2)) &&
        (*(byte *)(param_3 + 0x39) < 2)) &&
       (((uVar2 = *(ushort *)(param_3 + 0x38),
         uVar4 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)), uVar2 < uVar4 &&
         (*(ushort *)(param_3 + 0x38) < 0x120)) &&
        ((iVar1 = (uint)*(ushort *)(param_3 + 0x38) * 0x620, param_1 + iVar1 != -0x2f6a0 &&
         (*(char *)(param_1 + iVar1 + 0x2f762) == '\x01')))))) {
      MWDSAPCliPeerEnable(param_1,&DAT_0036db58 +
                                  (uint)*(byte *)(param_3 + 0x39) * 0x2137b0 + param_1,param_3);
    }
    local_2e = *(undefined4 *)(param_2 + 0x324);
    local_2a = *(undefined2 *)(param_2 + 0x328);
    local_28 = *(undefined4 *)(param_2 + 0x32a);
    local_24 = *(undefined2 *)(param_2 + 0x32e);
    local_22 = EAPOL;
    RTMPToWirelessSta(param_1,param_3,&local_2e,0xe,iVar3,
                      CONCAT11(*(undefined1 *)(iVar3 + 2),*(undefined1 *)(iVar3 + 3)) + 4,0);
    os_free_mem(local_34);
    if (2 < DebugLevel) {
      printk("<=== %s : send out Group Message 2\n","WPABuildGroupMsg2");
    }
  }
  return;
}


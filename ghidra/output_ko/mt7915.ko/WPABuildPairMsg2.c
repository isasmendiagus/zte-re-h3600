// module: mt7915.ko
// function: WPABuildPairMsg2 @ 0x11f1b4
// size: 448 bytes
//

void WPABuildPairMsg2(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int local_2c;
  undefined4 local_26;
  undefined2 local_22;
  undefined4 local_20;
  undefined2 local_1c;
  undefined2 local_1a;
  
  if (param_3 == 0) {
    return;
  }
  os_alloc_mem(0,&local_2c,0x5dc);
  iVar2 = local_2c;
  if (local_2c == 0) {
    if (-1 < DebugLevel) {
      printk("!!!%s : no memory!!!\n","WPABuildPairMsg2");
    }
  }
  else {
    __memzero(local_2c,0x5dc);
    WPAConstructEapolMsg(param_3,2,param_2,param_2,iVar2);
    local_26 = *(undefined4 *)(param_2 + 0x324);
    local_22 = *(undefined2 *)(param_2 + 0x328);
    local_20 = *(undefined4 *)(param_2 + 0x32a);
    local_1c = *(undefined2 *)(param_2 + 0x32e);
    local_1a = EAPOL;
    if (*(char *)(param_2 + 0x595) == '\0') {
      uVar1 = 1;
    }
    else {
      uVar1 = 0;
      if (*(char *)(param_1 + (uint)*(ushort *)(param_3 + 0xe0) * 0x620 + 0x2f762) != '\x01') {
        uVar1 = 1;
      }
    }
    RTMPToWirelessSta(param_1,param_3,&local_26,0xe,iVar2,
                      CONCAT11(*(undefined1 *)(iVar2 + 2),*(undefined1 *)(iVar2 + 3)) + 4,uVar1);
    os_free_mem(local_2c);
    iVar2 = *(int *)(param_3 + 8);
    if ((iVar2 != 0) && (*(int *)(iVar2 + 0x14) == 2)) {
      if (*(byte *)(iVar2 + 0x1a) < 0xf) {
        uVar1 = 0x12f1;
        uVar3 = 0xffffffff;
      }
      else {
        uVar1 = 0x12f5;
        uVar3 = 0xfffffffb;
      }
      __ZTE_STA_Assoc_Process(param_1,6,0,uVar3,0,0,param_3,"WPABuildPairMsg2",uVar1);
    }
    if (2 < DebugLevel) {
      printk("<=== %s: send Msg2 of 4-way\n","WPABuildPairMsg2");
    }
  }
  return;
}


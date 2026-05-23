// module: mt7915.ko
// function: PeerPairMsg2Action @ 0x12070c
// size: 612 bytes
//

void PeerPairMsg2Action(undefined4 param_1,undefined4 param_2,uint *param_3,int param_4)

{
  void *pvVar1;
  int iVar2;
  uint *puVar3;
  int iVar4;
  size_t __n;
  uint uVar5;
  undefined1 uStack_b5;
  undefined1 auStack_b4 [20];
  undefined1 auStack_a0 [124];
  
  log_time_begin(1,auStack_b4);
  if (2 < DebugLevel) {
    printk("===> %s\n","PeerPairMsg2Action");
  }
  uVar5 = *(uint *)(param_4 + 0x908);
  if (uVar5 < 0x83) {
    return;
  }
  if ((byte)param_3[0xe6] < 8) {
    return;
  }
  if ((byte)param_3[0xe6] == 10) {
    if (DebugLevel < 0) {
      return;
    }
    printk("%s: reject the Replayed Msg2\n","PeerPairMsg2Action");
    return;
  }
  if ((*(byte *)(param_4 + 1) & 3) == 3) {
    if (uVar5 < 0x89) {
      return;
    }
    iVar4 = 0x1e;
    iVar2 = 0x26;
  }
  else {
    iVar4 = 0x18;
    iVar2 = 0x20;
  }
  pvVar1 = memmove(param_3 + 0xd4,(void *)(param_4 + iVar2 + 0x11),0x20);
  puVar3 = param_3 + 0xc9;
  if ((*param_3 & 0x30000) == 0) {
    if ((char)param_3[0xa1] != '\x02') {
      if ((*param_3 & 0x6000) == 0) {
        if ((char)param_3[0xa1] == '\x01') {
          __n = 0x30;
          WpaDerivePTK_KDF_256
                    ((int)param_3 + 0x18e,param_3 + 0xcc,puVar3,pvVar1,(int)param_3 + 0x32a,
                     auStack_a0,0x30);
        }
        else {
          __n = 0x40;
          WpaDerivePTK((int)param_3 + 0x18e,param_3 + 0xcc);
        }
      }
      else {
        __n = 0x30;
        WpaDerivePTK_KDF_256
                  ((int)param_3 + 0x18e,param_3 + 0xcc,puVar3,pvVar1,(int)param_3 + 0x32a,auStack_a0
                   ,0x30);
        hex_dump(&_LC175,auStack_a0,0x30);
      }
      goto LAB_00120804;
    }
    __n = 0x30;
  }
  else {
    __n = 0x58;
  }
  WpaDerivePTK_KDF_384
            ((int)param_3 + 0x18e,param_3 + 0xcc,puVar3,pvVar1,(int)param_3 + 0x32a,auStack_a0,__n);
  hex_dump("PTK SHA384",auStack_a0,__n);
LAB_00120804:
  iVar2 = WpaMessageSanity(param_1,param_4 + iVar2,(uVar5 - 8) - iVar4,2,param_3,param_2,auStack_a0)
  ;
  if (iVar2 != 0) {
    memcpy((void *)((int)param_3 + 0x1ce),auStack_a0,__n);
    RTMPCancelTimer(param_3 + 0xe9,&uStack_b5);
    *(undefined1 *)(param_3 + 0xe6) = 9;
    *(undefined1 *)(param_3 + 0xf6) = 0;
    WPABuildPairMsg3(param_1,param_3,param_2);
    log_time_end(2,"peer_msg2",1,auStack_b4);
  }
  return;
}


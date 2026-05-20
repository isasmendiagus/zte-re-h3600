// module: mt7915.ko
// function: RRM_PeerMeasureReqAction @ 0x223570
// size: 468 bytes
//

void RRM_PeerMeasureReqAction(undefined4 param_1,int param_2)

{
  int iVar1;
  uint *puVar2;
  uint __n;
  uint uVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  undefined1 local_61;
  byte local_60;
  undefined2 local_5f;
  undefined1 local_5d;
  void *local_5c;
  undefined4 local_56;
  undefined4 local_52;
  undefined4 local_4e;
  undefined1 local_4a;
  char acStack_49 [37];
  
  iVar4 = *(int *)(param_2 + 0x92c);
  local_61 = 0;
  local_5c = (void *)0x0;
  local_60 = 0;
  if ((iVar4 != 0) && (*(int *)(iVar4 + 0x14) == 2)) {
    if (3 < DebugLevel) {
      printk("%s:: \n","RRM_PeerMeasureReqAction");
    }
    iVar1 = RRM_PeerBeaconReqSanity
                      (param_1,param_2,*(undefined4 *)(param_2 + 0x908),&local_61,&local_5c,
                       &local_60,&local_5f,&local_56);
    if ((iVar1 != 0) &&
       (puVar2 = (uint *)get_scan_tab_by_wdev(param_1,iVar4), puVar2 != (uint *)0x0)) {
      snprintf(acStack_49,0x21,"%s",local_5c);
      acStack_49[local_60] = '\0';
      if (3 < DebugLevel) {
        printk("pSsid=%s\n",acStack_49);
        if (3 < DebugLevel) {
          printk("SsidLen=%d\n",local_60);
        }
      }
      uVar7 = *puVar2;
      if (uVar7 != 0) {
        puVar5 = puVar2 + 2;
        uVar6 = 0;
        do {
          uVar3 = (uint)local_60;
          if (uVar3 == 0) {
LAB_002236b4:
            RRM_EnqueuePeerBeaconRep
                      (param_1,param_2 + 10,param_2 + 4,local_61,CONCAT12(local_5d,local_5f),
                       local_56,local_52,local_4e,local_4a,puVar5);
            uVar7 = *puVar2;
          }
          else {
            __n = (uint)(byte)puVar5[0x25];
            if (uVar3 <= (byte)puVar5[0x25]) {
              __n = uVar3;
            }
            iVar4 = memcmp((void *)((int)puVar5 + 0x95),local_5c,__n);
            if (iVar4 == 0) goto LAB_002236b4;
          }
          uVar6 = uVar6 + 1;
          puVar5 = puVar5 + 0x2bd;
        } while (uVar6 < uVar7);
      }
    }
  }
  return;
}


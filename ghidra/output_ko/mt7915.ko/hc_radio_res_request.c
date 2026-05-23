// module: mt7915.ko
// function: hc_radio_res_request @ 0xaa034
// size: 636 bytes
//

undefined4 hc_radio_res_request(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined1 *puVar8;
  
  iVar5 = *(int *)(param_1 + 0xabc);
  iVar2 = hdev_obj_state_ready(iVar5);
  if (iVar2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s(): wdev=%d, hobj is not ready!\n","hc_radio_res_request",
             *(undefined1 *)(param_1 + 0xc));
      return 0;
    }
  }
  else {
    uVar4 = *(undefined4 *)(iVar5 + 8);
    iVar2 = rc_radio_equal(uVar4,*(undefined4 *)(param_2 + 4));
    if (iVar2 != 0) {
      if (2 < DebugLevel) {
        printk("%s(): radio is equal, prim_ch=%d, rx stream:%x!\n","hc_radio_res_request",
               *(undefined1 *)(*(int *)(param_2 + 4) + 5),*(undefined1 *)(*(int *)(param_2 + 4) + 8)
              );
        return 1;
      }
      return 1;
    }
    iVar2 = rc_radio_res_acquire(uVar4,param_2);
    if (iVar2 == 1) {
      iVar7 = *(int *)(param_1 + 0xabc);
      uVar4 = *(undefined4 *)(param_1 + 8);
      iVar5 = *(int *)(param_2 + 4);
      cVar1 = *param_2;
      iVar2 = hdev_obj_state_ready(iVar7);
      if (iVar2 != 0) {
        puVar8 = *(undefined1 **)(iVar7 + 8);
        QBSS_LoadStatusClear(*(undefined4 *)(param_1 + 8),*(undefined1 *)(iVar5 + 5));
        puVar6 = (undefined4 *)(puVar8 + 0xc);
        iVar2 = *(int *)(*(int *)(puVar8 + 0x18) + 0x4328);
        for (puVar3 = (undefined4 *)*puVar6; puVar6 != puVar3; puVar3 = (undefined4 *)*puVar3) {
          RTMPSuspendMsduTransmission
                    (*(undefined4 *)(*(int *)(iVar2 + (uint)*(byte *)(puVar3 + -5) * 4 + 0xc) + 8));
        }
        AsicSwitchChannel(*(undefined4 *)(param_1 + 8),*puVar8,iVar5,cVar1 == '\x01');
        AsicSetBW(*(undefined4 *)(param_1 + 8),*(undefined1 *)(iVar5 + 3),*puVar8);
        RcUpdateRadio(puVar8,*(undefined1 *)(iVar5 + 3),*(undefined1 *)(iVar5 + 6),
                      *(undefined1 *)(iVar5 + 7),*(undefined1 *)(iVar5 + 4),
                      *(undefined1 *)(iVar5 + 8));
        RcUpdateChannel(puVar8,*(undefined1 *)(iVar5 + 5),cVar1 == '\x01');
        iVar2 = *(int *)(*(int *)(puVar8 + 0x18) + 0x4328);
        for (puVar3 = *(undefined4 **)(puVar8 + 0xc); puVar6 != puVar3;
            puVar3 = (undefined4 *)*puVar3) {
          iVar5 = *(int *)(iVar2 + (uint)*(byte *)(puVar3 + -5) * 4 + 0xc);
          if (*(char *)(iVar5 + 0x1a) == *(char *)(*(int *)(puVar8 + 4) + 4)) {
            RTMPResumeMsduTransmission();
          }
          else {
            RTMPSuspendMsduTransmission(*(undefined4 *)(iVar5 + 8),iVar5);
          }
        }
        DfsInitDedicatedScanStart(uVar4);
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s(): wdev=%d, hobj is not ready!\n","hc_radio_update",
               *(undefined1 *)(param_1 + 0xc));
        return 1;
      }
      return 1;
    }
    if (2 < DebugLevel) {
      printk("%s(): can\'t acquire radio resource!\n","hc_radio_res_request");
      return 0;
    }
  }
  return 0;
}


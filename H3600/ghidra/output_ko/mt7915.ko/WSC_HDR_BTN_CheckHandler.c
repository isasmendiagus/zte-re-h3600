// module: mt7915.ko
// function: WSC_HDR_BTN_CheckHandler @ 0x1ece08
// size: 368 bytes
//

void WSC_HDR_BTN_CheckHandler(int *param_1)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  uint local_14;
  
  iVar4 = *param_1;
  iVar1 = hc_get_hif_type(param_1[0x29e5e8]);
  if (iVar1 == 2) {
    if (0 < DebugLevel) {
      printk("%s(%d): Not support for HIF_MT yet!\n","WSC_HDR_BTN_CheckHandler",0x3257);
    }
  }
  else {
    mac_io_read32(param_1[0x29e5e8],0x228,&local_14);
    if ((param_1[0x28e7e3] & 2U) == 0) {
      uVar3 = 8;
    }
    else {
      uVar3 = 1;
    }
    if ((uVar3 & local_14) == 0) {
      if (*(char *)((int)param_1 + 0x795971) != '\x14') {
        *(char *)((int)param_1 + 0x795971) = *(char *)((int)param_1 + 0x795971) + '\x01';
        return;
      }
      *(undefined1 *)((int)param_1 + 0x795971) = 0;
      if (-1 < DebugLevel) {
        printk("wsc> execute WSC PBC...\n");
      }
      cVar2 = *(char *)((int)param_1 + 0x286285);
      if (cVar2 == '\x01') {
        *(undefined4 *)(iVar4 + 0x3c) = 0;
        Set_AP_WscMode_Proc(param_1,&_LC266);
        Set_AP_WscGetConf_Proc(param_1,&_LC267);
        cVar2 = *(char *)((int)param_1 + 0x286285);
      }
      if (cVar2 != '\0') {
        return;
      }
      *(undefined4 *)(iVar4 + 0x3c) = 0;
      Set_WscConfMode_Proc(param_1,&_LC267);
      iVar1 = Set_WscMode_Proc(param_1,&_LC266);
      if (iVar1 == 0) {
        return;
      }
      Set_WscGetConf_Proc(param_1,&_LC267);
      return;
    }
  }
  *(undefined1 *)((int)param_1 + 0x795971) = 0;
  return;
}


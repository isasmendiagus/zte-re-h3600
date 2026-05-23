// module: mt7915.ko
// function: ApCliIfUp @ 0x69a50
// size: 716 bytes
//

void ApCliIfUp(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  char *pcVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  
  if ((*(uint *)(param_1 + 0xa39f84) & 0x10020040) != 0x10000000) {
    return;
  }
  pcVar4 = &DAT_00580e8c + param_1;
  piVar6 = (int *)(s_MSG_WATCH_TASK___d_00371b30 + param_1 + 0xc);
  puVar3 = (undefined4 *)(&DAT_0036db58 + param_1);
  iVar5 = param_1 + 0x36ee89;
  iVar7 = 0;
  do {
    if (((((*pcVar4 == '\x01') && (*(char *)(puVar3 + 10) != '\0')) &&
         (*(char *)(puVar3 + 0x2aa) != '\0')) &&
        ((iVar1 = HcIsRadioAcq(puVar3), iVar1 != 0 &&
         (iVar1 = RtmpOSNetDevIsUp(*puVar3), iVar1 == 1)))) &&
       ((*(uint *)(&DAT_00580e8c + param_1 + iVar7 * 0x2137b0) & 0xffff00) == 0x100)) {
      iVar1 = *piVar6;
      if (iVar1 == 0) {
        return;
      }
      if (*(char *)(iVar1 + 4) == '\x01') {
        if (2 < DebugLevel) {
          printk("%s:Switching mode: Continue\n","ApCliIfUp");
        }
      }
      else if (((*(byte *)((int)puVar3 + 0x1a) < 0xf) || (*(char *)(param_1 + 0x795074) != '\x01'))
              || ((iVar2 = RadarChannelCheck(param_1), iVar2 == 0 ||
                  (*(char *)(iVar1 + 4) != '\x02')))) {
        if ((char)piVar6[-199] == '\0') {
          if (2 < DebugLevel) {
LAB_00069c48:
            printk("(%s) ApCli interface[%d] startup.\n","ApCliIfUp",iVar7);
            if ((char)piVar6[-199] != '\0') goto LAB_00069be8;
          }
LAB_00069bf4:
          cntl_connect_request(puVar3,2,0,0);
        }
        else {
          if (*(int *)(iVar5 + -0x41) == 0x23 || *(int *)(iVar5 + -0x41) == 0x102)
          goto LAB_00069ad0;
          if (2 < DebugLevel) goto LAB_00069c48;
LAB_00069be8:
          if (*(int *)(iVar5 + -0x41) != 0x27) goto LAB_00069bf4;
          if (0 < DebugLevel) {
            printk("%s: Enqueue connect by BSSID for WPS\n","ApCliIfUp");
          }
          cntl_connect_request(puVar3,1,6,iVar5);
        }
        pcVar4[0x10] = '\0';
      }
      else if (pcVar4[0x10] == '\x01') {
        *(undefined2 *)(iVar1 + 2) = *(undefined2 *)(iVar1 + 8);
        if (2 < DebugLevel) {
          printk("ApCliIfUp - PeerExist\n");
        }
      }
      else if (2 < DebugLevel) {
        printk("ApCliIfUp - Stop probing while Radar state is silent\n");
      }
    }
LAB_00069ad0:
    puVar3 = puVar3 + 0x84dec;
    pcVar4 = pcVar4 + 0x2137b0;
    piVar6 = piVar6 + 0x84dec;
    iVar5 = iVar5 + 0x2137b0;
    iVar7 = iVar7 + 1;
    if (puVar3 == (undefined4 *)(param_1 + 0x794ab8)) {
      return;
    }
  } while( true );
}


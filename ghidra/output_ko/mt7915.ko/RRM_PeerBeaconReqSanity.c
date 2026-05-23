// module: mt7915.ko
// function: RRM_PeerBeaconReqSanity @ 0x223a18
// size: 1080 bytes
//

undefined4
RRM_PeerBeaconReqSanity
          (undefined4 param_1,int param_2,int param_3,undefined1 *param_4,undefined4 *param_5,
          char *param_6,undefined1 *param_7,undefined1 *param_8)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  uint uVar4;
  char *pcVar5;
  char *pcVar6;
  
  if (2 < DebugLevel) {
    printk("%s - Got STA Beacon Measurement Request\n","RRM_PeerBeaconReqSanity");
  }
  if ((param_2 == 0 || (param_7 == (undefined1 *)0x0 || param_4 == (undefined1 *)0x0)) ||
     (iVar3 = MacTableLookup(param_1,param_2 + 10), iVar3 == 0)) {
    return 0;
  }
  *param_4 = *(undefined1 *)(param_2 + 0x1a);
  if (*(char *)(param_2 + 0x1d) != '&') {
    return 0;
  }
  *param_7 = *(undefined1 *)(param_2 + 0x1f);
  param_7[1] = *(undefined1 *)(param_2 + 0x20);
  cVar1 = *(char *)(param_2 + 0x21);
  param_7[2] = cVar1;
  if (cVar1 == '\x05') {
    if (3 < DebugLevel) {
      printk("%s - STA PeerMeasurementType %d\n","RRM_PeerBeaconReqSanity");
    }
  }
  else if (-1 < DebugLevel) {
    printk("unhandled PeerMeasurementType: %d\n",cVar1);
  }
  *param_8 = *(undefined1 *)(param_2 + 0x22);
  param_8[1] = *(undefined1 *)(param_2 + 0x23);
  *(ushort *)(param_8 + 2) = *(ushort *)(param_2 + 0x24) << 8 | *(ushort *)(param_2 + 0x24) >> 8;
  *(ushort *)(param_8 + 4) = *(ushort *)(param_2 + 0x26) << 8 | *(ushort *)(param_2 + 0x26) >> 8;
  bVar2 = *(byte *)(param_2 + 0x28);
  param_8[6] = bVar2;
  if (2 < bVar2) {
    return 0;
  }
  if (bVar2 == 1) {
    if (-1 < DebugLevel) {
      printk("%s - STA RRM_BCN_REQ_MODE_ACTIVE\n","RRM_PeerBeaconReqSanity");
      goto LAB_00223c78;
    }
  }
  else if (bVar2 == 2) {
    if (-1 < DebugLevel) {
      printk("%s - STA RRM_BCN_REQ_MODE_BCNTAB\n","RRM_PeerBeaconReqSanity");
LAB_00223c78:
      iVar3 = DebugLevel;
      *(undefined4 *)(param_8 + 7) = *(undefined4 *)(param_2 + 0x29);
      *(undefined2 *)(param_8 + 0xb) = *(undefined2 *)(param_2 + 0x2d);
      if (3 < iVar3) {
        uVar4 = (uint)(byte)param_8[0xc];
        printk("%s BSSID: (%02x:%02x:%02x:%02x:%02x:%02x)\n","RRM_PeerBeaconReqSanity",param_8[7],
               param_8[8],param_8[9],param_8[10],param_8[0xb],uVar4);
        if (3 < DebugLevel) {
          printk("%s - IE_MEASUREMENT_REQUEST., RegClass=%d ChNum=%d RandTime=%d Duration=%d Mode %d\n"
                 ,"RRM_PeerBeaconReqSanity",*param_8,param_8[1],*(undefined2 *)(param_8 + 2),
                 *(undefined2 *)(param_8 + 4),param_8[6],uVar4);
        }
      }
      goto LAB_00223b90;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s - STA RRM_BCN_REQ_MODE_PASSIVE\n","RRM_PeerBeaconReqSanity");
    goto LAB_00223c78;
  }
  *(undefined4 *)(param_8 + 7) = *(undefined4 *)(param_2 + 0x29);
  *(undefined2 *)(param_8 + 0xb) = *(undefined2 *)(param_2 + 0x2d);
LAB_00223b90:
  uVar4 = (uint)*(byte *)(param_2 + 0x30);
  pcVar6 = (char *)(param_2 + 0x2f);
  pcVar5 = pcVar6 + uVar4 + 2;
  do {
    if ((char *)(param_2 + param_3) < pcVar5) {
      return 1;
    }
    cVar1 = *pcVar6;
    if (cVar1 == '\x01') {
      if (uVar4 != 2) {
        if (-1 < DebugLevel) {
          printk("%s - Invalid reporting information subelement length: %d\n",
                 "RRM_PeerBeaconReqSanity");
          return 0;
        }
        return 0;
      }
      if (pcVar6[2] != '\0') {
        if (-1 < DebugLevel) {
          printk("%s reporting information=%d is not supported\n","RRM_PeerBeaconReqSanity");
          return 0;
        }
        return 0;
      }
    }
    else if (cVar1 == '\0') {
      if (uVar4 == 0) {
        if (-1 < DebugLevel) {
          printk("%s - SSID subelement length wild card SSID %d\n","RRM_PeerBeaconReqSanity");
        }
      }
      else {
        if (0x20 < uVar4) {
          if (-1 < DebugLevel) {
            printk("%s - Invalid SSID subelement length: %d\n","RRM_PeerBeaconReqSanity");
            return 0;
          }
          return 0;
        }
        *param_5 = pcVar6 + 2;
        *param_6 = pcVar6[1];
      }
    }
    else if (cVar1 == '\x02') {
      if (uVar4 != 1) {
        if (-1 < DebugLevel) {
          printk("%s - Invalid reporting Detail subelement length: %d\n","RRM_PeerBeaconReqSanity");
          return 0;
        }
        return 0;
      }
      if (2 < (byte)pcVar6[2]) {
        if (DebugLevel < 0) {
          return 0;
        }
        printk("%s Invalid reporting detail: %d \n","RRM_PeerBeaconReqSanity");
        return 0;
      }
    }
    else if (-1 < DebugLevel) {
      printk("unknown Eid: %d\n",cVar1);
    }
    pcVar6 = pcVar6 + (byte)pcVar6[1] + 2;
    uVar4 = (uint)(byte)pcVar6[1];
    pcVar5 = pcVar6 + uVar4 + 2;
  } while( true );
}


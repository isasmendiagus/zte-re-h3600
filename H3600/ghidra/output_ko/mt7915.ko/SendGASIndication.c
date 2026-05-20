// module: mt7915.ko
// function: SendGASIndication @ 0x22b004
// size: 1200 bytes
//

void SendGASIndication(int param_1,byte *param_2)

{
  byte bVar1;
  char cVar2;
  byte *pbVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  undefined4 uVar7;
  uint uVar8;
  int iVar9;
  byte *local_2c [2];
  
  uVar8 = (uint)*param_2;
  pcVar5 = "RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + uVar8 * 0x5834 + param_1 + 0x1c;
  if (2 < DebugLevel) {
    printk(&_LC1,"SendGASIndication");
  }
  if (param_2[10] == dot11GASAdvertisementID) {
    iVar9 = uVar8 * 0x5834;
    iVar4 = param_1 + iVar9;
    cVar2 = "RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n"[iVar4 + 0x28];
    if (cVar2 == '\0') {
      _raw_spin_lock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar9 + 0x24);
      pcVar6 = *(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + iVar4 + 0x1c);
      if (pcVar5 != pcVar6) {
        do {
          iVar4 = memcmp(pcVar6 + 0xd,param_2 + 1,6);
          if (iVar4 == 0) {
            if (pcVar6[0x50] == '\0') {
              RTMPSetTimer(pcVar6 + 0x1c,0x1400);
              pcVar6[0x50] = '\x01';
            }
            break;
          }
          pcVar6 = *(char **)pcVar6;
        } while (pcVar5 != pcVar6);
      }
      _raw_spin_unlock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar9 + 0x24);
      GASSetPeerCurrentState(param_1,param_2,1);
      return;
    }
    if (cVar2 == '\x01') {
      os_alloc_mem(0,local_2c,0x11);
      if (local_2c[0] != (byte *)0x0) {
        __memzero(local_2c[0],0x11);
        pbVar3 = local_2c[0];
        *local_2c[0] = *param_2;
        memmove(local_2c[0] + 1,param_2 + 1,6);
        pbVar3[7] = 1;
        pbVar3[8] = 0;
        _raw_spin_lock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar9 + 0x24);
        for (pcVar6 = *(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + iVar4 + 0x1c);
            pcVar5 != pcVar6; pcVar6 = *(char **)pcVar6) {
          iVar4 = memcmp(pcVar6 + 0xd,param_2 + 1,6);
          if (iVar4 == 0) {
            pbVar3[9] = pcVar6[0x13];
            break;
          }
        }
        _raw_spin_unlock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar9 + 0x24);
        pbVar3[0xb] = 0;
        pbVar3[10] = 0x41;
        pbVar3[0xc] = 0;
        pbVar3[0xd] = 0;
        bVar1 = pcVar6[0x14];
        pbVar3[0xf] = 0;
        pbVar3[0x10] = 0;
        pbVar3[0xe] = bVar1;
        goto LAB_0022b374;
      }
    }
    else {
      if (cVar2 != '\x02') {
        if (DebugLevel < 0) {
          return;
        }
        printk("%s: should not in this case\n","SendGASIndication");
        return;
      }
      os_alloc_mem(0,local_2c,0x11);
      if (local_2c[0] != (byte *)0x0) {
        __memzero(local_2c[0],0x11);
        pbVar3 = local_2c[0];
        *local_2c[0] = *param_2;
        memmove(local_2c[0] + 1,param_2 + 1,6);
        pbVar3[7] = 2;
        pbVar3[8] = 0;
        _raw_spin_lock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar9 + 0x24);
        for (pcVar6 = *(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + iVar4 + 0x1c);
            pcVar5 != pcVar6; pcVar6 = *(char **)pcVar6) {
          iVar4 = memcmp(pcVar6 + 0xd,param_2 + 1,6);
          if (iVar4 == 0) {
            pbVar3[9] = pcVar6[0x13];
            break;
          }
        }
        _raw_spin_unlock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" + param_1 + iVar9 + 0x24);
        pbVar3[10] = 0;
        pbVar3[0xc] = 1;
        pbVar3[0xb] = 0;
        pbVar3[0xd] = 0;
        pbVar3[0xe] = pcVar6[0x14];
LAB_0022b374:
        GASSetPeerCurrentState(param_1,param_2,1);
        SendGASRsp(param_1,local_2c[0]);
        os_free_mem(local_2c[0]);
        return;
      }
    }
  }
  else {
    os_alloc_mem(0,local_2c,0x11);
    if (local_2c[0] != (byte *)0x0) {
      __memzero(local_2c[0],0x11);
      pbVar3 = local_2c[0];
      *local_2c[0] = *param_2;
      memmove(local_2c[0] + 1,param_2 + 1,6);
      pbVar3[7] = 1;
      pbVar3[8] = 0;
      _raw_spin_lock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" +
                        param_1 + uVar8 * 0x5834 + 0x24);
      pcVar6 = *(char **)("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" +
                         param_1 + uVar8 * 0x5834 + 0x1c);
      do {
        if (pcVar5 == pcVar6) {
          uVar7 = 0x10;
LAB_0022b118:
          _raw_spin_unlock_bh("RT_OID_WSC_SET_PROFILE:: ProfileCnt = %d\n" +
                              param_1 + uVar8 * 0x5834 + 0x24);
          pbVar3[0xb] = 0;
          pbVar3[0xc] = 0;
          pbVar3[0xd] = 0;
          pbVar3[10] = 0x3b;
          bVar1 = pcVar6[0x14];
          pbVar3[0xf] = 0;
          pbVar3[0x10] = 0;
          pbVar3[0xe] = bVar1;
          GASSetPeerCurrentState(param_1,param_2,1);
          MlmeEnqueue(param_1,0x27,1,uVar7,local_2c[0],0);
          RtmpOsMlmeUp(param_1 + 0x286298);
          os_free_mem(local_2c[0]);
          return;
        }
        iVar4 = memcmp(pcVar6 + 0xd,param_2 + 1,6);
        if (iVar4 == 0) {
          uVar7 = 0x11;
          pbVar3[9] = pcVar6[0x13];
          goto LAB_0022b118;
        }
        pcVar6 = *(char **)pcVar6;
      } while( true );
    }
  }
  if (-1 < DebugLevel) {
    printk("%s Not available memory\n","SendGASIndication");
  }
  return;
}


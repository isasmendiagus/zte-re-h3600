// module: mt7915.ko
// function: RTMPSendPackets @ 0x14fe00
// size: 628 bytes
//

undefined4 RTMPSendPackets(int param_1,int *param_2,undefined4 param_3,uint param_4,code *param_5)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int local_24 [2];
  
  iVar5 = *(int *)(param_1 + 8);
  local_24[0] = *param_2;
  if (iVar5 == 0) {
    printk(&_LC52,0x770);
    dump_stack();
    if (local_24[0] != 0) {
      RTMPFreeNdisPacket(0);
      return 0;
    }
    uVar2 = 0;
  }
  else {
    uVar7 = *(uint *)(iVar5 + 0xa39c70);
    *(uint *)(iVar5 + 0xa39c70) = uVar7 + 1;
    *(uint *)(iVar5 + 0xa39c74) = *(int *)(iVar5 + 0xa39c74) + (uint)(0xfffffffe < uVar7);
    wlan_dbg_radio_statistics_inc(0,0);
    if (local_24[0] == 0) {
      wlan_dbg_set_last_error(0,0,0x781,"RTMPSendPackets");
      uVar2 = 0;
    }
    else {
      if (param_4 < 0xe) {
        hex_dump("bad packet",*(undefined4 *)(local_24[0] + 0xcc),param_4);
        RTMPFreeNdisPacket(iVar5,local_24[0]);
        wlan_dbg_set_last_error(0,0,0x788,"RTMPSendPackets");
        *(int *)(iVar5 + 0x9dba8) = *(int *)(iVar5 + 0x9dba8) + 1;
        return 0;
      }
      if (*(char *)(iVar5 + 0xa7d07e) == '\x01') {
        RTMPFreeNdisPacket(iVar5,local_24[0]);
        uVar2 = 0;
        wlan_dbg_set_last_error(0,0,0x798,"RTMPSendPackets");
      }
      else {
        if (*(int *)(param_1 + 0x14) == 2 || *(int *)(param_1 + 0x14) == 0x40) {
          iVar6 = *(int *)(local_24[0] + 0xcc);
          bVar4 = *(byte *)(iVar5 + 0xa77bcf);
          if (((((bVar4 & 2) != 0) && (*(char *)(iVar5 + 0xa77bd0) == '\0')) &&
              (*(char *)(iVar5 + 0xa77bf2) != '\0')) && ((*(byte *)(iVar6 + 6) & 1) == 0)) {
            iVar3 = (*param_5)(*(undefined4 *)(iVar5 + 4),iVar6);
            if (iVar3 == 0) {
              os_move_mem((void *)(iVar5 + 0xa77bc9),(void *)(iVar6 + 6),6);
              bVar4 = *(byte *)(iVar5 + 0xa77bcf);
              *(undefined1 *)(iVar5 + 0xa77bd0) = 1;
            }
            else {
              bVar4 = *(byte *)(iVar5 + 0xa77bcf);
            }
          }
          if ((bVar4 == 2) && (iVar6 = os_equal_mem(iVar5 + 0x794b5b,iVar6 + 6,6), iVar6 == 0)) {
            RTMPFreeNdisPacket(iVar5,local_24[0]);
            wlan_dbg_set_last_error(0,0,0x7ac,"RTMPSendPackets");
            return 0;
          }
        }
        iVar6 = local_24[0];
        if (*(code **)(local_24[0] + 0x54) == (code *)0x0) {
          if (*(int *)(local_24[0] + 0x14) != 0) {
                    /* WARNING: Does not return */
            pcVar1 = (code *)software_udf(0x12,0x14ff88);
            (*pcVar1)();
          }
        }
        else {
          (**(code **)(local_24[0] + 0x54))(local_24[0]);
          *(undefined4 *)(iVar6 + 0x54) = 0;
          *(undefined4 *)(iVar6 + 0x14) = 0;
        }
        uVar2 = wdev_tx_pkts(iVar5,local_24,1,param_1);
      }
    }
  }
  return uVar2;
}


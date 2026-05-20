// module: mt7915.ko
// function: IAPP_L2_Update_Frame_Send @ 0x4ee9c
// size: 84 bytes
//

undefined4 IAPP_L2_Update_Frame_Send(undefined4 param_1,undefined4 param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  uVar1 = get_netdev_from_bssid(param_1,param_3 & 0xff);
  iVar2 = RtmpOsPktIappMakeUp(uVar1,param_2);
  if (iVar2 != 0) {
    announce_802_3_packet(param_1,iVar2,1);
    IAPP_L2_UpdatePostCtrl(param_1,param_2,param_3);
    return 1;
  }
  return 0;
}


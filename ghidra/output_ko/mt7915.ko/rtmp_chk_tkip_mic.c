// module: mt7915.ko
// function: rtmp_chk_tkip_mic @ 0x119e48
// size: 268 bytes
//

undefined4 rtmp_chk_tkip_mic(undefined4 param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  short sVar5;
  
  iVar4 = *(int *)(param_3 + 0x3c);
  sVar5 = *(short *)(param_3 + 0x40);
  bVar2 = *(byte *)(*(int *)(param_3 + 0x1c) + 1) & 3;
  if (bVar2 == 3) {
    uVar1 = *(undefined4 *)(param_3 + 0x30);
    uVar3 = *(undefined4 *)(param_3 + 0x34);
  }
  else if (bVar2 == 2) {
    uVar1 = *(undefined4 *)(param_3 + 0x28);
    uVar3 = *(undefined4 *)(param_3 + 0x30);
  }
  else {
    uVar3 = *(undefined4 *)(param_3 + 0x2c);
    if (bVar2 == 1) {
      uVar1 = *(undefined4 *)(param_3 + 0x30);
    }
    else {
      uVar1 = *(undefined4 *)(param_3 + 0x28);
    }
  }
  if ((*(uint *)(param_3 + 0x44) & 0x40000) != 0) {
    iVar4 = iVar4 + 0xe;
    sVar5 = sVar5 + -0xe;
  }
  iVar4 = RTMPTkipCompareMICValue
                    (param_1,iVar4,uVar1,uVar3,param_2 + 0x37a,*(undefined1 *)(param_3 + 0x4a),sVar5
                    );
  if (iVar4 == 0) {
    if (-1 < DebugLevel) {
      printk("Rx MIC Value error 2\n");
    }
    if ((*(uint *)(param_3 + 0x44) & 0x200) != 0) {
      HandleCounterMeasure(param_1,param_2);
    }
    RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_3 + 0x38));
    wlan_dbg_set_last_error(0,1,0x680,"rtmp_chk_tkip_mic");
    uVar1 = 0;
  }
  else {
    uVar1 = 1;
  }
  return uVar1;
}


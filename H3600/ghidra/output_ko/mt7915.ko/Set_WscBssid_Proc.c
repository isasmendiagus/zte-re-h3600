// module: mt7915.ko
// function: Set_WscBssid_Proc @ 0x5a34c
// size: 180 bytes
//

undefined4 Set_WscBssid_Proc(int *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  undefined1 local_13;
  undefined1 local_12;
  undefined1 local_11;
  
  iVar3 = *(int *)(*param_1 + 0x3c);
  iVar1 = rtstrmactohex(param_2,&local_16);
  uVar2 = 0;
  if (iVar1 != 0) {
    iVar1 = (int)param_1 + iVar3 * 0x2137b0 + 0x36ee89;
    RTMPZeroMemory(iVar1,6);
    RTMPMoveMemory(iVar1,&local_16,6);
    if (DebugLevel < 3) {
      uVar2 = 1;
    }
    else {
      printk("Set_WscBssid_Proc:: %02x:%02x:%02x:%02x:%02x:%02x\n",local_16,local_15,local_14,
             local_13,local_12,local_11);
      uVar2 = 1;
    }
  }
  return uVar2;
}


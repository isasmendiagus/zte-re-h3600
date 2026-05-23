// module: mt7915.ko
// function: mt_op_set_test_mode_dnlk_clean @ 0x2593c4
// size: 96 bytes
//

undefined4 mt_op_set_test_mode_dnlk_clean(int param_1)

{
  char *pcVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 != 0) {
    uVar3 = *(undefined4 *)("SetPartProfileParameters" + iVar2 + 4);
    pcVar1 = "SetPartProfileParameters" + iVar2;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    sys_ad_zero_mem(uVar3,0x278);
    uVar3 = *(undefined4 *)("SetPartProfileParameters" + iVar2 + 0xc);
    pcVar1 = "SetPartProfileParameters" + iVar2 + 8;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    sys_ad_zero_mem(uVar3,0x24);
    uVar3 = *(undefined4 *)("SetPartProfileParameters" + iVar2 + 0x14);
    pcVar1 = "SetPartProfileParameters" + iVar2 + 0x10;
    pcVar1[0] = '\0';
    pcVar1[1] = '\0';
    pcVar1[2] = '\0';
    pcVar1[3] = '\0';
    sys_ad_zero_mem(uVar3,0xc0);
    return 0;
  }
  return 0x503;
}


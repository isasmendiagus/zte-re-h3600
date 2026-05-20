// module: mt7915.ko
// function: RtmpIoctl_rt_ioctl_siwmode @ 0x62200
// size: 124 bytes
//

undefined4
RtmpIoctl_rt_ioctl_siwmode(int *param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *param_1;
  iVar2 = *(int *)(iVar1 + 0x3c);
  if (param_3 == 2) {
    Set_NetworkType_Proc(param_1,"Infra",2,iVar1,param_4);
  }
  else if (param_3 == 3) {
    Set_NetworkType_Proc(param_1,"Monitor",3,iVar1,param_4);
  }
  else if (param_3 == 1) {
    Set_NetworkType_Proc(param_1,"Adhoc",1,iVar1,param_4);
  }
  *(undefined1 *)((int)param_1 + iVar2 * 0x2137b0 + 0x580311) = 0;
  return 0;
}


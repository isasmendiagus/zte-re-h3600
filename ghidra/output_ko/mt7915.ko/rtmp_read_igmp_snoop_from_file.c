// module: mt7915.ko
// function: rtmp_read_igmp_snoop_from_file @ 0x241ea4
// size: 240 bytes
//

void rtmp_read_igmp_snoop_from_file(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  
  uVar5 = 0;
  iVar2 = RTMPGetKeyParameter("IgmpSnEnable",param_2,0x80,param_3,0);
  if ((iVar2 != 0) && (iVar2 = rstrtok(param_2,&_LC38), iVar2 != 0)) {
    do {
      iVar3 = rtmp_band_index_get_by_order(param_1,uVar5);
      uVar1 = simple_strtol(iVar2,0,10);
      iVar2 = DebugLevel;
      (&DAT_0036b914)[param_1 + iVar3] = uVar1;
      if (2 < iVar2) {
        printk(" Band[%d]-IGMP Snooping Enable=%d\n",iVar3,uVar1);
      }
      iVar2 = rstrtok(0,&_LC38);
      uVar4 = uVar5 ^ 1;
      uVar5 = 1;
      if (iVar2 == 0) {
        uVar4 = 0;
      }
    } while (uVar4 != 0);
    return;
  }
  return;
}


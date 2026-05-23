// module: mt7915.ko
// function: Set_WscSsid_Proc @ 0x5a15c
// size: 496 bytes
//

undefined4 Set_WscSsid_Proc(int *param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  undefined4 uVar4;
  int iVar5;
  void *__dest;
  undefined *__dest_00;
  int iVar6;
  void *__dest_01;
  
  iVar6 = *(int *)(*param_1 + 0x3c);
  iVar1 = iVar6 * 0x2137b0;
  iVar2 = get_scan_tab_by_wdev(param_1,(undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar1)));
  __memzero((undefined *)((int)param_1 + (int)(&DAT_0036ee60 + iVar1 + 4)),0x24);
  uVar4 = 0;
  if (*param_2 != '\0') {
    sVar3 = strlen(param_2);
    if (sVar3 < 0x21) {
      __dest_00 = (undefined *)((int)param_1 + (int)(&DAT_0036ee60 + iVar1 + 8));
      memmove(__dest_00,param_2,sVar3);
      sVar3 = strlen(param_2);
      __dest = (void *)((int)param_1 + iVar1 + 0x371c71);
      param_1[iVar6 * 0x84dec + 0xdbb99] = sVar3;
      __memzero(__dest,0x20);
      sVar3 = strlen(param_2);
      __dest_01 = (void *)((int)param_1 + iVar1 + 0x36ee89);
      memmove(__dest,param_2,sVar3);
      sVar3 = strlen(param_2);
      *(char *)((int)param_1 + iVar1 + 0x371c91) = (char)sVar3;
      __memzero(__dest_01,6);
      iVar5 = WscSearchWpsApBySSID
                        (param_1,__dest_00,(char)param_1[iVar6 * 0x84dec + 0xdbb99],1,
                         (undefined *)((int)param_1 + (int)(&DAT_0036db58 + iVar1)));
      if (iVar5 != -1) {
        memmove(__dest_01,(void *)(iVar2 + iVar5 * 0xaf4 + 0xe),6);
        *(undefined1 *)((int)param_1 + iVar1 + 0x371cbd) =
             *(undefined1 *)(iVar2 + iVar5 * 0xaf4 + 0x14);
      }
      hex_dump("Set_WscSsid_Proc:: WscBssid",__dest_01,6);
      if (DebugLevel < 3) {
        uVar4 = 1;
      }
      else {
        printk("Set_WscSsid_Proc:: (Select SsidLen=%d,Ssid=%s)\n",param_1[iVar6 * 0x84dec + 0xdbb99]
               ,__dest_00);
        uVar4 = 1;
      }
    }
    else {
      uVar4 = 0;
    }
  }
  return uVar4;
}


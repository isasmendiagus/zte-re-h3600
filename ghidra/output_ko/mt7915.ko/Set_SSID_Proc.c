// module: mt7915.ko
// function: Set_SSID_Proc @ 0x58d18
// size: 912 bytes
//

undefined4 Set_SSID_Proc(int *param_1,char *param_2)

{
  undefined1 uVar1;
  size_t sVar2;
  size_t sVar3;
  int *piVar4;
  int *piVar5;
  char *__s;
  int iVar6;
  bool bVar7;
  size_t local_4c;
  undefined1 auStack_48 [36];
  
  iVar6 = *(int *)(*param_1 + 0x3c);
  *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0xdc72e) = 0x20;
  __memzero(param_1 + iVar6 * 0x84dec + 0xdc726,0x20);
  sVar2 = strlen(param_2);
  if (0x20 < sVar2) {
    return 0;
  }
  __memzero(&local_4c,0x24);
  if (*param_2 == '\0') {
    *(undefined1 *)(param_1 + iVar6 * 0x84dec + 0xdc6ee) = 1;
    param_1[iVar6 * 0x84dec + 0xdb6e1] = param_1[iVar6 * 0x84dec + 0xdb6e1] | 1;
    param_1[iVar6 * 0x84dec + 0xdb733] = param_1[iVar6 * 0x84dec + 0xdb733] | 1;
    local_4c = 0;
  }
  else {
    sVar2 = strlen(param_2);
    memcpy(auStack_48,param_2,sVar2);
    __s = (char *)((int)param_1 + iVar6 * 0x2137b0 + 0x36dcd1);
    local_4c = sVar2;
    sVar3 = strlen(__s);
    SetWPAPSKKey(param_1,__s,sVar3,auStack_48,sVar2,(int)param_1 + iVar6 * 0x2137b0 + 0x36dd12);
  }
  piVar4 = param_1 + iVar6 * 0x84dec;
  __memzero((undefined1 *)((int)piVar4 + 0x371c71),0x20);
  sVar2 = local_4c;
  uVar1 = (undefined1)local_4c;
  memcpy((undefined1 *)((int)piVar4 + 0x371c71),auStack_48,local_4c);
  *(undefined1 *)((int)piVar4 + 0x371c91) = uVar1;
  memcpy(param_1 + iVar6 * 0x84dec + 0xdc726,auStack_48,sVar2);
  *(undefined1 *)(piVar4 + 0xdc72e) = uVar1;
  *(undefined1 *)(piVar4 + 0x15fe68) = 1;
  *(undefined1 *)((int)piVar4 + 0x580ccd) = 0;
  *(undefined1 *)(piVar4 + 0x15fff0) = 1;
  *(undefined1 *)(piVar4 + 0x1600d8) = 0;
  *(undefined1 *)(piVar4 + 0xdb7d9) = 0;
  *(undefined1 *)((int)piVar4 + 0x36df66) = 0;
  *(undefined1 *)(piVar4 + 0xdb7da) = 0;
  if (((piVar4[0xdb6e1] & 0xc0U) == 0) || ((piVar4[0xdb733] & 0x20U) == 0)) {
    piVar5 = &DebugLevel;
    if (*(char *)((int)param_1 + iVar6 * 0x2137b0 + 0x36df65) != '\0') {
      if (DebugLevel < 0) goto LAB_00058f08;
      printk("[PMF]%s:: Security is not WPA2/WPA2PSK AES\n","Set_SSID_Proc");
    }
  }
  else {
    bVar7 = *(char *)((int)piVar4 + 0x36df65) == '\0';
    piVar5 = piVar4;
    if (bVar7) {
      piVar5 = (int *)&DAT_00005b30;
    }
    *(undefined1 *)(piVar4 + 0xdb7da) = *(undefined1 *)((int)piVar4 + 0x36df69);
    if (bVar7) {
      piVar5 = (int *)((uint)piVar5 & 0xffff | 0x5f0000);
    }
    else {
      *(undefined1 *)(piVar4 + 0xdb7d9) = 1;
      piVar5 = &DebugLevel;
      if (*(char *)((int)piVar4 + 0x36df67) != '\0') {
        *(undefined1 *)(piVar4 + 0xdb7da) = 1;
      }
      *(char *)((int)piVar4 + 0x36df66) = *(char *)((int)piVar4 + 0x36df67);
    }
  }
  if (-1 < *piVar5) {
    printk("[PMF]%s:: MFPC=%d, MFPR=%d, SHA256=%d\n","Set_SSID_Proc",
           (char)param_1[iVar6 * 0x84dec + 0xdb7d9],
           *(undefined1 *)((int)param_1 + iVar6 * 0x2137b0 + 0x36df66),
           (char)param_1[iVar6 * 0x84dec + 0xdb7da]);
  }
LAB_00058f08:
  cntl_connect_request(param_1 + iVar6 * 0x84dec + 0xdb6d6,0,0x24,&local_4c);
  if (local_4c == 0x20) {
    hex_dump("Set_SSID_Proc::Ssid",auStack_48);
  }
  else if (2 < *piVar5) {
    printk("Set_SSID_Proc::(Len=%d,Ssid=%s)\n",local_4c,auStack_48);
  }
  RtmpOsMlmeUp(param_1 + 0xa18a6);
  return 1;
}


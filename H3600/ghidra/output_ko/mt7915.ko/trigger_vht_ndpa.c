// module: mt7915.ko
// function: trigger_vht_ndpa @ 0x2024cc
// size: 368 bytes
//

void trigger_vht_ndpa(int param_1,int param_2)

{
  short sVar1;
  byte *pbVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  byte *local_1c;
  
  iVar5 = *(int *)(param_2 + 8);
  iVar4 = os_alloc_mem(param_1,&local_1c,0x900);
  if (iVar4 == 0) {
    __memzero(local_1c,0x900);
    pbVar2 = local_1c;
    *local_1c = *local_1c & 3 | 0x54;
    *(undefined4 *)(local_1c + 4) = *(undefined4 *)(param_2 + 0xec);
    *(undefined2 *)(local_1c + 8) = *(undefined2 *)(param_2 + 0xf0);
    *(undefined4 *)(local_1c + 10) = *(undefined4 *)(iVar5 + 0x1b);
    *(undefined2 *)(local_1c + 0xe) = *(undefined2 *)(iVar5 + 0x1f);
    local_1c[0x11] = *(byte *)(param_2 + 0xf8);
    local_1c[0x12] = *(byte *)(param_2 + 0xf9) & 0xf;
    local_1c[0x10] = local_1c[0x10] & 3 | *(char *)(param_2 + 0xc67) << 2;
    if ((*(byte *)(param_2 + 0xc67) & 0xc0) == 0) {
      *(byte *)(param_2 + 0xc67) = *(byte *)(param_2 + 0xc67) + 1;
    }
    else {
      *(undefined1 *)(param_2 + 0xc67) = 0;
    }
    sVar1 = *(short *)(param_1 + 0x794c4a);
    sVar3 = RTMPCalcDuration(param_1,*(undefined1 *)(param_1 + 0x794cd5),0x13);
    *(short *)(pbVar2 + 2) = sVar3 + sVar1;
    if (0 < DebugLevel) {
      printk("Send VHT NDPA Frame to STA(%02x:%02x:%02x:%02x:%02x:%02x)\n",
             *(undefined1 *)(param_2 + 0xec),*(undefined1 *)(param_2 + 0xed),
             *(undefined1 *)(param_2 + 0xee),*(undefined1 *)(param_2 + 0xef),
             *(undefined1 *)(param_2 + 0xf0),*(undefined1 *)(param_2 + 0xf1));
    }
    hex_dump("VHT NDPA Frame",local_1c,0x13);
    MiniportMMRequest(param_1,0,local_1c,0x13);
    os_free_mem(local_1c);
    return;
  }
  return;
}


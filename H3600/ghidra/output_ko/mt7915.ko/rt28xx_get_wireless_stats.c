// module: mt7915.ko
// function: rt28xx_get_wireless_stats @ 0x24679c
// size: 212 bytes
//

undefined2 * rt28xx_get_wireless_stats(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined4 local_28;
  undefined4 local_24;
  undefined2 *local_20;
  undefined1 local_1c;
  undefined1 local_1b;
  undefined1 local_1a;
  
  uVar1 = RtmpOsGetNetDevPriv();
  if (2 < DebugLevel) {
    printk("rt28xx_get_wireless_stats --->\n");
  }
  local_28 = RtmpDevPrivFlagsGet(param_1);
  local_24 = *(undefined4 *)(param_1 + 0x1dc);
  iVar2 = RTMP_COM_IoctlHandle(uVar1,0,0x503d,0,&local_28,0);
  puVar3 = (undefined2 *)0x0;
  if (iVar2 == 0) {
    *local_20 = 0;
    *(undefined1 *)((int)local_20 + 5) = 9;
    *(undefined4 *)(local_20 + 0xe) = 0;
    *(undefined1 *)(local_20 + 1) = local_1c;
    *(undefined1 *)((int)local_20 + 3) = local_1b;
    iVar2 = DebugLevel;
    *(undefined4 *)(local_20 + 4) = 0;
    *(undefined1 *)(local_20 + 2) = local_1a;
    puVar3 = local_20;
    if (2 < iVar2) {
      printk("<--- rt28xx_get_wireless_stats\n");
    }
  }
  return puVar3;
}


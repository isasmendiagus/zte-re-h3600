// module: mt7915.ko
// function: ApCliIfDown @ 0x69d20
// size: 344 bytes
//

void ApCliIfDown(int param_1)

{
  undefined4 uVar1;
  char cVar2;
  undefined4 *puVar3;
  undefined *puVar4;
  int iVar5;
  bool bVar6;
  
  puVar3 = (undefined4 *)(&DAT_00580004 + param_1);
  puVar4 = &DAT_0036db58 + param_1;
  iVar5 = 0;
  do {
    if ((*(char *)((int)puVar3 + 0xe89) != '\x01') && (*(char *)((int)puVar3 + 0xe8a) != '\0')) {
      if (*(char *)(puVar3 + 5) != '\0') {
        RTMP_FORCE_WAKEUP(param_1,puVar4);
        *puVar3 = 0;
      }
      if (-1 < DebugLevel) {
        printk("%s():ApCli interface[%d] start down.\n","ApCliIfDown",iVar5);
      }
      uVar1 = HcGetBandByWdev(puVar4);
      repeater_disconnect_by_band(param_1,uVar1);
      puVar3[0x366] = 0;
      __init_waitqueue_head(puVar3 + 0x367,"&x->wait",sta_cntl_api_ops);
      puVar3[0x3a9] = 4;
      RTEnqueueInternalCmd(*(undefined4 *)(puVar4 + 8),0x1d,puVar4,0x4060);
      sta_wait_link_down(puVar4);
    }
    bVar6 = iVar5 != 1;
    iVar5 = 1;
    puVar4 = puVar4 + 0x2137b0;
    puVar3 = puVar3 + 0x84dec;
  } while (bVar6);
  puVar4 = &DAT_00368120 + param_1;
  cVar2 = '\0';
  do {
    if ((&DAT_003678f8)[param_1] == '\0') {
      RepeaterRemoveIngoreEntry(param_1,cVar2,puVar4);
    }
    cVar2 = cVar2 + '\x01';
    puVar4 = puVar4 + 0xc;
  } while (cVar2 != ' ');
  return;
}


// module: mt7915.ko
// function: RtmpDrvAllE2PPrint @ 0x245914
// size: 396 bytes
//

void RtmpDrvAllE2PPrint(undefined4 param_1,ushort *param_2,uint param_3,uint param_4)

{
  ushort uVar1;
  char *pcVar2;
  uint uVar3;
  size_t sVar4;
  uint uVar5;
  uint local_38;
  undefined4 local_34;
  char *local_2c [2];
  
  os_alloc_mem(0,local_2c,0x400);
  if (local_2c[0] != (char *)0x0) {
    uVar5 = 0;
    local_34 = *(undefined4 *)(((uint)&local_38 & 0xffffe000) + 8);
    *(undefined4 *)(((uint)&local_38 & 0xffffe000) + 8) = 0;
    uVar3 = filp_open("EEPROMDump.txt",0x41,0);
    if (uVar3 < 0xfffff001) {
      if (*(int *)(uVar3 + 0x14) != 0) {
        local_38 = param_4 & 0xfffffffe;
        *(undefined4 *)(uVar3 + 0x40) = 0;
        *(undefined4 *)(uVar3 + 0x44) = 0;
        do {
          uVar1 = *param_2;
          param_2 = (ushort *)((int)param_2 + local_38);
          sprintf(local_2c[0],"%08x = %04x\n",uVar5,(uint)uVar1);
          pcVar2 = local_2c[0];
          sVar4 = strlen(local_2c[0]);
          __vfs_write(uVar3,pcVar2,sVar4,(undefined4 *)(uVar3 + 0x40));
          if (-1 < DebugLevel) {
            printk(&_LC52,local_2c[0]);
          }
          uVar5 = uVar5 + (param_4 & 0xffff) & 0xffff;
        } while (uVar5 <= param_3);
        snprintf(local_2c[0],0x400,"\nDump all EEPROM values to %s\n","EEPROMDump.txt");
      }
      filp_close(uVar3,0);
    }
    else if (2 < DebugLevel) {
      printk("-->2) %s: Error %ld opening %s\n","RtmpDrvAllE2PPrint",-uVar3,"EEPROMDump.txt");
    }
    *(undefined4 *)(((uint)&local_38 & 0xffffe000) + 8) = local_34;
    os_free_mem(local_2c[0]);
  }
  return;
}


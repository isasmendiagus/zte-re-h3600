// module: mt7915.ko
// function: RtmpDrvAllMacPrint @ 0x245790
// size: 384 bytes
//

void RtmpDrvAllMacPrint(undefined4 param_1,undefined4 *param_2,uint param_3,uint param_4,int param_5
                       )

{
  char *pcVar1;
  uint uVar2;
  size_t sVar3;
  uint uVar4;
  int unaff_r10;
  undefined1 *unaff_r11;
  undefined1 auStack_38 [4];
  undefined4 local_34;
  char *local_2c [2];
  
  os_alloc_mem(0,local_2c,0x400);
  if (local_2c[0] != (char *)0x0) {
    local_34 = *(undefined4 *)(((uint)auStack_38 & 0xffffe000) + 8);
    *(undefined4 *)(((uint)auStack_38 & 0xffffe000) + 8) = 0;
    uVar2 = filp_open("MacDump.txt",0x41,0);
    if (uVar2 < 0xfffff001) {
      if (*(int *)(uVar2 + 0x14) != 0) {
        if (param_3 <= param_4) {
          unaff_r10 = uVar2 + 0x40;
          unaff_r11 = &DAT_00005b30;
        }
        *(undefined4 *)(uVar2 + 0x40) = 0;
        *(undefined4 *)(uVar2 + 0x44) = 0;
        if (param_3 <= param_4) {
          do {
            uVar4 = param_3 + param_5;
            sprintf(local_2c[0],"%04x = %08x\n",param_3,*param_2);
            pcVar1 = local_2c[0];
            sVar3 = strlen(local_2c[0]);
            __vfs_write(uVar2,pcVar1,sVar3,unaff_r10);
            if (-1 < *(int *)((uint)unaff_r11 & 0xffff | 0x5f0000)) {
              printk(&_LC52,local_2c[0]);
            }
            param_3 = uVar4;
            param_2 = param_2 + 1;
          } while (uVar4 <= param_4);
        }
        snprintf(local_2c[0],0x400,"\nDump all MAC values to %s\n","MacDump.txt");
      }
      filp_close(uVar2,0);
    }
    else if (2 < DebugLevel) {
      printk("-->2) %s: Error %ld opening %s\n","RtmpDrvAllMacPrint",-uVar2,"MacDump.txt");
    }
    *(undefined4 *)(((uint)auStack_38 & 0xffffe000) + 8) = local_34;
    os_free_mem(local_2c[0]);
  }
  return;
}


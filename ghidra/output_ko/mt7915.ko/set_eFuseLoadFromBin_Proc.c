// module: mt7915.ko
// function: set_eFuseLoadFromBin_Proc @ 0x1d2c80
// size: 664 bytes
//

undefined4 set_eFuseLoadFromBin_Proc(undefined4 param_1,char *param_2)

{
  char *__dest;
  uint uVar1;
  int iVar2;
  size_t __n;
  uint uVar3;
  uint extraout_r1;
  ushort *puVar4;
  int iVar5;
  char *__s1;
  char *local_40;
  undefined1 auStack_3c [12];
  undefined4 local_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  
  local_30 = 0xffffffff;
  uStack_2c = 0xffffffff;
  uStack_28 = 0xffffffff;
  uStack_24 = 0xffffffff;
  os_alloc_mem(0,&local_40,0x290);
  if (local_40 != (char *)0x0) {
    __memzero(local_40,0x290);
    __dest = local_40;
    __s1 = local_40 + 0x80;
    if (*param_2 == '\0') {
      builtin_strncpy(local_40,"RT30xxEEPROM.bin",0x10);
    }
    else {
      __n = strlen(param_2);
      memmove(__dest,param_2,__n);
    }
    if (0 < DebugLevel) {
      printk("FileName=%s\n",__dest);
    }
    RtmpOSFSInfoChange(auStack_3c,1);
    uVar1 = RtmpOSFileOpen(__dest,0,0);
    if ((uVar1 == 0) || (0xfffff000 < uVar1)) {
      if (-1 < DebugLevel) {
        printk("--> Error opening file %s\n",__dest);
      }
    }
    else {
      iVar5 = 0;
      do {
        iVar2 = RtmpOSFileRead(uVar1,__dest + iVar5 + 0x80,1);
        if (iVar2 != 1) {
          iVar2 = RtmpOSFileClose(uVar1);
          if ((iVar2 != 0) && (2 < DebugLevel)) {
            printk("--> Error closing file %s\n",__dest);
          }
          RtmpOSFSInfoChange(auStack_3c,0);
          if (iVar5 != 0) {
            uVar1 = 0;
            do {
              iVar2 = memcmp(__s1,&local_30,0x10);
              if (iVar2 != 0) {
                if (2 < DebugLevel) {
                  printk("offset 0x%04x: ",uVar1);
                }
                puVar4 = (ushort *)(__s1 + -2);
                iVar2 = DebugLevel;
                do {
                  puVar4 = puVar4 + 1;
                  uVar3 = (uint)*puVar4;
                  if (2 < iVar2) {
                    printk("0x%04x ",uVar3);
                    uVar3 = extraout_r1;
                    iVar2 = DebugLevel;
                  }
                } while ((ushort *)(__s1 + 0xe) != puVar4);
                if (2 < iVar2) {
                  printk(&_LC19,uVar3);
                }
              }
              __s1 = __s1 + 0x10;
              uVar1 = uVar1 + 0x10 & 0xffff;
            } while ((int)uVar1 < iVar5);
          }
          return 1;
        }
        iVar5 = iVar5 + 1;
      } while (iVar5 != 0x201);
      if (-1 < DebugLevel) {
        printk("--> Error reading file %s, file size too large[>%d]\n",__dest,0x200);
      }
      RtmpOSFileClose(uVar1);
    }
    RtmpOSFSInfoChange(auStack_3c,0);
    if (local_40 != (char *)0x0) {
      os_free_mem();
    }
  }
  return 0;
}


// module: mt7915.ko
// function: WscSearchWpsApBySSID @ 0x1eb484
// size: 272 bytes
//

uint WscSearchWpsApBySSID(undefined4 param_1,void *param_2,size_t param_3,int param_4,int param_5)

{
  uint *puVar1;
  int iVar2;
  short sVar3;
  uint uVar4;
  uint uVar5;
  
  puVar1 = (uint *)get_scan_tab_by_wdev(param_1,param_5);
  if (param_4 == 2) {
    sVar3 = 4;
  }
  else {
    sVar3 = 0;
  }
  uVar5 = *puVar1;
  if (uVar5 != 0) {
    uVar4 = 0;
    do {
      if (((((byte)puVar1[uVar4 * 0x2bd + 0x27] == param_3) &&
           (iVar2 = memcmp(param_2,(void *)((int)puVar1 + uVar4 * 0xaf4 + 0x9d),param_3), iVar2 == 0
           )) && ((char)puVar1[uVar4 * 0x2bd + 0x14f] != '\0')) &&
         (sVar3 == 0 || *(short *)((int)puVar1 + uVar4 * 0xaf4 + 0x53e) == sVar3)) {
        if (*(char *)(param_5 + 0x3d3d) == '\x01') {
          if (0xe < (byte)puVar1[uVar4 * 0x2bd + 5]) {
            return uVar4;
          }
        }
        else if ((*(char *)(param_5 + 0x3d3d) != '\0') || ((byte)puVar1[uVar4 * 0x2bd + 5] < 0xf)) {
          return uVar4;
        }
      }
      uVar4 = uVar4 + 1 & 0xff;
    } while (uVar4 < uVar5);
  }
  return 0xffffffff;
}


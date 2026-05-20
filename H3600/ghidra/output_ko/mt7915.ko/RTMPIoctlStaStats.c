// module: mt7915.ko
// function: RTMPIoctlStaStats @ 0x15bec0
// size: 816 bytes
//

void RTMPIoctlStaStats(undefined4 param_1,int param_2)

{
  undefined1 *puVar1;
  byte *__s;
  int *piVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  size_t sVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint local_178;
  uint local_174;
  uint local_170;
  undefined1 auStack_166 [6];
  char acStack_160 [64];
  char acStack_120 [260];
  
  memset(acStack_160,0,0x40);
  if ((*(ushort *)(param_2 + 0x14) & 0xfffb) == 0x12) {
    if (*(char **)(param_2 + 0x10) != (char *)0x0) {
      strncpy(acStack_160,*(char **)(param_2 + 0x10),0x11);
    }
    __s = (byte *)rstrtok(acStack_160,&_LC11);
    puVar1 = auStack_166;
    while (__s != (byte *)0x0) {
      sVar6 = strlen((char *)__s);
      if (sVar6 != 2) {
        return;
      }
      if (((&_ctype)[*__s] & 0x44) == 0) {
        return;
      }
      if (((&_ctype)[__s[1]] & 0x44) == 0) {
        return;
      }
      AtoH(__s,puVar1);
      __s = (byte *)rstrtok(0,&_LC11);
      puVar1 = puVar1 + 1;
    }
    piVar2 = (int *)MacTableLookup(param_1,auStack_166);
    if (((piVar2 != (int *)0x0) && (*piVar2 == 0x20001)) && (piVar2[0x3f] == 2)) {
      if (*(short *)(param_2 + 0x14) == 0x16) {
        pcVar3 = strstr(*(char **)(param_2 + 0x10),"=clr");
        if (pcVar3 != (char *)0x0) {
          __memzero(piVar2 + 0x4c0,8);
          __memzero(piVar2 + 0x4c2,8);
          __memzero(piVar2[0x52c],0x1040);
        }
      }
      else {
        pcVar3 = strstr(acStack_160,"=get");
        if (pcVar3 == (char *)0x0) {
          local_178 = (uint)*(byte *)((int)piVar2 + 0xef);
          local_174 = (uint)*(byte *)(piVar2 + 0x3c);
          local_170 = (uint)*(byte *)((int)piVar2 + 0xf1);
          printk("STA:%02x:%02x:%02x:%02x:%02x:%02x \n",(char)piVar2[0x3b],
                 *(undefined1 *)((int)piVar2 + 0xed),*(undefined1 *)((int)piVar2 + 0xee));
          printk("total pkt rx num:%lu \n",piVar2[0x4c2]);
          FUN_0015630c(param_1,piVar2);
        }
        else {
          memset(acStack_120,0,0x100);
          iVar4 = snprintf(acStack_120,0xff,"tx pkts:%lu \n",piVar2[0x4c0]);
          iVar5 = snprintf(acStack_120 + iVar4,0xff - iVar4,"tx bytes:%lu \n",piVar2[0x4c4]);
          iVar4 = iVar4 + iVar5;
          iVar5 = snprintf(acStack_120 + iVar4,0xff - iVar4,"rx pkts:%lu \n",piVar2[0x4c2]);
          iVar5 = iVar5 + iVar4;
          iVar4 = snprintf(acStack_120 + iVar5,0xff - iVar5,"rx bytes:%lu \n",piVar2[0x4c6]);
          sVar6 = strlen(acStack_160);
          uVar8 = iVar4 + iVar5;
          if (((uint)(iVar4 + iVar5) < sVar6) && (uVar8 = sVar6, 0xfe < sVar6)) {
            uVar8 = 0xff;
          }
          if ((int)uVar8 <= (int)(uint)*(ushort *)(param_2 + 0x14)) {
            uVar7 = *(uint *)(param_2 + 0x10);
            uVar9 = *(uint *)(((uint)&local_178 & 0xffffe000) + 8);
            if (!CARRY4(uVar7,uVar8) && uVar7 + uVar8 <= uVar9) {
              uVar9 = 0;
            }
            if (uVar9 == 0) {
              uVar8 = __copy_to_user(uVar7,acStack_120);
            }
            if (uVar8 != 0) {
              if (DebugLevel < 0) {
                return;
              }
              printk("Get::%s error!! Status=%d\n","RTMPIoctlStaStats");
            }
          }
          if (1 < DebugLevel) {
            printk("%s: %s retun %s\n","RTMPIoctlStaStats",acStack_160,acStack_120);
          }
        }
      }
    }
  }
  return;
}


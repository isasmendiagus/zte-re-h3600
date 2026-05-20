// module: mt7915.ko
// function: BssTableSsidSort @ 0x10fb20
// size: 1768 bytes
//

void BssTableSsidSort(int param_1,int param_2,uint *param_3,void *param_4,byte param_5)

{
  byte bVar1;
  ushort uVar2;
  bool bVar3;
  int iVar4;
  uint *puVar5;
  int iVar6;
  uint *__dest;
  void *__dest_00;
  uint __n;
  uint uVar7;
  void *__src;
  void *__s2;
  uint uVar8;
  bool bVar9;
  bool bVar10;
  
  __n = (uint)param_5;
  iVar4 = GetStaCfgByWdev();
  puVar5 = (uint *)get_scan_tab_by_wdev(param_1,param_2);
  BssTableInit(param_3);
  bVar3 = __n == 0;
  if ((*(int *)(param_2 + 0x14) == 2 && __n == 0) && (*(char *)(iVar4 + 0x213173) == '\0')) {
    return;
  }
  uVar7 = *puVar5;
  if (uVar7 - 1 < 0xff) {
    __s2 = (void *)((int)puVar5 + 0x9d);
    uVar8 = 0;
    __dest_00 = (void *)(iVar4 + 0x4119);
    do {
      if (*(char *)((int)__s2 + 0x62e) == '\0') {
        if (((*(char *)(param_1 + 0x795074) == '\x01') && (0xe < *(byte *)(iVar4 + 0x4165))) &&
           (iVar6 = RadarChannelCheck(param_1,*(undefined1 *)((int)__s2 + -0x89)), iVar6 != 0)) {
          bVar10 = *(char *)((int)__s2 + -0x10) != '\0';
        }
        else {
          bVar10 = false;
        }
        if (((*(uint *)((int)__s2 + 0x2f) & *(uint *)(param_2 + 0x2c)) == 0) &&
           ((*(uint *)((int)__s2 + 0x33) & *(uint *)(param_2 + 0x174)) == 0)) goto LAB_0010fc84;
        __src = (void *)((int)__s2 + -0x95);
        if ((*(uint *)(param_2 + 0x2c) & 0x812000) == 0 || __s2 == (void *)0x95) {
          if ((*(uint *)(param_2 + 0x2c) & 0xc0) != 0 && __s2 != (void *)0x95) {
            uVar2 = *(ushort *)((int)__s2 + 0x3b);
            if (*(char *)(param_2 + 0x40e) != '\0') goto joined_r0x0010fcbc;
            if (*(char *)(param_2 + 0x40c) == '\0') {
              uVar2 = uVar2 & 0x80;
            }
            else {
              if ((uVar2 & 0x80) == 0) goto LAB_0010fcc0;
              uVar2 = uVar2 & 0x40;
            }
            if (((uVar2 == 0) && (*(char *)(param_2 + 0x410) != '\0')) &&
               (*(char *)((int)__s2 + 0x45f) == '\0')) {
              if (3 < DebugLevel) {
                printk("[PMF]%s : Peer is not sha256.\n","BssTableSsidSort");
                uVar7 = *puVar5;
                goto LAB_0010fbd8;
              }
              goto LAB_0010fc84;
            }
          }
        }
        else {
          uVar2 = *(ushort *)((int)__s2 + 0x3b);
joined_r0x0010fcbc:
          if ((uVar2 & 0x80) == 0) {
            if (3 < DebugLevel) {
              printk("[PMF]%s : Peer\'s MPFC isn\'t used.\n","BssTableSsidSort");
              uVar7 = *puVar5;
              goto LAB_0010fbd8;
            }
            goto LAB_0010fc84;
          }
        }
LAB_0010fcc0:
        uVar7 = (uint)*(byte *)((int)__s2 + -1);
        bVar9 = uVar7 == 0x20;
        if (uVar7 < 0x21) {
          bVar9 = __n == uVar7;
        }
        if (((bVar9) && (iVar6 = memcmp(param_4,__s2,__n), iVar6 == 0)) || (bVar10)) {
          if (*(char *)((int)__s2 + -0x81) != *(char *)(iVar4 + 0x4060)) goto LAB_0010fcf0;
          uVar7 = *param_3;
          if (uVar7 < 0x100) {
            __dest = param_3 + uVar7 * 0x2bd + 2;
            if (((*(int *)(param_2 + 0x14) == 2) && (*(int *)(iVar4 + 0x12e4) != 0)) &&
               (*(char *)(iVar4 + 0x3cc8) != '\0')) goto LAB_00110138;
            if (((*(uint *)((int)__s2 + 0xa33) & 1) == 0) &&
               ((*(ushort *)(param_2 + 0x18) & 0xffc7) == 0)) goto LAB_0010ff88;
            if ((*(ushort *)(param_2 + 0x18) == 0xc) &&
               ((uint)*(byte *)((int)__s2 + -0x6f) + (uint)*(byte *)((int)__s2 + -0x62) < 0xc))
            goto LAB_0010fd9c;
            if (!bVar3) {
              memmove(__dest,__src,0xaf4);
              if (2 < DebugLevel) {
                printk("-------->%s(%d), AKMMap=0x%x, PairwiseCipher=0x%x, GroupCipher=0x%x, CapabilityInfo=0x%x\n"
                       ,"BssTableSsidSort",0x5ae,*(undefined4 *)((int)__s2 + 0x2f),
                       *(undefined4 *)((int)__s2 + 0x33),*(undefined4 *)((int)__s2 + 0x37),
                       *(undefined2 *)((int)__s2 + -0xb));
              }
              goto LAB_00110068;
            }
            goto LAB_0010fc84;
          }
          if (bVar3) goto LAB_00110000;
          if ((*(int *)(param_2 + 0x14) != 2) || (*(int *)(iVar4 + 0x12e4) == 0)) break;
LAB_0010fe18:
          if (*(char *)(iVar4 + 0x3cc8) != '\0') {
LAB_0010fe28:
            iVar6 = memcmp((void *)(iVar4 + 0x1331),(void *)((int)__s2 + -0x8f),6);
            if (iVar6 == 0) {
              if (uVar7 < 0x100) {
                memmove(param_3 + uVar7 * 0x2bd + 2,__src,0xaf4);
                __memzero(__dest_00,0x20);
                memmove(__dest_00,__s2,(uint)*(byte *)((int)__s2 + -1));
                *(undefined1 *)(iVar4 + 0x4139) = *(undefined1 *)((int)__s2 + -1);
                __memzero((void *)(iVar4 + 0x4140),0x20);
                bVar1 = *(byte *)(iVar4 + 0x4139);
                memmove((void *)(iVar4 + 0x4140),__dest_00,(uint)bVar1);
                *(byte *)(iVar4 + 0x4160) = bVar1;
                *param_3 = *param_3 + 1;
                uVar7 = *puVar5;
                goto LAB_0010fbd8;
              }
              break;
            }
          }
LAB_0010fd00:
          if (0xff < uVar7) break;
        }
        else {
          if ((!bVar3) || (*(char *)((int)__s2 + -0x81) != *(char *)(iVar4 + 0x4060))) {
LAB_0010fcf0:
            uVar7 = *param_3;
            if ((*(int *)(param_2 + 0x14) == 2) && (*(int *)(iVar4 + 0x12e4) != 0))
            goto LAB_0010fe18;
            goto LAB_0010fd00;
          }
          uVar7 = *param_3;
          if (0xff < uVar7) {
LAB_00110000:
            if (((*(int *)(param_2 + 0x14) == 2) && (*(int *)(iVar4 + 0x12e4) != 0)) &&
               (*(char *)(iVar4 + 0x3cc8) != '\0')) goto LAB_0010fe28;
            break;
          }
          __dest = param_3 + uVar7 * 0x2bd + 2;
          if ((*(int *)(iVar4 + 0x12e4) != 0) && (*(char *)(iVar4 + 0x3cc8) != '\0')) {
LAB_00110138:
            memmove(__dest,__src,0xaf4);
            *param_3 = *param_3 + 1;
            uVar7 = *puVar5;
            goto LAB_0010fbd8;
          }
          if (((*(uint *)((int)__s2 + 0xa33) & 1) == 0) &&
             ((*(ushort *)(param_2 + 0x18) & 0xffc7) == 0)) {
LAB_0010ff88:
            if (2 < DebugLevel) {
              printk("STA is in N-only Mode, this AP don\'t have Ht capability in Beacon.\n");
              uVar7 = *puVar5;
              goto LAB_0010fbd8;
            }
          }
          else {
            if ((*(ushort *)(param_2 + 0x18) != 0xc) ||
               (0xb < (uint)*(byte *)((int)__s2 + -0x6f) + (uint)*(byte *)((int)__s2 + -0x62))) {
              memmove(__dest,__src,0xaf4);
              if (2 < DebugLevel) {
                printk("-------->%s(%d), AKMMap=0x%x, PairwiseCipher=0x%x\n","BssTableSsidSort",
                       0x5d5,*(undefined4 *)((int)__s2 + 0x2f),*(undefined4 *)((int)__s2 + 0x33));
              }
LAB_00110068:
              uVar7 = *param_3 + 1;
              *param_3 = uVar7;
              goto LAB_0010fd00;
            }
LAB_0010fd9c:
            if (2 < DebugLevel) {
              printk("STA is in GN-only Mode, this AP is in B mode.\n");
              uVar7 = *puVar5;
              goto LAB_0010fbd8;
            }
          }
        }
LAB_0010fc84:
        uVar7 = *puVar5;
      }
      else if (-1 < DebugLevel) {
        printk("%s : skip %02x:%02x:%02x:%02x:%02x:%02x, SSID:%s, AKM:0x%x by OWE transition\n",
               "BssTableSsidSort",*(undefined1 *)((int)__s2 + -0x8f),
               *(undefined1 *)((int)__s2 + -0x8e),*(undefined1 *)((int)__s2 + -0x8d),
               *(undefined1 *)((int)__s2 + -0x8c),*(undefined1 *)((int)__s2 + -0x8b),
               *(undefined1 *)((int)__s2 + -0x8a),__s2,*(undefined4 *)((int)__s2 + 0x2f));
        uVar7 = *puVar5;
      }
LAB_0010fbd8:
      uVar8 = uVar8 + 1;
      bVar10 = 0xfe < uVar7;
      if (uVar7 < 0x100) {
        bVar10 = uVar7 <= uVar8;
      }
      __s2 = (void *)((int)__s2 + 0xaf4);
    } while (!bVar10);
  }
  BssTableSortByRssi(param_3,0);
  return;
}


// module: mt7915.ko
// function: PeerAssocRspSanity @ 0x529d4
// size: 1436 bytes
//

undefined4
PeerAssocRspSanity(undefined4 param_1,int param_2,uint param_3,undefined4 *param_4,void *param_5,
                  short *param_6,ushort *param_7,byte *param_8,undefined1 *param_9,void *param_10,
                  undefined1 *param_11,int param_12)

{
  byte bVar1;
  int iVar2;
  size_t __n;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *__src;
  int iVar6;
  uint uVar7;
  bool bVar8;
  undefined1 local_29 [5];
  
  *param_8 = 0xff;
  *param_4 = *(undefined4 *)(param_2 + 10);
  *(undefined2 *)(param_4 + 1) = *(undefined2 *)(param_2 + 0xe);
  memmove(param_5,(void *)(param_2 + 0x18),2);
  memmove(param_6,(void *)(param_2 + 0x1a),2);
  *param_11 = 0;
  *param_9 = 0;
  if (*param_6 == 0) {
    memmove(param_7,(void *)(param_2 + 0x1c),2);
    *param_7 = (ushort)(((uint)*param_7 << 0x12) >> 0x12);
    bVar1 = *(byte *)(param_2 + 0x1f);
    uVar7 = (uint)bVar1;
    bVar8 = uVar7 == 0xc;
    if (uVar7 < 0xd) {
      bVar8 = *(char *)(param_2 + 0x1e) == '\x01';
    }
    if (!bVar8) {
      if (DebugLevel < 3) {
        return 0;
      }
      printk("%s(): fail - wrong SupportedRates IE\n","PeerAssocRspSanity");
      return 0;
    }
    iVar6 = uVar7 + 0x20;
    __src = (byte *)(param_2 + iVar6);
    memmove((void *)(param_12 + 0x245),(void *)(param_2 + 0x20),uVar7);
    *(byte *)(param_12 + 0x244) = bVar1;
    uVar7 = (uint)__src[1];
    __n = uVar7 + 2;
    uVar3 = __n + iVar6;
    while (uVar3 <= param_3) {
      bVar1 = *__src;
      if (bVar1 == 0x3d) {
LAB_00052c0c:
        if (uVar7 < 0x16) {
          if (DebugLevel < 2) goto LAB_00052b34;
          printk("%s():wrong IE_ADD_HT\n","PeerAssocRspSanity");
          uVar7 = (uint)__src[1];
        }
        else {
          memmove((void *)(param_12 + 0x28e),__src + 2,0x16);
          *(uint *)(param_12 + 0x240) = *(uint *)(param_12 + 0x240) | 2;
          uVar7 = (uint)__src[1];
        }
      }
      else if (bVar1 < 0x3e) {
        if (bVar1 == 0x32) {
          if (0xc < uVar7) goto LAB_00052b34;
          memmove((void *)(param_12 + 0x252),__src + 2,uVar7);
          *(byte *)(param_12 + 0x251) = __src[1];
          uVar7 = (uint)__src[1];
        }
        else {
          if (bVar1 < 0x33) {
            if (bVar1 != 0x2d) {
              if (bVar1 != 0x30) goto LAB_00052b28;
              memmove((void *)(param_12 + 0x92),__src,__n);
              *(byte *)(param_12 + 0x191) = __src[1] + 2;
              uVar7 = (uint)__src[1];
              goto LAB_00052b38;
            }
          }
          else if (bVar1 != 0x34) {
            if (bVar1 == 0x35) goto LAB_00052c0c;
LAB_00052b28:
            if (2 < DebugLevel) {
              printk("%s():ignore unrecognized EID = %d\n","PeerAssocRspSanity",bVar1);
            }
            goto LAB_00052b34;
          }
          if (uVar7 < 0x1a) {
            if (DebugLevel < 2) {
LAB_00052b34:
              uVar7 = (uint)__src[1];
            }
            else {
              printk("%s():wrong IE_HT_CAP\n","PeerAssocRspSanity");
              uVar7 = (uint)__src[1];
            }
          }
          else {
            memmove((void *)(param_12 + 0x274),__src + 2,0x1a);
            *(uint *)(param_12 + 0x240) = *(uint *)(param_12 + 0x240) | 1;
            uVar7 = (uint)__src[1];
          }
        }
      }
      else if (bVar1 == 0xbf) {
        if (uVar7 == 0xc) {
          memmove((void *)(param_12 + 0x2a4),__src + 2,0xc);
          *(uint *)(param_12 + 0x240) = *(uint *)(param_12 + 0x240) | 4;
          uVar7 = (uint)__src[1];
        }
        else {
          if (DebugLevel < 2) goto LAB_00052b34;
          printk("%s():wrong IE_VHT_CAP\n","PeerAssocRspSanity");
          uVar7 = (uint)__src[1];
        }
      }
      else if (bVar1 < 0xc0) {
        if (bVar1 != 0x3e) {
          if (bVar1 != 0x7f) goto LAB_00052b28;
          if (uVar7 != 0) {
            if (10 < uVar7) {
              uVar7 = 0xb;
            }
            memmove(param_10,__src + 2,uVar7);
            if (1 < DebugLevel) {
              printk("PeerAssocReqSanity - IE_EXT_CAPABILITY!\n");
              uVar7 = (uint)__src[1];
              goto LAB_00052b38;
            }
          }
          goto LAB_00052b34;
        }
        if (uVar7 == 1) {
          *param_8 = __src[2];
          uVar7 = (uint)__src[1];
        }
        else {
          if (DebugLevel < 2) goto LAB_00052b34;
          printk("%s():wrong IE_SECONDARY_CH_OFFSET\n","PeerAssocRspSanity");
          uVar7 = (uint)__src[1];
        }
      }
      else if (bVar1 == 0xdd) {
        iVar2 = map_check_cap_ie(__src,local_29);
        if (iVar2 == 1) {
          *(undefined1 *)(param_12 + 0x1a7) = local_29[0];
        }
        iVar2 = map_check_zte_ie(__src,local_29);
        if (iVar2 == 1) {
          *(undefined1 *)(param_12 + 0x1a8) = local_29[0];
        }
        iVar2 = memcmp(__src + 2,&WME_PARM_ELEM,6);
        uVar7 = (uint)__src[1];
        if ((iVar2 == 0) && (uVar7 == 0x18)) {
          param_9[2] = 0;
          param_9[3] = 0;
          param_9[4] = 0;
          *param_9 = 1;
          param_9[6] = __src[8] & 0xf;
          param_9[5] = __src[8] >> 7;
          pbVar4 = __src + 0xe;
          do {
            pbVar5 = pbVar4 + 4;
            uVar7 = ((uint)pbVar4[-4] << 0x19) >> 0x1e;
            param_9[uVar7 + 0x1c] = (byte)(((uint)pbVar4[-4] << 0x1b) >> 0x1f);
            param_9[uVar7 + 7] = pbVar4[-4] & 0xf;
            param_9[uVar7 + 0xb] = pbVar4[-3] & 0xf;
            param_9[uVar7 + 0xf] = pbVar4[-3] >> 4;
            *(ushort *)(param_9 + uVar7 * 2 + 0x14) =
                 (ushort)pbVar4[-2] + (ushort)pbVar4[-1] * 0x100;
            pbVar4 = pbVar5;
          } while (pbVar5 != __src + 0x1e);
          goto LAB_00052b34;
        }
      }
      else if (bVar1 == 0xff) {
        parse_he_assoc_rsp_ies(__src,param_12);
        if (__src[2] == 0x20) {
          os_zero_mem(param_12 + 0x1ae,__src[1] - 3);
          *(undefined1 *)(param_12 + 0x1a9) = 0xff;
          *(byte *)(param_12 + 0x1aa) = __src[1];
          memmove((void *)(param_12 + 0x1ab),__src + 2,(uint)__src[1]);
          uVar7 = (uint)__src[1];
        }
        else {
          if (DebugLevel < 0) goto LAB_00052b34;
          printk("RESP IE_WLAN_EXTENSION: no handler for extension_id:%d\n");
          uVar7 = (uint)__src[1];
        }
      }
      else {
        if (bVar1 != 0xc0) goto LAB_00052b28;
        if (uVar7 == 5) {
          memmove((void *)(param_12 + 0x2b0),__src + 2,5);
          *(uint *)(param_12 + 0x240) = *(uint *)(param_12 + 0x240) | 8;
          uVar7 = (uint)__src[1];
        }
        else {
          if (DebugLevel < 2) goto LAB_00052b34;
          printk("%s():wrong IE_VHT_OP\n","PeerAssocRspSanity");
          uVar7 = (uint)__src[1];
        }
      }
LAB_00052b38:
      __src = __src + uVar7 + 2;
      iVar6 = iVar6 + uVar7 + 2;
      uVar7 = (uint)__src[1];
      __n = uVar7 + 2;
      uVar3 = __n + iVar6;
    }
  }
  return 1;
}


// module: mt7915.ko
// function: rx_chk_amsdu_invalid_frame @ 0xcc380
// size: 648 bytes
//

undefined4 rx_chk_amsdu_invalid_frame(int param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined1 *__s2;
  undefined1 *puVar6;
  
  uVar5 = (uint)*(ushort *)(param_2 + 0x4e);
  uVar2 = *(ushort *)(param_2 + 0x24);
  cVar1 = *(char *)(param_2 + 0x73);
  if ((((((*(uint *)(param_2 + 0x44) & 1) == 0) && (*(byte *)(param_2 + 0x4a) < 0x11)) &&
       (uVar3 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0)),
       uVar5 < 0x120 && uVar5 < uVar3)) &&
      ((param_1 + uVar5 * 0x620 != -0x2f6a0 &&
       (uVar3 = (uint)*(byte *)(param_2 + 0x4a), (*(uint *)(param_2 + 0x44) & 2) != 0)))) &&
     (*(void **)(param_2 + 0x88) != (void *)0x0)) {
    __s2 = *(undefined1 **)(param_2 + 0x2c);
    if ((*(byte *)(*(int *)(param_2 + 0x1c) + 1) & 3) == 2) {
      __s2 = *(undefined1 **)(param_2 + 0x28);
    }
    if ((cVar1 == '\x03') && (iVar4 = memcmp(*(void **)(param_2 + 0x88),__s2,6), iVar4 != 0)) {
      if ((2 < DebugLevel) &&
         (printk("%s: AMSDU ATTACK,\twcid=%d SN-AN(%d,%d)\n","rx_chk_amsdu_invalid_frame",
                 *(undefined2 *)(param_2 + 0x4e),*(undefined2 *)(param_2 + 0x24),3), 2 < DebugLevel)
         ) {
        puVar6 = *(undefined1 **)(param_2 + 0x88);
        printk("80211 Addr=%02x:%02x:%02x:%02x:%02x:%02x\t",*puVar6,puVar6[1],puVar6[2],puVar6[3],
               puVar6[4],puVar6[5]);
        if (2 < DebugLevel) {
          printk("8023 Addr=%02x:%02x:%02x:%02x:%02x:%02x\n",*__s2,__s2[1],__s2[2],__s2[3],__s2[4],
                 __s2[5]);
        }
      }
      iVar4 = param_1 + uVar5 * 0x620 + uVar3;
      *(undefined1 *)(iVar4 + 0x2fa14) = 1;
      *(uint *)(param_1 + (uVar3 + uVar5 * 0x188 + 0xbe1e) * 4 + 0x1c0) = (uint)uVar2;
      *(undefined1 *)(iVar4 + 0x2fa25) = 3;
      return 1;
    }
    iVar4 = param_1 + uVar5 * 0x620 + uVar3;
    if ((*(char *)(iVar4 + 0x2fa14) != '\0') &&
       (param_1 = param_1 + (uVar3 + uVar5 * 0x188) * 4, *(uint *)(param_1 + 0x2fa38) == (uint)uVar2
       )) {
      *(char *)(iVar4 + 0x2fa25) = cVar1;
      if (cVar1 == '\x01') {
        *(undefined1 *)(iVar4 + 0x2fa14) = 0;
        *(undefined4 *)(param_1 + 0x2fa38) = 0;
        *(undefined1 *)(iVar4 + 0x2fa25) = 0;
      }
      if (2 < DebugLevel) {
        printk("%s: AMSDU ATTACK, wcid=%d SN-AN(%d,%d)\n","rx_chk_amsdu_invalid_frame",
               *(undefined2 *)(param_2 + 0x4e),*(undefined2 *)(param_2 + 0x24),cVar1);
        return 1;
      }
      return 1;
    }
    if (3 < DebugLevel) {
      printk("%s: NON-(AMSDU ATTACK), wcid=%d SN-AN(%d,%d)\n","rx_chk_amsdu_invalid_frame",
             *(undefined2 *)(param_2 + 0x4e),*(undefined2 *)(param_2 + 0x24),cVar1);
    }
  }
  return 0;
}


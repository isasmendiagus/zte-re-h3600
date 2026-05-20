// module: plat-zxylzb_9128S.ko
// function: pon_pp_learned_mac @ 0x17034
// size: 148 bytes
//

int pon_pp_learned_mac(void)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined1 auStack_24 [8];
  byte local_1c;
  
  uVar1 = *(ushort *)(&mac_table_size + (*(uint *)(pp_base + 0x8184) & 3) * 2);
  if (uVar1 == 0) {
    iVar5 = 0;
  }
  else {
    uVar4 = 0;
    iVar5 = 0;
    do {
      iVar2 = 0;
      do {
        iVar3 = iVar2 + 1;
        iVar2 = brg_ram_get(uVar4,auStack_24,iVar2);
        if (iVar2 < 0) break;
        if ((local_1c & 0xf0) != 0) {
          iVar5 = iVar5 + 1;
        }
        iVar2 = iVar3;
      } while (iVar3 != 4);
      uVar4 = uVar4 + 1;
    } while (uVar1 != uVar4);
  }
  return iVar5;
}


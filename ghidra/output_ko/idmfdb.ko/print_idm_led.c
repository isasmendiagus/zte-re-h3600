// module: idmfdb.ko
// function: print_idm_led @ 0x124a4
// size: 264 bytes
//

void print_idm_led(void)

{
  char cVar1;
  undefined1 *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar5 = 0;
  puVar2 = &led_handle;
  cVar1 = DAT_00017e74;
  while( true ) {
    if (cVar1 != '\0') {
      printk("led %d, en %d, stat %d, total thoughput %dkbps\n",iVar5,1,
             *(undefined4 *)(puVar2 + 0x34),*(undefined4 *)(puVar2 + 0x14));
      printk("   bind devs:");
      iVar4 = *(int *)(puVar2 + 0xc);
      if (0 < iVar4) {
        iVar6 = 0;
        do {
          if (-1 < *(int *)(*(int *)(puVar2 + 8) + iVar5 * 4)) {
            uVar3 = get_node_index();
            if ((((uVar3 < 0x11) && ((&fdb_list)[uVar3 * 0x128] != '\0')) &&
                ((&DAT_0001341c)[uVar3 * 0x4a] != 0)) &&
               ((*(uint *)((&DAT_0001341c)[uVar3 * 0x4a] + 0x30) & 1) != 0)) {
              printk(&_LC14);
            }
            iVar4 = *(int *)(puVar2 + 0xc);
          }
          iVar6 = iVar6 + 1;
        } while (iVar6 < iVar4);
      }
      printk(&_LC16);
    }
    if (iVar5 == 1) break;
    cVar1 = puVar2[0x44];
    iVar5 = 1;
    puVar2 = puVar2 + 0x40;
  }
  return;
}


// module: tm.ko
// function: tm_show_fast_rule_list @ 0x60b60
// size: 592 bytes
//

void tm_show_fast_rule_list(void)

{
  int iVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  
  puVar5 = (undefined4 *)((int)&g_fast_entry_v6 + 4);
  printk(
        " direction | indx |    sip     |    dip     | sport | dport |protocol|ruleAddr|flwId|hashRam |   extRam   |extIdx\n"
        );
  printk(
        "================================================================================================\n"
        );
  iVar3 = 1;
  iVar4 = 0;
  do {
    puVar5 = puVar5 + 1;
    puVar2 = (undefined1 *)*puVar5;
    if (puVar2 != (undefined1 *)0x0) {
      do {
        while ((*(uint *)(puVar2 + 4) & 0xfffffffd) != 0) {
          iVar1 = iVar3 + iVar4 * 0x10000;
          iVar3 = iVar3 + 1;
          printk("%5u | %5u | %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x:%02x:%02x%02x:%02x%02x:%02x%02x | %02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x:%02x%02x |%6u |%6u |%7u |0x%5x|%4u | 0x%4.4x | 0x%8.8x |%2u\n"
                 ,*puVar2,iVar1,puVar2[8],puVar2[9],puVar2[10],puVar2[0xb],puVar2[0xc],puVar2[0xd],
                 puVar2[0xe],puVar2[0xf],puVar2[0x10],puVar2[0x11],puVar2[0x12],puVar2[0x13],
                 puVar2[0x14],puVar2[0x15],puVar2[0x16],puVar2[0x17],puVar2[0x18],puVar2[0x19],
                 puVar2[0x1a],puVar2[0x1b],puVar2[0x1c],puVar2[0x1d],puVar2[0x1e],puVar2[0x1f],
                 puVar2[0x20],puVar2[0x21],puVar2[0x22],puVar2[0x23],puVar2[0x24],puVar2[0x25],
                 puVar2[0x26],puVar2[0x27],*(undefined2 *)(puVar2 + 0x28),
                 *(undefined2 *)(puVar2 + 0x2a),puVar2[0x2c],*(undefined4 *)(puVar2 + 0x34),
                 *(undefined4 *)(puVar2 + 0x30),*(undefined4 *)(puVar2 + 0x38),
                 *(undefined4 *)(puVar2 + 0x3c),*(undefined4 *)(puVar2 + 0x40));
          puVar2 = *(undefined1 **)(puVar2 + 0x48);
          if (puVar2 == (undefined1 *)0x0) goto LAB_00060d9c;
        }
        iVar1 = iVar3 + iVar4 * 0x10000;
        iVar3 = iVar3 + 1;
        printk("%5u | %5u | %8.8x:%8.8x:%8.8x:%8.8x | %8.8x:%8.8x:%8.8x:%8.8x |%6u |%6u |%7u |%5s  |%4u | 0x%4.4x | 0x%8.8x |%2u\n"
               ,*puVar2,iVar1,0,0,0,*(undefined4 *)(puVar2 + 8),0,0,0,*(undefined4 *)(puVar2 + 0x18)
               ,*(undefined2 *)(puVar2 + 0x28),*(undefined2 *)(puVar2 + 0x2a),puVar2[0x2c],&_LC3,
               *(undefined4 *)(puVar2 + 0x30),*(undefined4 *)(puVar2 + 0x38),
               *(undefined4 *)(puVar2 + 0x3c),*(undefined4 *)(puVar2 + 0x40));
        puVar2 = *(undefined1 **)(puVar2 + 0x48);
      } while (puVar2 != (undefined1 *)0x0);
    }
LAB_00060d9c:
    iVar4 = iVar4 + 1;
    if (iVar4 == 0x200) {
      return;
    }
  } while( true );
}


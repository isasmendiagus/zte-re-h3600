// module: mt7915.ko
// function: set_vow_watf_del_entry @ 0x48694
// size: 692 bytes
//

undefined4 set_vow_watf_del_entry(int param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  byte bVar7;
  undefined4 *puVar8;
  void *__s1;
  int iVar9;
  int iVar10;
  void *__s1_00;
  uint local_50;
  undefined1 local_4c [6];
  undefined1 auStack_46 [6];
  undefined4 uStack_40;
  undefined1 auStack_3c [4];
  undefined1 auStack_38 [4];
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [8];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar2 = sscanf(param_2,"%u-%02x:%02x:%02x:%02x:%02x:%02x",&local_50,&uStack_40,auStack_3c,
                 auStack_38,auStack_34,auStack_30,auStack_2c);
  uVar1 = local_50;
  if (local_50 < 4) {
    __memzero(auStack_46,6);
    if ((iVar2 == 7) && (local_50 < 4)) {
      puVar5 = local_4c;
      puVar8 = &uStack_40;
      do {
        puVar6 = puVar5 + 1;
        *puVar5 = (char)*puVar8;
        puVar5 = puVar6;
        puVar8 = puVar8 + 1;
      } while (puVar6 != auStack_46);
      bVar7 = *(byte *)(param_1 + uVar1 * 0x6c1 + 0xa7a331);
      if (bVar7 != 0) {
        iVar2 = uVar1 * 0x6c1 + 0xa7a332;
        __s1_00 = (void *)(param_1 + iVar2);
        __s1 = __s1_00;
        do {
          iVar3 = memcmp(__s1,local_4c,6);
          if (iVar3 == 0) {
            __memzero(__s1,6);
            if (-1 < DebugLevel) {
              printk("The entry %02x:%02x:%02x:%02x:%02x:%02x founded will be deleted!\n",
                     local_4c[0],local_4c[1],local_4c[2],local_4c[3],local_4c[4],local_4c[5]);
            }
            iVar2 = param_1 + uVar1 * 0x6c1;
            if (*(char *)(iVar2 + 0xa7a331) == '\0') {
              bVar7 = 0;
            }
            else {
              iVar9 = 0;
              iVar3 = iVar9;
              do {
                iVar9 = iVar9 + 1;
                iVar4 = memcmp(__s1_00,auStack_46,6);
                iVar10 = iVar3;
                if (iVar4 != 0) {
                  iVar10 = iVar3 + 1;
                  memmove((void *)(param_1 + local_50 * 0x6c1 + iVar3 * 6 + 0xa7a332),__s1_00,6);
                }
                bVar7 = *(byte *)(iVar2 + 0xa7a331);
                __s1_00 = (void *)((int)__s1_00 + 6);
                iVar3 = iVar10;
              } while (iVar9 < (int)(uint)bVar7);
            }
            *(byte *)(param_1 + uVar1 * 0x6c1 + 0xa7a331) = bVar7 - 1;
            return 1;
          }
          __s1 = (void *)((int)__s1 + 6);
        } while (__s1 != (void *)(param_1 + (short)(ushort)bVar7 * 6 + iVar2));
      }
      if (DebugLevel < 0) {
        return 1;
      }
      printk("The entry %02x:%02x:%02x:%02x:%02x:%02x is not in the list!\n",local_4c[0],local_4c[1]
             ,local_4c[2],local_4c[3],local_4c[4],local_4c[5]);
      return 1;
    }
    if (-1 < DebugLevel) {
      printk(
            "Wrong format, vow_watf_add_entry=[Level]-[Addr]:[Addr]:[Addr]:[Addr]:[Addr]:[Addr]\n[Level] should be among 0 to 3 !\n"
            );
    }
  }
  return 0;
}


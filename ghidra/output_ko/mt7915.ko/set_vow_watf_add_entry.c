// module: mt7915.ko
// function: set_vow_watf_add_entry @ 0x4845c
// size: 568 bytes
//

undefined4 set_vow_watf_add_entry(int param_1,char *param_2)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  void *pvVar8;
  void *__s1;
  void *pvVar9;
  uint local_4c;
  undefined4 local_46;
  undefined2 local_42;
  undefined4 uStack_40;
  undefined1 auStack_3c [4];
  undefined1 auStack_38 [4];
  undefined1 auStack_34 [4];
  undefined1 auStack_30 [4];
  undefined1 auStack_2c [8];
  
  if (param_2 == (char *)0x0) {
    return 0;
  }
  iVar4 = sscanf(param_2,"%u-%02x:%02x:%02x:%02x:%02x:%02x",&local_4c,&uStack_40,auStack_3c,
                 auStack_38,auStack_34,auStack_30,auStack_2c);
  uVar3 = local_4c;
  if (local_4c < 4) {
    if (iVar4 == 7) {
      puVar5 = &uStack_40;
      puVar6 = &local_46;
      do {
        puVar7 = (undefined4 *)((int)puVar6 + 1);
        *(char *)puVar6 = (char)*puVar5;
        puVar5 = puVar5 + 1;
        puVar6 = puVar7;
      } while (puVar7 != &uStack_40);
      pvVar8 = (void *)(param_1 + 0xa7a332);
      bVar2 = false;
      do {
        bVar1 = *(byte *)((int)pvVar8 + -1);
        if (bVar1 != 0) {
          __s1 = pvVar8;
          do {
            pvVar9 = (void *)((int)__s1 + 6);
            iVar4 = memcmp(__s1,&local_46,6);
            if (iVar4 == 0) {
              if (DebugLevel < 0) {
                bVar2 = true;
              }
              else {
                bVar2 = true;
                printk("This MAC Address %02x:%02x:%02x:%02x:%02x:%02x is duplicate.\n",
                       local_46 & 0xff,local_46._1_1_,local_46._2_1_,local_46 >> 0x18,
                       (undefined1)local_42,local_42._1_1_);
              }
              break;
            }
            __s1 = pvVar9;
          } while (pvVar9 != (void *)((uint)bVar1 * 6 + (int)pvVar8));
        }
        pvVar8 = (void *)((int)pvVar8 + 0x6c1);
        if (pvVar8 == (void *)(param_1 + 0xa7be36)) {
          if (!bVar2) {
            iVar4 = param_1 + uVar3 * 0x6c1;
            bVar1 = *(byte *)(iVar4 + 0xa7a331);
            *(byte *)(iVar4 + 0xa7a331) = bVar1 + 1;
            param_1 = param_1 + uVar3 * 0x6c1 + (uint)bVar1 * 6 + 0xa7a330;
            *(uint *)(param_1 + 2) = local_46;
            iVar4 = DebugLevel;
            *(undefined2 *)(param_1 + 6) = local_42;
            if (-1 < iVar4) {
              printk("The entry Level %d - %02x:%02x:%02x:%02x:%02x:%02x is set complete!\n",
                     local_4c,local_46 & 0xff,local_46._1_1_,local_46 >> 0x10 & 0xff,
                     local_46 >> 0x18,(undefined1)local_42,local_42._1_1_);
            }
          }
          return 1;
        }
      } while( true );
    }
    if (-1 < DebugLevel) {
      printk(
            "Wrong format, vow_watf_add_entry=[Level]-[Addr]:[Addr]:[Addr]:[Addr]:[Addr]:[Addr]\n[Level] should be among 0 to 3 !\n"
            );
    }
  }
  return 0;
}


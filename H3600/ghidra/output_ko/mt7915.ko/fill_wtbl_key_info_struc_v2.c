// module: mt7915.ko
// function: fill_wtbl_key_info_struc_v2 @ 0x116eac
// size: 648 bytes
//

void * fill_wtbl_key_info_struc_v2(uint *param_1,int param_2)

{
  undefined1 uVar1;
  char cVar2;
  byte bVar3;
  void *pvVar4;
  size_t __n;
  uint uVar5;
  int iVar6;
  bool bVar7;
  
  *(undefined1 *)(param_2 + 5) = 0;
  if ((*param_1 & 0xfffffffd) == 1) {
    *(undefined1 *)(param_2 + 4) = 1;
    return (void *)0x0;
  }
  *(undefined1 *)(param_2 + 4) = 0;
  uVar1 = *(undefined1 *)((int)param_1 + 0xf);
  *(undefined1 *)(param_2 + 9) = 0x24;
  *(undefined1 *)(param_2 + 10) = uVar1;
  __n = (size_t)(byte)param_1[0x18];
  if (((param_1[2] & 0x20) == 0) || (__n != 0x20)) {
    if (__n < 0x21) {
      bVar7 = false;
      goto LAB_00116f3c;
    }
    if (-1 < DebugLevel) {
      printk("%s: KeyLen is larger than the aucKeyMaterial\n","fill_wtbl_key_info_struc_v2");
    }
LAB_00116f1c:
    pvVar4 = (void *)0x1;
  }
  else {
    __n = 0x10;
    bVar7 = true;
    *(undefined1 *)(param_1 + 0x18) = 0x10;
LAB_00116f3c:
    *(char *)(param_2 + 0xb) = (char)__n;
    os_move_mem((void *)(param_2 + 0xc),param_1 + 4,__n);
    pvVar4 = (void *)hex_dump_with_cat_and_lvl
                               ("install key:",(void *)(param_2 + 0xc),
                                *(undefined1 *)(param_2 + 0xb),0xf,1,3);
    uVar5 = param_1[2];
    if ((uVar5 & 0xe) == 0) {
      if ((uVar5 & 0x10) == 0) {
        if ((uVar5 & 0x20) == 0) {
          if ((uVar5 & 0x40) == 0) {
            if ((uVar5 & 0x80) == 0) {
              if ((uVar5 & 0x100) == 0) {
                if (0 < DebugLevel) {
                  printk("%s(%d): Not support Cipher[0x%x]\n","fill_wtbl_key_info_struc_v2",0x886);
                  return (void *)0x1;
                }
                goto LAB_00116f1c;
              }
              *(undefined1 *)(param_2 + 8) = 8;
            }
            else {
              *(undefined1 *)(param_2 + 8) = 7;
            }
          }
          else {
            *(undefined1 *)(param_2 + 8) = 6;
          }
        }
        else {
          *(undefined1 *)(param_2 + 8) = 5;
        }
      }
      else {
        *(undefined1 *)(param_2 + 8) = 4;
        os_move_mem((void *)(param_2 + 0x1c),param_1 + 0xe,8);
        pvVar4 = os_move_mem((void *)(param_2 + 0x24),param_1 + 0xc,8);
      }
    }
    else {
      cVar2 = (char)param_1[0x18];
      if (cVar2 == '\x05') {
        *(undefined1 *)(param_2 + 8) = 1;
      }
      else if (cVar2 == '\r') {
        *(undefined1 *)(param_2 + 8) = 2;
      }
      else if (cVar2 == '\x10') {
        *(undefined1 *)(param_2 + 8) = 3;
      }
    }
    if (2 < DebugLevel) {
      pvVar4 = (void *)printk("%s: ucCipherId = %d, ucKeyIdx = %d\n","fill_wtbl_key_info_struc_v2",
                              *(undefined1 *)(param_2 + 8),*(undefined1 *)(param_2 + 10));
    }
    bVar3 = *(byte *)(param_2 + 9);
    if (!bVar7) {
      pvVar4 = (void *)0x0;
    }
    *(char *)(param_2 + 5) = *(char *)(param_2 + 5) + '\x01';
    if (bVar7) {
      iVar6 = param_2 + 8 + (uint)bVar3;
      *(undefined1 *)(iVar6 + 1) = 0x24;
      *(undefined1 *)(param_2 + 8 + (uint)bVar3) = 10;
      *(undefined1 *)(iVar6 + 3) = 0x10;
      os_move_mem((void *)(iVar6 + 4),param_1 + 8,0x10);
      hex_dump_with_cat_and_lvl("install igtk key:",(void *)(iVar6 + 4),0x10,0xf,1,3);
      pvVar4 = (void *)0x0;
      *(char *)(param_2 + 5) = *(char *)(param_2 + 5) + '\x01';
    }
  }
  return pvVar4;
}


// module: mt7915.ko
// function: fill_wtbl_key_info_struc @ 0x116cdc
// size: 460 bytes
//

undefined4 fill_wtbl_key_info_struc(uint *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  uint uVar2;
  
  if ((*param_1 & 0xfffffffd) == 1) {
    *(undefined1 *)(param_2 + 4) = 1;
    *(undefined1 *)(param_2 + 9) = 0x20;
    return 0;
  }
  *(undefined1 *)(param_2 + 4) = 0;
  *(undefined1 *)(param_2 + 8) = *(undefined1 *)((int)param_1 + 0xf);
  uVar2 = (uint)(byte)param_1[0x18];
  if (0x20 < uVar2) {
    if (-1 < DebugLevel) {
      printk("%s: KeyLen is larger than the aucKeyMaterial\n","fill_wtbl_key_info_struc",uVar2,
             DebugLevel,param_4);
    }
    return 1;
  }
  *(byte *)(param_2 + 9) = (byte)param_1[0x18];
  os_move_mem((void *)(param_2 + 0xc),param_1 + 4,uVar2);
  uVar2 = param_1[2];
  if ((uVar2 & 0xe) == 0) {
    if ((uVar2 & 0x10) == 0) {
      if ((uVar2 & 0x20) == 0) {
        if ((uVar2 & 0x40) == 0) {
          if ((uVar2 & 0x80) == 0) {
            if ((uVar2 & 0x100) == 0) {
              if (DebugLevel < 1) {
                return 1;
              }
              printk("%s(%d): Not support Cipher[0x%x]\n","fill_wtbl_key_info_struc",0x837,uVar2,
                     param_4);
              return 1;
            }
            *(undefined1 *)(param_2 + 7) = 0xc;
          }
          else {
            *(undefined1 *)(param_2 + 7) = 0xb;
          }
        }
        else {
          *(undefined1 *)(param_2 + 7) = 10;
        }
      }
      else {
        *(undefined1 *)(param_2 + 7) = 4;
      }
    }
    else {
      *(undefined1 *)(param_2 + 7) = 2;
      os_move_mem((void *)(param_2 + 0x1c),param_1 + 0xe,8);
      os_move_mem((void *)(param_2 + 0x24),param_1 + 0xc,8);
    }
  }
  else {
    cVar1 = *(char *)(param_2 + 9);
    if (cVar1 == '\x05') {
      *(undefined1 *)(param_2 + 7) = 1;
    }
    else if (cVar1 == '\r') {
      *(undefined1 *)(param_2 + 7) = 5;
    }
    else if (cVar1 == '\x10') {
      *(undefined1 *)(param_2 + 7) = 7;
    }
  }
  uVar2 = param_1[1];
  if ((uVar2 & 0xfffffffd) == 0) {
    *(undefined1 *)(param_2 + 5) = 0;
    *(undefined1 *)(param_2 + 6) = 0;
    uVar2 = param_1[1];
  }
  if (uVar2 - 1 < 2) {
    *(undefined1 *)(param_2 + 5) = 1;
    if (((param_1[2] & 0x200) != 0) ||
       (((param_1[2] & 0x20) != 0 && (*(char *)(param_2 + 9) == ' ')))) {
      *(undefined1 *)(param_2 + 6) = 1;
      return 0;
    }
  }
  return 0;
}


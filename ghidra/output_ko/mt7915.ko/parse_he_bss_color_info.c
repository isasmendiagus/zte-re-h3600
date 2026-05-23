// module: mt7915.ko
// function: parse_he_bss_color_info @ 0x205e98
// size: 216 bytes
//

void parse_he_bss_color_info(int param_1,int param_2)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  byte bVar4;
  
  bVar1 = *(byte *)(param_2 + 0x142);
  bVar4 = bVar1 & 0x3f;
  bVar2 = bVar1 >> 7;
  if (3 < DebugLevel) {
    printk("%s: bss_color_info = 0x%x, color = %d, disabled = %d\n","parse_he_bss_color_info",bVar1,
           bVar4,bVar2);
  }
  if ((bVar1 & 0x3f) != 0) {
    iVar3 = *(int *)(param_1 + 0x14);
    if (iVar3 == 2) {
      iVar3 = GetStaCfgByWdev(*(undefined4 *)(param_1 + 8),param_1);
      iVar3 = memcmp((void *)(param_2 + 6),(void *)(iVar3 + 0x212428),6);
      if (iVar3 == 0) {
        set_bss_color_info();
        iVar3 = *(int *)(param_1 + 0x14);
      }
      else {
        bss_color_collision_detect(param_1,bVar2,bVar4);
        iVar3 = *(int *)(param_1 + 0x14);
      }
    }
    if (iVar3 == 1) {
      bss_color_collision_detect(param_1,bVar2,bVar4);
      return;
    }
  }
  return;
}


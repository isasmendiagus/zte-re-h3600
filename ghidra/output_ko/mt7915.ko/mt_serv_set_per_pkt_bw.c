// module: mt7915.ko
// function: mt_serv_set_per_pkt_bw @ 0x2527ec
// size: 100 bytes
//

int mt_serv_set_per_pkt_bw(undefined4 *param_1)

{
  int unaff_r4;
  
  if (*(char *)(param_1 + 0x7d1) == '\0') {
    unaff_r4 = 0;
  }
  if ((*(char *)(param_1 + 0x7d1) != '\0') &&
     (unaff_r4 = (**(code **)(param_1[0x7c4] + 0x88))
                           (*param_1,*(undefined1 *)
                                      ((int)param_1 +
                                      (uint)*(byte *)(param_1 + 0x133) * 0xd18 + 0x1137)),
     unaff_r4 != 0)) {
    printk("%s: err=0x%08x\n","mt_serv_set_per_pkt_bw",unaff_r4);
  }
  return unaff_r4;
}


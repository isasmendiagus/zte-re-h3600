// module: plat-zxylzb_9128S.ko
// function: hwnat_set_hook_ptr @ 0x154e4
// size: 52 bytes
//

undefined4 hwnat_set_hook_ptr(void)

{
  hwnat_skb_to_foe_hook = hwnat_skb_to_foe;
  multicast_flood_is_bind_hook = multicast_flood_is_bind;
  hwnat_is_from_cpu_hook = hwnat_is_from_cpu;
  return 0;
}


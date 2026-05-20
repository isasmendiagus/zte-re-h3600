// module: plat-zxylzb_9128S.ko
// function: hwnat_unset_hook_ptr @ 0x15518
// size: 32 bytes
//

undefined4 hwnat_unset_hook_ptr(void)

{
  hwnat_skb_to_foe_hook = 0;
  multicast_flood_is_bind_hook = 0;
  hwnat_is_from_cpu_hook = 0;
  return 0;
}


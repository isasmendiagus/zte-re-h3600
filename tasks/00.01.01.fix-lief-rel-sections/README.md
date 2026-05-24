# fix-lief-rel-sections — patch LIEF #661 to enable `.ko` section addition

**ID**: 00.01.01
**Parent**: [00.01 eth-driver](../00.01.eth-driver/)
**Children**: none
**TaskList items**: #21
**Status**: 🚧 IN PROGRESS — patch written, building

## Why

[`tasks/00.01.eth-driver/scripts/ko_printk_splice.py`](../00.01.eth-driver/scripts/ko_printk_splice.py)
needs LIEF to add a new `.text.splice` section to ARM kernel modules
(`switch.ko`, etc.). LIEF 0.17.6 fails:

- `binary.add(section, loaded=False)` → crashes (`unordered_map::at`, "Node not found")
- `binary.add(section, loaded=True)`  → silently drops the section (returns `None`, no section added)

This is **upstream issue [#661](https://github.com/lief-project/LIEF/issues/661)**
("add section in ELF file : unexpected section size"), open since 2022,
labeled `help wanted`. Affects all ARM relocatable ELF files (`.ko`, `.o`).

Rather than pivot to a runtime tracer kernel module, this subtask fixes
LIEF directly so the original binary-splicer plan works.

## The bug, in concrete terms

Both code paths in `src/ELF/Binary.tcc` assume the file has LOAD segments
(true for `EXEC`/`DYN` files, false for `REL` files):

### `add_section<true>` (when `loaded=True`)

```cpp
Segment* segment_added = add(seg_for_section(section));
if (segment_added == nullptr) {
  LIEF_ERR("Can't add a LOAD segment of the section");
  return nullptr;  // ← silent drop for REL files
}
```

The inner `add(Segment&)` (in `Binary.cpp:1048`) has switch cases for
`EXEC` and `DYN` only; `REL` falls into the `default:` branch which
returns `nullptr` with a warning `"Adding segment not implemented for REL"`.

### `add_section<false>` (when `loaded=False`)

```cpp
const uint64_t last_offset_segments = last_offset_segment();  // == 0 for REL
uint64_t last_offset = 0;
switch (pos) {
  case AUTO:
  case POST_SEGMENT: last_offset = last_offset_segments; break;  // == 0
  ...
}
const uint64_t delta = section.size();
shift_sections(last_offset, delta);                              // shifts every section by delta
auto alloc = datahandler_->make_hole(last_offset, section.size()); // inserts at offset 0 → corrupts ELF header
```

For REL files (no segments), `last_offset_segments == 0`, so we shift
everything from offset 0 — including the ELF header bytes. The downstream
builder then can't find expected nodes in its internal `unordered_map` →
`unordered_map::at` exception.

## The fix (two surgical changes in `Binary.tcc`)

**Change 1**: `add_section<true>` detects REL early and delegates to
`add_section<false>` (skipping the segment-creation path entirely).
REL files don't have LOAD segments by spec — the kernel module loader
places each section at its own runtime address.

**Change 2**: `add_section<false>` uses `last_offset_section()` as the
floor when `last_offset_segments == 0` (REL case). This appends new
section data AFTER existing section content instead of at offset 0.

Both changes are localized to `src/ELF/Binary.tcc` and don't affect the
EXEC/DYN code paths (which already work).

## Verification plan

1. Build LIEF from source in this folder (`api/python/`, scikit-build-core)
2. `pip install --force-reinstall --no-deps` to replace the system LIEF
3. Re-run `tasks/00.01.eth-driver/scripts/ko_printk_splice.py` on `switch.ko`
4. Verify output `.ko` has a new `.text.splice` section via `readelf -S`
5. Verify relocations are present via `readelf -r`
6. (Future) Smoke-test on the device with `insmod`

## After this works

- Promote `tasks/00.01.eth-driver/PLAN_init_debug.md` Phase 1 from
  ⛔ BLOCKED to 🚧 IN PROGRESS, swap "tracer.ko pivot" back to "splicer"
- Submit the patch as a PR to upstream LIEF (optional but valuable —
  this issue has been open since 2022)
- Update `tasks/00.01.eth-driver/research/splice_poc/README.md` with the
  fix and the new "yes, LIEF works after this patch" status

## Files in this subtask

```
tasks/00.01.01.fix-lief-rel-sections/
├── README.md       (this file)
└── LIEF/           (cloned source — gitignored at the parent level if needed)
    └── src/ELF/Binary.tcc  ← the file we patched
```

The `LIEF/` clone is large (~71 MB). Not committed; the patch itself is
tiny and lives entirely in the two edits to `Binary.tcc`. To reproduce:

```sh
cd tasks/00.01.01.fix-lief-rel-sections
git clone --depth=1 https://github.com/lief-project/LIEF.git
# apply the two edits documented in this README
cd LIEF/api/python
pip install --force-reinstall --no-deps .
```

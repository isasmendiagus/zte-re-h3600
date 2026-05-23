#!/usr/bin/env bash
# setup_fork.sh — recreate the ZTE ZX driver tree on top of a modern Linux LTS
#
# Resucita el código eliminado en enero 2021 (commit 89d4f98ae90d y siguientes)
# y lo reaplica encima de un kernel base elegido por el usuario (por defecto
# v6.6 LTS, fijada por línea de comandos).
#
# Uso:
#   ./setup_fork.sh [BASE_TAG]              # por defecto v6.6
#   ./setup_fork.sh v6.12                   # otra base
#
# Resultado: clona linux mainline en ./linux-zxic-fork/, crea una rama
# "zxic-resurrect-${BASE_TAG}" y hace cherry-pick de los commits que
# reintroducen TODO el subsistema ZX.
#
# Política de errores: ante un conflicto en cherry-pick, el script se detiene
# con `git status` mostrado para que el usuario decida (NO continúa
# automáticamente, NO --skip).
#
set -euo pipefail

BASE_TAG="${1:-v6.6}"
WORKDIR="$(pwd)/linux-zxic-fork"
BRANCH="zxic-resurrect-${BASE_TAG}"

# --- 1. Mainline checkout --------------------------------------------------
if [ ! -d "${WORKDIR}/.git" ]; then
    echo "==> Clonando linux mainline en ${WORKDIR} (puede tardar 10-30 min)..."
    git clone https://github.com/torvalds/linux.git "${WORKDIR}"
fi

cd "${WORKDIR}"

echo "==> Asegurando historia completa..."
git fetch --unshallow 2>/dev/null || git fetch --all --tags

# --- 2. Rama base ----------------------------------------------------------
echo "==> Creando rama '${BRANCH}' desde ${BASE_TAG}..."
git checkout -B "${BRANCH}" "${BASE_TAG}"

# --- 3. Listado de commits a revertir (orden cronológico inverso de la
# eliminación: primero el "leftover" tardío, luego los grandes 2021-01).
# Reverting them en este kernel base reintroduce el código.
# Si hay conflictos, ceden naturalmente ya que el código eliminado no existe.
#
# IMPORTANTE: NO usamos cherry-pick desde un commit antiguo (no funcionaría
# bien con el "punto de eliminación"); usamos `git revert --no-edit` sobre
# los commits que ELIMINARON el código. El revert reintroduce los archivos.
# ---------------------------------------------------------------------------
REVERTS=(
    635e4172bd0a   # 2021-11-02 arm: remove zte zx platform left-over
    b1e202503508   # 2021-08-31 dt-bindings: display: remove zte,vou.txt
    d014c93515e9   # 2021-08-21 dt-bindings: clock: remove obsolete zte zx header
    09f3824342f6   # 2021-08-21 reset: simple: remove ZTE details in Kconfig
    47ddb72f7893   # 2021-08-19 drm: zte: remove obsolete DRM Support for ZTE SoCs
    0c4f8fd3ed9c   # 2021-06-27 ASoC: remove zte zx dangling kconfig
    30f1ec70ddf5   # 2021-01-20 watchdog: remove zte zx driver
    dc98f1d655ca   # 2021-01-20 ASoC: remove zte zx drivers
    73da3f0cca94   # 2021-01-20 thermal/drivers/zx: Remove zx driver
    a2bc9b21fd3f   # 2021-01-20 pwm: Remove ZTE ZX driver
    9483b961ad08   # 2021-01-20 power/reset: remove zte zx driver
    799ddc037085   # 2021-01-20 media: rc: remove zte zx ir driver
    73cc584cfced   # 2021-01-20 i2c: remove zte zx bus driver
    484c58d6601c   # 2021-01-20 pinctrl: remove zte zx driver
    f0a2c77eb8e9   # 2021-01-20 gpio: remove zte zx driver
    1c8963f83013   # 2021-01-20 dmaengine: remove zte zx driver
    bcbe6005eb18   # 2021-01-20 clk: remove zte zx driver
    89d4f98ae90d   # 2021-01-18 ARM: remove zte zx platform
)

echo "==> Ejecutando ${#REVERTS[@]} reverts..."
for sha in "${REVERTS[@]}"; do
    echo "  --> revert ${sha}"
    if ! git revert --no-edit "${sha}"; then
        cat <<EOF

================================================================
CONFLICT al revertir ${sha}.
Razón típica: el archivo "víctima" original ya no existe en ${BASE_TAG}
(por refactor mainline desde 5.11 hacia ${BASE_TAG}) o algún hunk se ha
solapado con cambios posteriores.

Procedimiento:
  1) git status        para ver qué falla
  2) Resuelve manualmente (a menudo basta con 'git rm' los ficheros
     que ya no existen y 'git add' las extracciones limpias).
  3) git revert --continue
  4) Re-ejecuta este script desde el siguiente revert.

Conflictos esperados (basados en la diff observable):
  * MAINTAINERS              — quitado el bloque ZX manualmente
  * arch/arm/Kconfig         — la entry ARCH_ZX y debug
  * arch/arm/Makefile        — la línea machine-\$(CONFIG_ARCH_ZX) := zx
  * arch/arm/boot/dts/Makefile (ahora arch/arm/boot/dts/Makefile.zte
                                según versión)
  * Documentation/devicetree/bindings/serial/pl011.yaml
                            — la lista de compatibles cambió de schema
================================================================
EOF
        exit 1
    fi
done

# --- 4. Defconfig opcional -------------------------------------------------
echo "==> Reverts aplicados. Sugerencias:"
echo "    make ARCH=arm zx_defconfig"
echo "    make ARCH=arm O=build-zx -j\$(nproc)"
echo
echo "==> Rama '${BRANCH}' lista en ${WORKDIR}"
echo "==> Para empezar tu port ZX279128S:"
echo "    git checkout -b zx279128s-port"
echo "    cp arch/arm/boot/dts/zx296702.dtsi arch/arm/boot/dts/zx279128s.dtsi"
echo "    # editar zx279128s.dtsi con direcciones del DTB extraído de NAND"

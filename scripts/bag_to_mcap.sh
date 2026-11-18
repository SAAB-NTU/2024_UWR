#!/usr/bin/env bash
# Convert older kf_3dof output bags (sqlite3 .db3) to MCAP so Foxglove can
# decode the custom sonar_msgs types (MCAP embeds the message definitions).
# Bags recorded since kf_3dof switched to MCAP don't need this.
#
# Usage: pixi run to-mcap <bag_dir_or_parent_dir> [...]
#   Each <name>.bag/ holding a .db3 gets a sibling <name>.mcap/ directory.
#   Already-converted and already-MCAP bags are skipped.
set -euo pipefail

if [ $# -eq 0 ]; then
    echo "usage: $0 <bag_dir_or_parent_dir> [...]" >&2
    exit 1
fi

tmp_yaml=$(mktemp --suffix=.yaml)
trap 'rm -f "$tmp_yaml"' EXIT

convert_one() {
    local in="${1%/}"
    local out="${in%.bag}.mcap"
    if ! grep -q "storage_identifier: sqlite3" "$in/metadata.yaml"; then
        echo "skip  $in (not sqlite3)"
        return
    fi
    if [ -e "$out" ]; then
        echo "skip  $in (exists: $out)"
        return
    fi
    printf 'output_bags:\n- uri: %s\n  storage_id: mcap\n  all_topics: true\n' "$out" > "$tmp_yaml"
    echo "conv  $in -> $out"
    ros2 bag convert -i "$in" -o "$tmp_yaml" > /dev/null
}

for arg in "$@"; do
    if [ -f "$arg/metadata.yaml" ]; then
        convert_one "$arg"
    else
        while IFS= read -r meta; do
            convert_one "$(dirname "$meta")"
        done < <(find "$arg" -name metadata.yaml -path '*.bag/*' | sort)
    fi
done

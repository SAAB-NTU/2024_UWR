# Sourced by pixi on activation: overlay the colcon workspace if it has been built.
if [ -f "$PIXI_PROJECT_ROOT/install/local_setup.sh" ]; then
    . "$PIXI_PROJECT_ROOT/install/local_setup.sh"
fi

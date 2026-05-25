# **Part A:** How to Build and Run

The project can be built using make. We also have some convenience tools:

## On Linux and MacOS

### Using Bash, Dash, zsh, etc.

- run `source csharpflat` in the project root
- a `compile_commands.json` is created for smooth integration with your ide (requires bear)
- use displayed aliases to compile and run

### Using Nix

- run `nix develop` in the project root
- a `compile_commands.json` is created for smooth integration with your ide (requires bear)
- use displayed aliases to compile and run

### Using make

- run `make <target>`, available targets are:
  - `part_a` for exercise part a,
  - `part_bc` for exercise part b and c,
  - `part_d` for exercise part d,
  - `part_e` for exercise part e _and_
  - `all` to build all above targets.
- the resulting binaries are written to `/bin/<target>` (except `all` of course).

## On Windows

I have no idea how to use windows, so please don't ask me.

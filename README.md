# findf

A Linux command-line utility for recursively searching files, similar to `find`.

## Quickstart

```bash
git clone <repo-url>
cd find_command
bash setup.sh        # checks deps, builds binary

./findf .            # list all files in current directory
```

## Usage

```
findf <dir>                           List all files recursively
findf <dir> -name <filename>          Find by exact filename
findf <dir> -mmin [+/-]<minutes>      Find by modification time
findf <dir> -inum <inode>             Find by inode number
```

Append `-delete` as the 5th argument to delete matched files:

```
findf <dir> -name <filename> -delete
```

### Examples

```bash
findf /home/user/docs -name report.txt
findf /var/log -mmin -10          # modified less than 10 minutes ago
findf /var/log -mmin +60          # modified more than 60 minutes ago
findf /tmp -inum 1234567
findf /tmp -name scratch.txt -delete
```

## Building

**Using make (recommended):**

```bash
make                   # release build
make BUILD=debug       # debug build with -g symbols
make clean             # remove build artifacts
make help              # show all targets
```

**Using CMake:**

```bash
cmake --preset linux-debug
cmake --build out/build/linux-debug
```

## Running Tests

```bash
make test
```

## Installing to PATH

```bash
make install                        # installs to /usr/local/bin (needs sudo)
make install PREFIX=$HOME/.local    # installs to ~/.local/bin (no sudo needed)
make uninstall                      # removes the installed binary
```

## Requirements

- Linux / POSIX
- `g++` (C++14 or later)
- `make`

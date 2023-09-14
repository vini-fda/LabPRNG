# Task 5: Get Random Numbers from /dev/urandom

```bash
$ cat /dev/urandom | hexdump
```

```bash
$ head -c 1M /dev/urandom > output.bin
$ ent output.bin
```

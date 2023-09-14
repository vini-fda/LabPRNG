# Task 4: Get Pseudo Random Numbers from /dev/random

Question: If a server uses /dev/random to generate the random session key with a client. Please
describe how you can launch a Denial-Of-Service (DOS) attack on such a server.

Answer: The server will block when the entropy pool is empty. To launch a DOS attack, we can simply read from /dev/random until the entropy pool is empty.

```bash
$ cat /dev/random > /dev/null
```

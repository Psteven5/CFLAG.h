# CFLAG.h
No bullshit command line flag parser for C

There is not much to this header:
 * CFLAG(FLAG) that parses the flag -FLAG and stores its result in the FLAG variable.
 * CFLAGS(...) (|...| <= 16) that does this for multiple flags. (for convenience)

Check example.c for more details

```c
int main(int argc, char **argv) {
  char const *i = NULL, *o = NULL;
  bool h = false;
  CFLAGS(i, o, h);
  printf("i=%s, o=%s, h=%s\n", i, o, h ? "true" : "false");
}
```
```
./main -i=main.js -h -o trash

i=main.js, o=trash, h=true
```

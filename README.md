# RingBuffer
A lightweight, basic C++ Ring Buffer

### Initially wrote this as a POC, however if this comes in useful to you, feel free to enjoy it :) ###

```cpp
ring_buffer<char, 500> r_buf{};
for (int i = 0; i < 500; i++) {
    r_buf.write('a');
}
r_buf.write('b');
r_buf.as_string(); // expected output is 1 x b, and 499 x a.
```

# License #
This project is licensed under the MIT License (yay! free software!) - see the [LICENSE](https://github.com/Yuhanun/RingBuffer/blob/master/LICENSE) file for details.

# Acknowledgments #
Thanks to anyone whose code was used.

### Buy me a coffee ;) (BTC) ###
32dcJ31dsxj8BMD5oD3mWKTDFSzpFHuHP1

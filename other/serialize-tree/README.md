# serialize-tree

## 1. Description

* Serialize/deserialize tree
* Tree node stores value in `int`, `double`, `string` data types
* Tree sample shows bellow

```

                             +---------+
                             |    8    |
                             +---------+
                                  |
                 +----------------+---------------+
                 |                                |
            +---------+                      +---------+
            |  "bar"  |                      |  "baz"  |
            +---------+                      +---------+
                 |                                |
     +-----------+-----------+             +------+------+
     |           |           |             |             |
+---------+ +---------+ +---------+    +---------+ +---------+
|  2.015  | |   2015  | | "2015"  |    |  "foo"  | | 6.28318 |
+---------+ +---------+ +---------+    +---------+ +---------+
     |                                                  |
+---------+                                        +---------+
|    9    |                                        | "hello" |
+---------+                                        +---------+
```

* Implement tree data structure
* Implement tree serialization into file
* Implement tree deserialization from file
* Implement tree print function
* Implement as command-line application (`-i [INPUT FILE] -o [OUTPUT FILE]`)

## 2. Features

* Pure C++ (without additional libraries)
* C++17 standard
* `serialize()`, `deserialize()`, `print()`
* Unit-tests
* Cmake
* Command-line parsing
* Serialize tree format checking

## 3. How to

1. `make && make test`
2. `./serialize-tree -i input.txt -o output.txt`

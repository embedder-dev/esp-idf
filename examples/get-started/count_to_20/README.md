# Count to 20 Example

A simple ESP-IDF example that counts from 1 to 20, printing each number to the serial console with a one-second delay between each count.

## How to Use

### Build and Flash

```
idf.py set-target esp32s3
idf.py build
idf.py -p PORT flash monitor
```

Replace `PORT` with your serial port name.

### Example Output

```
Counting to 20:
1
2
3
...
20
Done counting!
```

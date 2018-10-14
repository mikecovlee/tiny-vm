# Tiny Virtual Machine Byte Code

### Instructions
| Mnemonic | Opcode (in hex) | Other bytes ([count]: [operand labels]) | Description |
|:--------:|:---------------:|:---------------------------------------:|:-----------:|
|nop|00|none|Do noting|
|pop|01|none|Pop top element from stack|
|push_i32|02|4:bytes|Push an 32bit integer into stack|
|push_i64|03|8:bytes|Push an 64bit integer into stack|
|add_i32|04|none|Add two element|
|add_i64|05|none|Add two element|
|sub_i32|06|none|Subtract two element|
|sub_i64|07|none|Subtract two element|
|int|08|8:index|Call interrupt|

### Interrupts
| Mnemonic | Opcode (in hex) | Other bytes ([count]: [operand labels]) | Description |
|:--------:|:---------------:|:---------------------------------------:|:-----------:|
|Print_i32|01|4:bytes|Print top element|
|Print_i64|02|8:bytes|Print top element|
# Tiny Virtual Machine Byte Code

### Instructions
| Mnemonic | Opcode (in hex) | Other bytes ([count]: [operand labels]) | Description |
|:--------:|:---------------:|:---------------------------------------:|:-----------:|
|nop|00|none|Do noting|
|int|01|1:index|Call interrupt|
|jmp|02|8:index|Jump to an 64bit index|
|jmp_if|03|8:index|Jump to an 64bit index if top element equals to zero|
|pop|04|none|Pop top element from stack|
|push_i32|05|4:bytes|Push an 32bit integer into stack|
|push_i64|06|8:bytes|Push an 64bit integer into stack|
|add_i32|07|none|Add two element|
|add_i64|08|none|Add two element|
|sub_i32|09|none|Subtract two element|
|sub_i64|0a|none|Subtract two element|
|mul_i32|0b|none|Multiply two element|
|mul_i64|0c|none|Multiply two element|
|div_i32|0d|none|Divide two element|
|div_i64|0e|none|Divide two element|
|eof|ff|none|Mark the end of the file|

### Interrupts
| Mnemonic | Opcode (in hex) | Other bytes ([count]: [operand labels]) | Description |
|:--------:|:---------------:|:---------------------------------------:|:-----------:|
|Print_i32|01|4:bytes|Print top element|
|Print_i64|02|8:bytes|Print top element|
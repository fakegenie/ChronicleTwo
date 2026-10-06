#ifndef INCLUDE_ASM_H
#define INCLUDE_ASM_H

#define INCLUDE_ASM(FOLDER, NAME)
#define INCLUDE_RODATA(FOLDER, NAME)

#define INCLUDE_BSS(NAME, SIZE) unsigned char NAME##__DATA[SIZE]

#endif

/* Header.h - Define header portion of frame 
 *
 *
 */
#pragma once

typedef struct header Header;

struct header {
	short int sid;
	short int rid;
	char priority; 
	short int seqNum;
	long int payloadSize;		// Number of bytes in payload after this header
	char payLoadType;			// 0: Text, 1: Audio, 2: Image etc.
	char encryption;			// 0: None, 1: XOR,	  2: Vigenere	3: Both
	char compression;			// 0: None, 1: RLE,	  2: Huffman,	3: Both
};
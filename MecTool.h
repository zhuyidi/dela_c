#ifndef _MEC_TOOL_H_
#define _MEC_TOOL_H_

#include<string.h>

typedef unsigned char boolean;
typedef boolean u8;
typedef unsigned short u16;
typedef unsigned int u32;
#define	TRUE			1
#define	FALSE			0

#define NOT_FOUND		-1

char *getSubstringBeforeLastChar(const char *str, char ch, char *tagStr);
int lastCharIndex(const char *str, char ch);
char *getSubstringAfterLastChar(const char *str, char ch, char *tagStr);

char *getSubstringAfterLastChar(const char *str, char ch, char *tagStr) {
	int index = lastCharIndex(str, ch);
	int i;
	
	if(NOT_FOUND == index) {
		tagStr[0] = 0;
		
		return tagStr;
	}

	for(i = 0, ++index; str[index]; index++, i++) {
		tagStr[i] = str[index];
	}
	tagStr[i] = 0;

	return tagStr;
}

int lastCharIndex(const char *str, char ch) {
	int index = NOT_FOUND;
	int i;
	
	for(i = 0; str[i]; i++) {
		if(str[i] == ch) {
			index = i;
		}
	}

	return index;
}

char *getSubstringBeforeLastChar(const char *str, char ch, char *tagStr) {
	int index = lastCharIndex(str, ch);
	int i;
	
	if(NOT_FOUND == index) {
		*tagStr = 0;
		
		return tagStr;
	}

	for(i = 0; i < index; i++) {
		tagStr[i] = str[i];
	}
	tagStr[i] = 0;

	return tagStr;
}

#endif

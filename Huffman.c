#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#include"MecTool.h"

typedef struct{
	unsigned char alpha;
	unsigned int freq;
}FREQ;

typedef struct{
	FREQ alFreq;
	int leftChild;
	int rightChild;
	boolean isVisited;
	char *huffmanCode;
}HUFFMAN;

void huffman_main();
void my_error(const char *err_string, int line);
int getFreq(char *str, FREQ **freq, unsigned char *alphaIndex);
void showFreq(FREQ *freq, int alphaCount);
HUFFMAN *initHuffmanTable(FREQ *freq, int alphaCount);
int getMinFreqAlphaIndex(HUFFMAN *huff, int num);
void createHuffmanTree(HUFFMAN *huff, int alphaCount);
void showHuffmanTable(HUFFMAN *huff, int alphaCount);
void createHuffmanCode(HUFFMAN *huff, int rootIndex, int codeIndex, char *code);
void destroyHuffmanTable(HUFFMAN **huffPoint);
char *codingString(char *str, HUFFMAN *huff, unsigned char *alphaIndex);
int getCodingStringLength(HUFFMAN *huff);
char *encodingString(char *codingString, HUFFMAN *huff, int alphaCount, int fileLen);
int getFileLen(int fd);
unsigned char *compression(char *codeString);
char *enCompression(unsigned char *compression, int len);
char *getNumberString(unsigned char tmp);

char *getNumberString(unsigned char tmp)
{
    int i = 7;
    int j = 0;
    char *res;

    res = (char *)calloc(sizeof(char), 9);
    for(j = 0; j < 8; j++)
    {
        res[j] = '0';
    }

    while(tmp != 0)
    {
        if(tmp%2 == 0)
        {
            res[i--] = '0';
        }
        else
        {
            res[i--] = '1';
        }
        tmp /= 2;
    }
    
    return res;
}

char *enCompression(unsigned char *compression, int len)
{
    int i;
    int remainder;
    int bytes;
    char *res;
    char tmp[9] = {0};

    res = (char *)calloc(sizeof(char), len+1);

    //本函数主要处理编码串的首尾部,并将该编码串还原成01串
    bytes = strlen(compression) - 1;
    remainder = compression[0];
    
    for(i = 1; i < bytes; i++)
    {
        strcpy(tmp, getNumberString(compression[i]));
        strcat(res, tmp);
    }
    
    memset(tmp, 0, sizeof(char)*8);
    memcpy(tmp, getNumberString(compression[i]), sizeof(char)*(remainder-1));
    strcat(res, tmp);
    
    return res;
}

unsigned char *compression(char *codeString)
{
    int len;
    int bits;
    int remainder;
    int i;
    int j;
    int k = 0;
    unsigned char *res;
    unsigned char tmp = 0;

    len = strlen(codeString);
    res = (unsigned char*)calloc(sizeof(unsigned char), len+2);
    bits = len/8;
    remainder = len%8;
    
    res[k++] = remainder;
    for(i = 0; i < bits+1; i++)
    {
        for(j = i*8 + 0; j < i*8 + 8; j++)
        {
            if(codeString[j] == '1')
            {
                tmp |= (128>>(j%8));
            }
        }
        res[k++] = tmp;
        tmp = 0;
    }

    return res;
}

int getFileLen(int fd)
{
    int len;

    if(lseek(fd, 0, SEEK_END) == -1)
    {
        my_error("lseek", __LINE__);
    }

    if((len = lseek(fd, 0, SEEK_CUR)) == -1)
    {
        my_error("lseek", __LINE__);
    }

    if((lseek(fd, 0, SEEK_SET)) == -1)
    {
        my_error("lseek", __LINE__);
    }

    return len;
}

char *encodingString(char *codingString, HUFFMAN *huff, int alphaCount, int fileLen)
{
    //将编码后的文件再次解码,从根开始解码,若访问到的结点为叶子结点,则结束一次编码,直至将01串全部解码
	int rootIndex = 2*(alphaCount - 1);
    int i = 0;
	int len = strlen(codingString);
    char *encodestring;

    encodestring = (char*)calloc(sizeof(char), fileLen);

    while(i <= len)
    {
        if(-1 == huff[rootIndex].leftChild)
        {
            strcat(encodestring, &(huff[rootIndex].alFreq.alpha)); 
            rootIndex = 2*(alphaCount - 1);
        }
        else
        {
            rootIndex = ('1' == codingString[i]) 
            ? huff[rootIndex].leftChild : huff[rootIndex].rightChild;
            i++;
        }
    }

    return encodestring;
}

int getCodingStringLength(HUFFMAN *huff)
{
    //得到当前要编码的字符串编码之后的码串长度
	int i;
	int sum = 0;

	for(i = 0; -1 == huff[i].leftChild; i++)
    {
		sum += strlen(huff[i].huffmanCode) * huff[i].alFreq.freq;
	}

	return sum;
}

char *codingString(char *str, HUFFMAN *huff, unsigned char *alphaIndex)
{
    //编码拼接,将输入的字符串以其哈夫曼编码的形式依次拼接起来
	int i;
	char *res;

	res = (char *)calloc(sizeof(char), getCodingStringLength(huff)+1);

	for(i = 0; str[i]; i++)
    {
		strcat(res, huff[alphaIndex[str[i]]].huffmanCode);
	}
	printf("\n");

	return res;
}

void destroyHuffmanTable(HUFFMAN **huffPoint)
{
    //释放哈夫曼表(哈夫曼表内所有在堆里申请的空间)
	HUFFMAN *huff = *huffPoint;
	int i;

	for(i = 0; -1 == huff[i].leftChild; i++)
    {
		free(huff[i].huffmanCode);
	}

	free(huff);
	*huffPoint = NULL;
}

void createHuffmanCode(HUFFMAN *huff, int rootIndex, int codeIndex, char *code)
{
    //创建哈夫曼编码(递归调用)
    
    //先访问左子树,后访问右子树,直至访问到一次叶子结点,当前函数调用结束
    if(-1 == huff[rootIndex].leftChild)
    {
        //结束编码,并将该临时编码数组的值复制给当前叶子结点的结构体的huffmanCode成员
        code[codeIndex] = 0; 
        strcpy(huff[rootIndex].huffmanCode, code);
        return;
    }

	code[codeIndex] = '1';
	createHuffmanCode(huff, huff[rootIndex].leftChild, codeIndex+1, code);
	code[codeIndex] = '0';
	createHuffmanCode(huff, huff[rootIndex].rightChild, codeIndex+1, code);
}

void showHuffmanTable(HUFFMAN *huff, int alphaCount)
{
    //输出哈夫曼编码表
	int i;

	printf("\n%-4s %-4s %-9s %-6s %-6s %-8s %s\n", "下标", "字符", "频度", "左孩子", "右孩子", "访问标志", "哈夫曼编码");
    for(i = 0; i < 2*alphaCount - 1; i++)
    {
        printf("%-4d %-4c %-9d %-6d %-6d %-8d %s\n", i,
               huff[i].alFreq.alpha,
               huff[i].alFreq.freq,
               huff[i].leftChild,
               huff[i].rightChild,
               huff[i].isVisited,
               (huff[i].huffmanCode == NULL ? "无需编码" : huff[i].huffmanCode));
    }
}

void createHuffmanTree(HUFFMAN *huff, int alphaCount)
{
    //创建哈夫曼树
	int leftChildIndex;
	int rightChildIndex;
	int i;
	
    for(i = 0; i < alphaCount-1; i++)
    {
        leftChildIndex = getMinFreqAlphaIndex(huff, alphaCount+i);
        rightChildIndex = getMinFreqAlphaIndex(huff, alphaCount+i);
        //凡是组合得到的结点都用'#'表示,且因为其无需编码,所以其huffmanCode这一项的值为null
        huff[alphaCount+i].alFreq.alpha = '#';
        huff[alphaCount+i].alFreq.freq = huff[leftChildIndex].alFreq.freq + huff[rightChildIndex].alFreq.freq;
        huff[alphaCount+i].leftChild = leftChildIndex;
        huff[alphaCount+i].rightChild = rightChildIndex;
        huff[alphaCount+i].isVisited = FALSE;
        huff[alphaCount+i].huffmanCode = NULL;
    }
}

int getMinFreqAlphaIndex(HUFFMAN *huff, int num)
{
    //得到最小权值的结点的下标
	int minIndex = -1;
	int i;

	for(i = 0; i < num; i++){
		if(huff[i].isVisited == FALSE &&	// 只有没有被访问过的，才有必要比较
			(minIndex == -1 || huff[i].alFreq.freq < huff[minIndex].alFreq.freq)){
			// 对于没有访问过的，如果是第一次访问(minIndex==-1)，则，……
			minIndex = i;
		}
	}

	huff[minIndex].isVisited = TRUE;

	return minIndex;
}

HUFFMAN *initHuffmanTable(FREQ *freq, int alphaCount)
{  
    //初始化哈夫曼树
	int i;
	HUFFMAN *huff;

	huff = (HUFFMAN *)calloc(sizeof(HUFFMAN), 2*alphaCount-1);

    for(i = 0; i < alphaCount; i++)
    {
        huff[i].alFreq.alpha = freq[i].alpha;
        huff[i].alFreq.freq = freq[i].freq;
        huff[i].leftChild = huff[i].rightChild = -1;
        huff[i].isVisited = FALSE;
        huff[i].huffmanCode = (char *)calloc(sizeof(char), alphaCount);
        //经实际验证,每一个结点的最长编码长度为alphaCount-1
    }
 
	return huff;
}

void showFreq(FREQ *freq, int alphaCount)
{  
    //打印字符及其频度
	int i;

	for(i = 0; i < alphaCount; i++){
		printf("[%c]:%d\n", freq[i].alpha, freq[i].freq);
	}
}

int getFreq(char *str, FREQ **freq, unsigned char *alphaIndex)
{  
    //得到输入的字符的个数/频度等
	unsigned char alpha[256] = {0}; //字符数组
	int alphaFreq[256] = {0};   //频度数组,其下标为对应的字符的ascii码
	int alphaCount = 0;         //字符个数,也是该函数的返回值
	FREQ *res = NULL;
	int index;
	int resIndex = 0;

	for(index = 0; str[index]; index++)
    {        
        //如果该字符是第一次出现,则将该字符存入alphaFreq这个数组中
        if(0 == alphaFreq[str[index]])
        { 
            //字符下标数组,将字符本身及字符在字符数组中的位置对应起来,其值即为位置
            alphaIndex[str[index]] = alphaCount;
	        alpha[alphaCount++] = str[index];   //将初次出现的字符顺次存入alpha数组
        }
        alphaFreq[str[index]]++;
	}

	res = (FREQ *)calloc(sizeof(FREQ), alphaCount);     //将出现的字符及其频度存入FREQ结构体数组中
	for(index = 0; index < alphaCount; index++)
    {
		res[resIndex].alpha = alpha[index];
		res[resIndex++].freq = alphaFreq[alpha[index]];
	}

	*freq = res;

	return alphaCount;
}

void huffman_main()
{
    char tmpName[256] = {0};
    char fileName[256] = {0};
    char encodeFileName[256] = {0};
    int fileFd;     //要打开的文件描述符
    int encodeFd;
    int fileLen;    //该文件大小
    char *read_buf;
    int ret;        //read函数读到的字节数

	unsigned char alphaIndex[256] = {0};
	FREQ *freq = NULL;  //存放字符频度表
	int alphaCount;     //输入的字符的个数
	HUFFMAN *huff;  
	char *code;
	char *codeString;
    unsigned char *compressionCode;
    char *encodestring;
    char *enCompressionCode;
    int i;

    //先输入文件名,然后将文件内的内容都读出来(其中包含得到文件长度等参数)
    printf("请输入要压缩的文件名(格式:xxx.xxx,含文件扩展名)\n");
    scanf("%s", fileName);


    //先以只读的方式打开该文件
    if((fileFd = open(fileName, O_RDONLY)) == -1)
    {
        printf("未找到该文件!\n");
        my_error("open", __LINE__);
    }

    //再将得到该文件的大小
    fileLen = getFileLen(fileFd);
    read_buf = (char *)malloc(sizeof(char)*fileLen);
    
    //然后将文件内的内容读到指定的buf里
    if((ret = read(fileFd, read_buf, fileLen)) < 0)
    {
        my_error("read", __LINE__);
    }
    close(fileFd);
    //将文件内容进行哈夫曼编码(显示哈夫曼编码表,及各字符所对应的编码串)
    alphaCount = getFreq(read_buf, &freq, alphaIndex);
	huff = initHuffmanTable(freq, alphaCount);
	createHuffmanTree(huff, alphaCount);
	code = (char *)calloc(sizeof(char), alphaCount);
	createHuffmanCode(huff, 2*(alphaCount-1), 0, code);

	codeString = codingString(read_buf, huff, alphaIndex);
	showHuffmanTable(huff, alphaCount);
    printf("压缩成功!\n");

    //将哈夫曼编码后的文件压缩存储
    compressionCode = compression(codeString);
   
    //再将编码串写进一个新的文件里
    strcpy(encodeFileName, fileName);
    strcat(encodeFileName, ".huffman");

    if((encodeFd = open(encodeFileName, O_RDWR | O_CREAT, 0664)) == -1)
    {
        my_error("read", __LINE__);
    }
    
    if(write(encodeFd, compressionCode, strlen(compressionCode)) != strlen(compressionCode))
    {
        my_error("write", __LINE__);
    }
    close(encodeFd);
   
    sleep(1);
    system("clear");
    printf("请问是否需要解压缩(是按1,否按0):");
    scanf("%d", &i);

    if(i)
    {
        //接下来要将编码串还原成01串
        enCompressionCode = enCompression(compressionCode, strlen(codeString));

        //再将编码串还原,并写进一个新的文件,比较还原后的字符串和从起始文件中读出的字符串是否完全相同
        encodestring = encodingString(codeString, huff, alphaCount, fileLen);
        strcpy(encodeFileName, fileName);
        strcat(encodeFileName, ".restore");
        if((encodeFd = open(encodeFileName, O_RDWR | O_CREAT, 0664)) == -1)
        {
            my_error("read", __LINE__);
        }

        if(write(encodeFd, encodestring, strlen(encodestring)) != strlen(encodestring))
        {
            my_error("write", __LINE__);
        }
        close(encodeFd);
        if(strcmp(read_buf, encodestring) == 0)
        {
            printf("解压缩成功!\n");
        }
    }

	//最后释放哈夫曼编码过程中在堆内所申请的全部空间

    free(code);
    destroyHuffmanTable(&huff);
    free(freq);
    free(codeString);
    free(compressionCode);
    free(encodestring);
    free(enCompressionCode);
    exit(0);
}

void my_error(const char *err_string, int line)
{
    fprintf(stderr, "line:%d ", line);
    perror(err_string);
    exit(1);
}

/*
abacacacaadaabbebbfaabd
1011001100110011100011101010000101010000011010001
*/
int main(int argc, char *argv[])
{
    huffman_main();
}

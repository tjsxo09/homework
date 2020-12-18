#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <unistd.h>

#define ROW 512
#define COL 512

void error_handling(char* message);
int RLUnComp(char *);

unsigned char image[ROW*COL*3];
unsigned char imagebuffer[ROW*COL*3];
unsigned char decodeimage[ROW*COL*3];

int main(void)
{
	FILE *src = fopen("./statue.bmp", "rb");
	FILE *dsc = fopen("./statuecp.bmp", "wb");

	char header[2048];
    int i,j;

	fread(header, 1, 54, src);
	fread(image, 3, ROW*COL, src);

	for(i=0; i<ROW; i++){
        for(j = 0; j<COL; j++){
            printf("%02X ", image[i*COL+j]);
        }
	}

	fwrite(header, 1, 54, dsc);
	fwrite(image, 3, ROW*COL,dsc);

	return 0;
}

void error_handling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

void RLEComp(unsigned char *data)
{
    int i,j =0;
    int cnt=0;
    unsigned char count =0;
    unsigned char end = '/';
    unsigned char code;

    for(i=0; i<ROW; i++){
        for(j = 0; j<COL; j++){
                if(count == 0)
                {
                    code = data[i*COL+j];
                }
                else if(code != data[i*COL+j]){
                    imagebuffer[cnt++] = code;
                    imagebuffer[cnt++] = count;

                    count = 0;
                    code = data[i*COL+j];
                }
                count++;

                if(count == 255){
                    imagebuffer[cnt++] = code;
                    imagebuffer[cnt++] = count;
                    count = 0;
                }
        }
	}
	imagebuffer[cnt++] = code;
    imagebuffer[cnt++] = count;

    //imagebuffer[cnt++] = end;
    //imagebuffer[cnt++] = end;
    //imagebuffer[cnt++] = end;
}

void RLEdecode(unsigned char *data)
{
    int cnt =0;
    int data_size=0;
    int end_count=0;
    unsigned char code;
    unsigned char end = '/';

    data_size = sizeof(data);

    for(i=0; i<ROW; i++){
        for(j = 0; j<COL; j++){
            printf("%02X ", image[i*COL+j]);
        }
	}
}


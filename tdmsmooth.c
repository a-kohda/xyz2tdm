#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX_RNUM 100  // Input file 1行あたりの最大列数
#define MAX_CNUM 1000 // Input file 1行あたりの最大文字数

int main(){

	char line[MAX_CNUM];
	float val[MAX_RNUM];

	float z[100][100];

	int lastx, lasty;

	int k;

	char line1st[MAX_CNUM];
	char line2nd[MAX_CNUM];
	char linehead[100][100];

	// 3行目から読む
	fgets(line, 1000, stdin);
	for(k=0;k<1000;k++){line1st[k]=line[k];}
	fgets(line, 1000, stdin);
	for(k=0;k<1000;k++){line2nd[k]=line[k];}

	int lineid =0;
	while(fgets(line, 1000, stdin)!= NULL){
		int i;
		char* s = line;
		char* inis;
		s +=13;
		lineid++;
		for(k=0;k<100;k++){linehead[lineid][k]=line[k];}

		for(i=0;i<MAX_RNUM;i++){
			int xid = i+1;
			int yid = lineid;
			float tempz;
			inis = s;
			tempz = strtof(s,&s); // 正常に読み取れたら
											// 読み込んだ位置までポインタが移動されてるはず。
			z[xid][yid] = tempz;

			if(s-inis <= 0) break; // 読み取りに失敗したらポインタ移動がおこらない
			lastx = xid;
			//printf("(%d,%d)\t%#6g\n",xid,yid, z[xid][yid]);
		}
		//printf("lastx is %d\n",lastx);
	}
	lasty=lineid;
	//printf("lasty is %d\n",lasty);
	
	// 境界処理
	// 左上
	z[0][0] = 2 * z[1][1] - z[2][2];

	// 左下
	z[0][lasty+1] = 2 * z[1][lasty] - z[2][lasty-1];

	// 右上
	z[lastx+1][0] = 2 * z[lastx][1] - z[lastx-1][2];

	// 右下
	z[lastx+1][lasty+1] = 2 * z[lastx][lasty] - z[lastx-1][lasty-1];

	int x,y;

	// 上下
	for(x=1;x<=lastx;x++){
		z[x][0] = 2 * z[x][1] - z[x][2];
		z[x][lasty+1] = 2 * z[x][lasty] - z[x][lasty-1];
	}

	// 左右
	for(y=1;y<=lasty;y++){
		z[0][y] = 2 * z[1][y] - z[2][y];
		z[lastx+1][y] = 2 * z[lastx][y] - z[lastx-1][y];
	}

	// 確認
	/*
	for(y=0;y<lasty+2;y++){
		for(x=0;x<lastx+2;x++){
			printf("%#6g ",z[x][y]);
		}
		printf("\n");
	}
	*/

	float newz[100][100];
	for(y=1;y<=lasty;y++){
		for(x=1;x<=lastx;x++){
			newz[x][y] = ( z[x][y] 
			           + z[x+1][y] + z[x][y+1] + z[x-1][y] + z[x][y-1] 
			           + z[x+1][y+1] + z[x+1][y-1] + z[x-1][y+1] + z[x-1][y-1] )/9.0;
		}
	}

	// 確認
	/*
	for(y=0;y<lasty+2;y++){
		for(x=0;x<lastx+2;x++){
			printf("%#6g ",newz[x][y]);
		}
		printf("\n");
	}

	printf("%s",line1st);
	printf("%s",line2nd);

	for(y=1;y<=lasty;y++){printf("%.13s\n",linehead[y]);}
	*/

	// 最終出力
	printf("%s",line1st);
	printf("%s",line2nd);
	for(y=1;y<=lasty;y++){
		printf("%.13s",linehead[y]);
		for(x=1;x<=lastx;x++){ printf("%#6g ",newz[x][y]); }
		printf("\n");
	}

	return 0;
}

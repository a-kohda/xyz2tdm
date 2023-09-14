#include<stdio.h>
#include<stdlib.h>
#include <math.h>
//#include<errno.h>

#define MAX_RNUM 10   // Input file 1行あたりの最大列数
#define MAX_CNUM 1000 // Input file 1行あたりの最大文字数

// x, y, z が記述されてる列番号を引数にする
int main(int argc, char *argv[]){
	// settings
	int xl = 0; // Input fileの何列目が x か
	int yl = 1; // コマンドライン引数がない場合にこの値を使う
	int zl = 2;
	float dx = 0.1; // 同じxとして扱う範囲
	float dy = 0.1;

	//printf("%d\n",argc);
	if(argc==4){
	xl = atoi(argv[1]) -1; // 引数入力は1始まりで指定して、
	yl = atoi(argv[2]) -1; // ここで0始まりに変換する
	zl = atoi(argv[3]) -1;
	//printf("Using Row for x y z : %d %d %d\n", xl, yl, zl);
	}


	char line[MAX_CNUM];
	float val[MAX_RNUM];
	float x, y, z;

	float qx[1000]; // 量子化されたx
	float qy[1000];
	float qz[1000][1000];

	//float x[1000], y[1000];
	int xnum = 0; // 使用済み x idx 数
	int ynum = 0;

	int xid, yid;

	short sortx[100], sorty[100]; // qx, qyを小さい順に並べた時にn番目のid 

	while(fgets(line, 1000, stdin)!= NULL){

		//printf("%s\n",line);
		//param[0]=-1;
		//param[1]=-1;
		//param[2]=-1;

		//int num = sscanf(line, " %*f %f %f %f\n", &x, &y, &z);
		int i;
		char* s = line;
		char* inis;
		for(i=0;i<MAX_RNUM;i++){
			inis = s;
			//sscanf(line +i, "%f\n",&val[i]);
			val[i] = strtof(s,&s); // 正常に読み取れたら
											// 読み込んだ位置までポインタが移動されてるはず。
			//printf("%f %d\n", val[i], s-inis);
			if(s-inis <= 0) break; // 読み取りに失敗したらポインタ移動がおこらない
			//line ++; 
			
		}
		if (i <3) continue; // 読み込んだ列数が1以下なら読み飛ばす
		x = val[xl];
		y = val[yl];
		z = val[zl];
		
		//if(num < 3) continue; 
		// sscanfの返り値は代入された数値の個数になる。(失敗した場合は3以外になる)
		
		
		for(i=0;i<xnum+1;i++){
			if(xnum==0){
				qx[xnum] = x;
				xid =i;
				xnum++;
				 break;
			}
			if( fabs(qx[i]-x) < 0.001 ){
				xid =i;
				break;
			} else if(i == xnum-1){
				qx[xnum] = x;
				xnum++;
				xid=i;
			}
		}
		//xid = i-1;

		for(i=0;i<ynum+1;i++){
			if(ynum==0){
				qy[ynum] = y;
				yid =i;
				ynum++;
				 break;
			}
			if( fabs(qy[i]-y) < 0.001 ){
				yid =i;
				break;
			} else if(i == ynum-1){
				qy[ynum] = y;
				ynum++;
				yid=i;
			}
		}

		if(0){ // 途中経過を表示したければ1
			printf("%f %f %f x,yid: %d %d\n", x, y, z, xid,yid );	
		}	
		qz[xid][yid]=z;

	}
	
	int i,j,k;
	for(i=0;i<xnum;i++){
		//printf("x(%d)=%f ",i,qx[i]);
		k=0;
		for(j=0;j<xnum;j++){
			if(i>0&& (qx[sortx[i-1]] > qx[j] || sortx[i-1]==j)) continue;
			if(k==0) { sortx[i] =j; k++;}
			//if(i==j) continue;
			if(qx[sortx[i]] > qx[j]) sortx[i] =j;
		}
		//printf("sort %d\n", sortx[i]);
	}
	for(i=0;i<ynum;i++){
		//printf("y(%d)=%f ",i,qy[i]);
		k=0;
		for(j=0;j<ynum;j++){
			if(i>0&& (qy[sorty[i-1]] > qy[j] || sorty[i-1]==j)) continue;
			if(k==0) { sorty[i] =j; k++;}
			//if(i==j) continue;
			if(qy[sorty[i]] > qy[j]) sorty[i] =j;
		}
		//printf("sorted %d %f\n", i, qy[sorty[i]]);
	}


	// 最終出力

	printf("READ MESH\n");
	printf("FOR       X= ");
	for(i=0;i<xnum;i++){
    printf("%#6g ",qx[sortx[i]]);
  }
	printf("\n");
	for(i=0;i<ynum;i++){
		printf("Y=%#6g Z= ",qy[sorty[i]]);

		for(j=0;j<xnum;j++){
			printf("%#6g ",qz[sortx[j]][sorty[i]]);
		}
		printf("\n");
	}


	return 0;
}

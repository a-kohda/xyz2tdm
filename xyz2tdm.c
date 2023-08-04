#include<stdio.h>
#include<stdlib.h>
#include <math.h>
//#include<errno.h>

#define MAX_RNUM 10   // 1$B9T$"$?$j$N:GBgNs?t(B
#define MAX_CNUM 1000 // 1$B9T$"$?$j$N:GBgJ8;z?t(B

// x, y, z $B$,5-=R$5$l$F$kNsHV9f$r0z?t$K$9$k(B
int main(int argc, char *argv[]){
	// settings
	int xl = 1; // Input file$B$N2?NsL\$,(B x $B$+(B
	int yl = 2;
	int zl = 3;
	float dx = 0.1; // $BF1$8(Bx$B$H$7$F07$&HO0O(B
	float dy = 0.1;

	//int xl = atoi(argv[1]);
	//int yl = atoi(argv[2]);
	//int zl = atoi(argv[3]);
	//printf("Using Row for x y z : %d %d %d\n", xl, yl, zl);

	char line[MAX_CNUM];
	float val[MAX_RNUM];
	float x, y, z;

	float qx[1000]; // $BNL;R2=$5$l$?(Bx
	float qy[1000];
	float qz[1000][1000];

	//float x[1000], y[1000];
	int xnum = 0; // $B;HMQ:Q$_(B x idx $B?t(B
	int ynum = 0;

	int xid, yid;

	short sortx[100], sorty[100]; // qx, qy$B$r>.$5$$=g$KJB$Y$?;~$K(Bn$BHVL\$N(Bid 

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
			val[i] = strtof(s,&s); // $B@5>o$KFI$_<h$l$?$i(B
											// $BFI$_9~$s$@0LCV$^$G%]%$%s%?$,0\F0$5$l$F$k$O$:!#(B
			//printf("%f %d\n", val[i], s-inis);
			if(s-inis <= 0) break; // $BFI$_<h$j$K<:GT$7$?$i%]%$%s%?0\F0$,$*$3$i$J$$(B
			//line ++; 
			
		}
		if (i <3) continue; // $BFI$_9~$s$@Ns?t$,(B1$B0J2<$J$iFI$_Ht$P$9(B
		x = val[xl];
		y = val[yl];
		z = val[zl];
		
		//if(num < 3) continue; 
		// sscanf$B$NJV$jCM$OBeF~$5$l$??tCM$N8D?t$K$J$k!#(B($B<:GT$7$?>l9g$O(B3$B0J30$K$J$k(B)
		
		
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

		if(0){ // $BESCf7P2a$rI=<($7$?$1$l$P(B1
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


	// $B:G=*=PNO(B

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

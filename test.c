#include <pbc.h>
#include <stdio.h>
#include<string.h>
#include <pbc_test.h>
#include<time.h>



int main(int argc, char **argv) {
	pairing_t pairing;

	pbc_demo_pairing_init(pairing, argc, argv);
	
	
	double th1, th2, thh1, thh2, tp1, tp2, tpp1, tpp2, tw1, tw2,tm1, tm2;
	
	element_t x, h;
	element_t P, H;
	element_t Q;
	
	
	element_init_Zr(x, pairing);
	element_init_Zr(h, pairing);
	element_init_G1(P, pairing);
	element_init_G1(H, pairing);
	element_init_GT(Q, pairing);
	
	th1 = pbc_get_time();
	element_from_hash(P, "message", 7);
	th2 = pbc_get_time();
	/*hash*/
	thh1 = pbc_get_time();
	element_from_hash(x, "message", 7);
	thh2 = pbc_get_time();
	
	element_random(x);
	element_random(P);
	
	tp1 = pbc_get_time();
	element_mul_zn(H, P, x);
	tp2 = pbc_get_time();
	
	//printf("break\n");
	

	tw1 = pbc_get_time();
	pairing_apply(Q, P, H, pairing);
	tw2 = pbc_get_time();
	/*pairing*/
	

	
	tpp1 = pbc_get_time();
	element_mul(Q,Q,Q);
	tpp2 = pbc_get_time();
	/*p2p*/
	
	
	
	
	tm1 = pbc_get_time();
	element_pow_zn(H, P, x);
	tm2 = pbc_get_time();
	/*expon*/
	
	printf("%f\t%f\t%f\n%f\n", th2-th1,  tp2-tp1, tw2-tw1, tm2-tm1);
	/*H2G1, H2Z, point mul zq, pairing, expon,P2P*/
	//H2Z\P2P are negligible
	
	FILE *fp;
	fp=fopen("test_data.txt", "a");
	
	fprintf(fp, "%f\t%f\t%f\n%f\n", th2-th1, tp2-tp1, tw2-tw1,tm2-tm1);
	fclose(fp);
	
	element_clear(x);
	element_clear(P);
	element_clear(H);

	pairing_clear(pairing);

 	return 0;
}

// Ben Boldt
// December 2009
// http://www.d.umn.edu/~bold0070/
// https://benboldtumd.github.io/

#include <stdio.h>
#include <iostream>
using namespace std;

	int temp = 0;

	bool t[12] = {1,0,0,0,1,0,0,1,1,0,1,1}; // Original people, all facing the same direction, away from the rope.
	bool l[12] = {1,1,1,0,1,0,0,1,0,1,1,0};
	bool b[12] = {1,1,0,1,1,0,0,0,1,1,0,0};	// top and bottom: tooth pointing down = 1.
	bool r[12] = {1,1,1,1,0,1,0,0,0,0,1,1}; // left and right: top tooth pointing right, bottom tooth pointing left = 1.

	int turn = 0; // This is a bitfield representing which people are turned backwards.

	bool t2[12]; // These are the new people based on the turn bitfield.
	bool l2[12];
	bool b2[12];
	bool r2[12];
				
	bool space0[12]; // These define which person can possibly even fit into each of the 12 spaces, based on edges of raft.
	bool space1[12];
	bool space2[12];
	bool space3[12];
	bool space4[12];
	bool space5[12];
	bool space6[12];
	bool space7[12];
	bool space8[12];
	bool space9[12];
	bool space10[12];
	bool space11[12];
	
	char turnvisual[12];
		
int main () {
cout << "Raging Rapids Solver 2.0\n";
cout << "Ben Boldt\n";
cout << "12/21/2009\n\n";

cout << "People are identified as follows, facing toward you:\n";
cout << "Person ID         0    1    2    3    4    5    6    7    8    9    10   11\n";
cout << "Top Tooth         in   out  out  out  in   out  out  in   in   out  in   in\n";
cout << "Left Top Tooth    in   in   in   out  in   out  out  in   out  in   in   out\n";
cout << "Bottom Tooth      out  out  in   out  out  in   in   in   out  out  in   in\n";
cout << "Right Top Tooth   out  out  out  out  in   out  in   in   in   in   out  out\n\n";

cout << "Place people in the following order:\n\n";

cout << "   ROPE\n";
cout << "a   b   c\n";
cout << "d   e   f\n";
cout << "g   h   i\n";
cout << "j   k   l\n\n";

cout << "People without a ' look away from the rope, people with a ' look toward it.\n\n";

cout << "a\tb\tc\td\te\tf\tg\th\ti\tj\tk\tl\n";

long int count = 0;
for (int z=0; z < 4096; z++) {
	turn = z;
// Stores prime symbols in an array based on int turn.
	temp = 1;
	for(int y=0; y<12; y++) {
		if (turn & temp) turnvisual[y]='\'';
		else turnvisual[y]=' ';
		temp *= 2;
	}
	
// TURN PEOPLE BASED ON int turn.  Transfer t[] to t2[], l[] to l2[], etc.
	temp = 1;
	for (int i=0; i<12; i++) {
		if (turn & temp) {
			t2[i] = !b[i];
			l2[i] = r[i];
			b2[i] = !t[i];
			r2[i] = l[i];
		}
		else {
			t2[i] = t[i];
			l2[i] = l[i];
			b2[i] = b[i];
			r2[i] = r[i];
		}
		temp*=2;
	}

// COMPUTE bool space0[], space1[], etc, for each piece to see if they fit in each space.
	for (int i=0; i<12; i++) {
		if (!t2[i] && !l2[i]) space0[i] = 1;
		else space0[i] = 0;

		if (!t2[i]) space1[i] = 1;
		else space1[i] = 0;

		if (!t2[i] && r2[i]) space2[i] = 1;
		else space2[i] = 0;

		if (!l2[i]) space3[i] = 1;
		else space3[i] = 0;

		space4[i] = 1;

		if (!r2[i]) space5[i] = 1;
		else space5[i] = 0;

		if (!l2[i]) space6[i] = 1;
		else space6[i] = 0;

		space7[i] = 1;
		
		if (!r2[i]) space8[i] = 1;
		else space8[i] = 0;

		if (l2[i] && !b2[i]) space9[i] = 1;
		else space9[i] = 0;

		if (!b2[i]) space10[i] = 1;
		else space10[i] = 0;

		if (!b2[i] && !r2[i]) space11[i] = 1;
		else space11[i] = 0;
	}
	
	for (int a=0; a<12; a++) { // space 0
		if (space0[a]) {
	for (int b=0; b<12; b++) { // space 1
		if (b!=a && space1[b] && l2[b] == r2[a]) {
	for (int c=0; c<12; c++) { // space 2
		if (c!=a && c!=b && space2[c] && l2[c] == r2[b]) {
	for (int d=0; d<12; d++) { // space 3
		if (d!=a && d!=b && d!=c && space3[d] && t2[d] == b2[a]) {
	for (int e=0; e<12; e++) { // space 4
		if (e!=a && e!=b && e!=c && e!=d && space4[e] && t2[e] == b2[b] && l2[e] == r2[d]) {
	for (int f=0; f<12; f++) { // space 5
		if (f!=a && f!=b && f!=c && f!=d && f!=e && space5[f] && t2[f] == b2[c] && l2[f] == r2[e]) {
	for (int g=0; g<12; g++) { // space 6
		if (g!=a && g!=b && g!=c && g!=d && g!=e && g!=f && space6[g] && t2[g] == b2[d]) {
	for (int h=0; h<12; h++) { // space 7
		if (h!=a && h!=b && h!=c && h!=d && h!=e && h!=f && h!=g && space7[h] && t2[h] == b2[e] && l2[h] == r2[g]) {
	for (int i=0; i<12; i++) { // space 8
		if (i!=a && i!=b && i!=c && i!=d && i!=e && i!=f && i!=g && i!=h && space8[i] && t2[i] == b2[f] && l2[i] == r2[h]) {
	for (int j=0; j<12; j++) { // space 9
		if (j!=a && j!=b && j!=c && j!=d && j!=e && j!=f && j!=g && j!=h && j!=i && space9[j] && t2[j] == b2[g]) {
	for (int k=0; k<12; k++) { // space 10
		if (k!=a && k!=b && k!=c && k!=d && k!=e && k!=f && k!=g && k!=h && k!=i && k!=j && space10[k] && t2[k] == b2[h] && l2[k] == r2[j]) {
	for (int l=0; l<12; l++) { // space 11
		if (l!=a && l!=b && l!=c && l!=d && l!=e && l!=f && l!=g && l!=h && l!=i && l!=j && l!=k && space11[l] && t2[l] == b2[i] && l2[l] == r2[k]) {
	count++;
	cout << a << turnvisual[a] <<"\t" << b << turnvisual[b] << "\t"  << c << turnvisual[c] << "\t"  << d << turnvisual[d] << "\t"  << e << turnvisual[e] << "\t"  << f << turnvisual[f] << "\t"  << g << turnvisual[g] << "\t"  << h << turnvisual[h] << "\t"  << i << turnvisual[i] << "\t"  << j << turnvisual[j] << "\t"  << k << turnvisual[k] << "\t"  << l << turnvisual[l] << "\t# " << count << endl;
		}
	}
		}
	}
		}
	}
		}
	}
		}
	}
		}
	}
		}
	}
		}
	}
		}
	}
		}
	}
		}
	}
		}
	}
}
	cout << "\n" << count << " total combinations out of 1,961,990,553,600 possible combinations.\n\nRandom chance of 1 : " << (1961990.553600 / (count*1.0) * 1000000);

    return 0;
}

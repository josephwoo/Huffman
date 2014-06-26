#include <fstream>
#include "Huffmantree.h"
using namespace std;


int asc[128] = {0} ;
char c[100] ;
string s ;

void getfile(){
	int i , j ;
	ifstream inf ;
	inf.open("input.txt" , ios::in) ;
	if(!inf)
		cerr<<"In Open Error!"<<endl;
	while(!inf.eof()){
		inf.getline(c , 100 ) ;
		for(i = 0 ; c[i]!='\0' ; i ++){
			j = c[i] ;
			asc[j] ++ ;
		}
	}
	inf.close() ;
}


int main(int argc, char const *argv[])
{
	getfile() ;

	cout<<"Code:" << endl ;
	HuffmanTree<int> Htree(asc , 128) ;

	cout<<'\n'<<"Print:" <<endl ;
	string code ;
	Htree.print(Htree.root, code ) ;

	return 0;
}

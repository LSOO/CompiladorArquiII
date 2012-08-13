#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> extractwords(string line){

  vector<string> words;
  string pal;
  
  for(int i=0;i<line.size();i++){
    if(line.at(i)==',' or line.at(i)==' ' or line.at(i)==';'){
      words.push_back(pal);
      pal.clear();
    }else{
      pal.push_back(line[i]);
    }
  }
  return words;

}

void bopcode(string line){
  
  fstream top;
  string auxline;
  string opcode;
  
  top.open("tableOp");

  for(int i=0;i<line.size();i++){
    if(isdigit(line[i])){
      line[i]='*';
      if(isdigit(line[i+1])){
	line.erase(i+1);
	i--;
      }
    }
  }

  for(int i=0;i<line.size();i++){
    if(line[i]==' '){
      line[i]=',';
    }
  }

  while(! top.eof()){
    top >> auxline;
    if(auxline == line){
      top >> opcode;
    }else{
      top >> auxline;
    }
  }

  top.close();

  cout << opcode;
  //return opcode;
}

void bregs(string line){

  string regs, r1, r2, br1, br2;
  string line2, auxreg;
  fstream treg;

  treg.open("tableReg");

  for(int i=0;i<line.size();i++){
    if(line[i]=='R'){
      r1.push_back(line[i]);
      r1.push_back(line[i+1]);
      if(isdigit(line[i+2])){
	r1.push_back(line[i+2]);
      }
      line[i]='P';
      i=line.size()+1;
    }
  }

  for(int i=0;i<line.size();i++){
    if(line[i]=='R'){
      r2.push_back(line[i]);
      r2.push_back(line[i+1]);
      if(isdigit(line[i+2])){
	r2.push_back(line[i+2]);
      }
      i=line.size()+1;
    }
  }

  while(! treg.eof()){
    treg >> auxreg;
    if(auxreg == r1){
      treg >> br1;
    }else{
      if(auxreg == r2){
	treg >> br2;
      }else{
	treg >> auxreg;
      }
    }
  }

  regs.append(br1);
  regs.append(br2);

  cout << regs;
  //return regs;
}

void bcons(string line){

  string cons="0", bcons="00000000", auxcons;
  fstream tcons;
  
  tcons.open("tableCons");

  for(int i=1;i<line.size();i++){
    if(isdigit(line[i]) and line[i-1]!='R'){
      cons.erase(0);
      cons.push_back(line[i]);
      if(isdigit(line[i+1])){
	cons.push_back(line[i+1]);
	if(isdigit(line[i+2])){
	  cons.push_back(line[i+2]);	  
	}
      }
    }
  }

  while(!tcons.eof()){
    tcons >> auxcons;
    if(auxcons == cons){
      tcons >> bcons;
    }else{
      tcons >> auxcons;
    }
  }

  cout << bcons ;
  //return bcons;

}

void printwords(vector< vector<string> > v){
  for(int i=0;i<v.size();i++){
    for(int j=0;j<v[i].size();j++){
      cout << v[i][j] << endl;
    }
  }
}

int main(){

  vector<string> vwords;
  vector< vector<string> > vtext;
  string line;
  fstream tex;

  tex.open("code");
  while (! tex.eof() ){
    getline (tex,line);
    //bopcode(line);
    //bregs(line);
    //bcons(line);
    //cout << endl;
    vwords = extractwords(line);
    vtext.push_back(vwords);
  }

  printwords(vtext);

  tex.close();

  return 0;
}

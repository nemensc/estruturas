#include <iostream>
#include <lapacke.h>

#define NNODES 4
#define NELE 3

void stiffness(double k, double Ke[2][2]);
void global(int e, double ke[2][2], int nnodes, int nEle, int MM[2][NELE], double k[][NNODES]);

int main(){



  int nnodes=4;
  //std::cin >> nnodes;

  double k=10.0;
  //std::cin >> k;

  int nEle=3;
  //std::cin >> nEle;

  int MM[2][NELE];
  MM[0][0] = 0;
  MM[0][1] = 2;
  MM[0][2] = 3;
  MM[1][0] = 2;
  MM[1][1] = 3;
  MM[1][2] = 1;


  double kele[2][2];

  stiffness(k, kele);
  for (size_t i = 0; i < 2; i++) {
    for (size_t j = 0; j < 2; j++) {
      std::cout << kele[i][j] << " ";
    }
    std::cout << std::endl;
  }

  double kglobal[NNODES][NNODES];
  for (size_t i = 0; i < nnodes; i++) {
    for (size_t j = 0; j < nnodes; j++) {
      kglobal[i][j] = 0.0;
    }
  }


  for (size_t e = 0; e < nEle; e++) {
    global(e, kele, nnodes, nEle, MM, kglobal );
  }

  for (size_t i = 0; i < nnodes; i++) {
    for (size_t j = 0; j < nnodes; j++) {
      std::cout << kglobal[i][j] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}

void stiffness(double k, double Ke[2][2]){
  Ke[0][0] = k;
  Ke[0][1] = -k;
  Ke[1][0] = -k;
  Ke[1][1] = k;

}

void global(int e, double ke[2][2],int nnodes,int nEle, int MM[2][NELE], double k[][NNODES] ){

    for (size_t i = 0; i < 2; i++) {
      int pos1 = MM[i][e];
      for (size_t j = 0; j < 2; j++) {
        int pos2 = MM[j][e];
        std::cout << pos1 << " " << pos2 << std::endl;
        k[pos1][pos2] += ke[i][j];
      }
    }

  }

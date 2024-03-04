// Solved using the STL generic vector container class 


#include <iostream>
#include <vector>
#include <cmath> // for pow function

using namespace std;

typedef vector <double> Dvector;
typedef vector <Dvector> Dmatrix;

// Prototypes (variable names included, but not needed)

Dmatrix GetA(); 
// gets the matrix A from the user and returns it

Dvector Getb(const int &siz); 
// gets the vector b from the user and returns it

void Display(const Dvector &xvect); 
// displays the contents of vector xvect

void Display(const Dmatrix &Amat); 
// displays the contents of matrix Amat (Note: Display function is overloaded)

Dvector Solvex(const Dmatrix &Amat, const Dvector &bvect);
// Solves for systems of linear equations in the form Ax=b using cramer's rule 

double Det(const Dmatrix &Amat);
// returns the Determinant of matrix Amat using a recursive algorithm
// base case is 2x2 matrix 

Dmatrix Replace(Dmatrix Rmat, const int col, const Dvector &bvect);
// Replaces the column 'col' in Rmat with bvect and returns Rmat

Dmatrix Minor(Dmatrix Amat, int col);
// Gets the Minor matrix of Amat by crossing out the first row and 
// column 'col' then returns that smaller matrix


//-------------------------------------------
int main(){

Dmatrix A;     
Dvector b,x;

A=GetA();
Display(A);
b=Getb(A.size());
Display(b); //temporary to print out b matrix
x=Solvex(A,b);
Display(x);

return(0);
}
//-------------------------------------------

Dmatrix GetA(){
    int key;
    int tempnum;
    Dmatrix mainvec;
    Dvector row;
    cin>>key;
    for (int x = 0; x < key; x++){
        row = {};
        for (int y = 0; y < key; y++){
            cin>>tempnum;
            row.push_back(tempnum);
            tempnum = 0;
        }
        mainvec.push_back(row);
    }
    return mainvec;
}


void Display(const Dmatrix &Amat){
    int size = Amat.size();
    for (int x = 0; x < size; x++){
        for (int y = 0; y < size; y++){
            cout<<Amat[x][y]<<"   ";
        }
        cout<<endl;
    }
}


void Display(const Dvector &xvect){
    int size = xvect.size();
    for (int x = 0; x < size; x++){
        cout<<xvect[x]<<endl;
    }
}

Dvector Getb(const int &siz){
    int tempnum;
    Dvector mainvec;
    for (int x = 0; x < siz; x++){
        cin>>tempnum;
        mainvec.push_back(tempnum);
    }
    return mainvec;
}


Dvector Solvex(const Dmatrix &Amat, const Dvector &bvect){
    Dvector answervec;
    double denominator = Det(Amat);
    for (int x = 0; x < Amat.size(); x++){
        answervec.push_back((Det(Replace(Amat, x, bvect)))/denominator);
    }
    return answervec;
}


Dmatrix Replace(Dmatrix Rmat, const int col, const Dvector &bvect){
    for (int x = 0; x < Rmat.size(); x++){
        Rmat[x][col] = bvect[x];
    }
    return Rmat;
}


double Det(const Dmatrix &Amat){
    int posorneg;
    int matrixsize = Amat.size();
    double answer;
    Dmatrix minormatrix;
    double detofminor;
    if (matrixsize==2){
        return (Amat[0][0]*Amat[1][1])-(Amat[0][1]*Amat[1][0]);
    }
    else{
        for (int x = 0; x < matrixsize; x++){
            posorneg = pow(-1,x+2);
            minormatrix = Minor(Amat,x);
            detofminor = Det(minormatrix);
            answer = answer + (posorneg*Amat[1][x]*detofminor);
        }
    }
    return answer;
}

Dmatrix Minor(Dmatrix Amat, int col){
    int isize = Amat.size();
    Amat.erase(Amat.begin() + 1);
    int fsize = Amat.size();
    for (int x = 0; x < fsize; x++){
        Amat[x].erase(Amat[x].begin() + col);
    }
    return Amat;
}

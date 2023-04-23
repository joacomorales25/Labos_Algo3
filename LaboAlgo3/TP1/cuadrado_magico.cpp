#include <iostream>
#include <vector>

using namespace std;

vector<int> sumaFila;
vector<int> sumaCol;
vector<int> sumaDiag;
vector<int> num;
int tam;
int cteMagica;
bool poda(vector<vector<int>>& m, int i, int j, int k){
    
    // chequeo el valor de la fila en la que estoy parado
    if(sumaFila[i] + k > cteMagica){
        return false;
    }
    // chequeo el valor de la columna en la que estoy parado
    if(sumaCol[j] + k > cteMagica){
        return false;
    }// chequeo el valor de la diagonal en la que estoy parado
    if(i == j && sumaDiag[0] + k > cteMagica){
        return false;
    } //la otra diagonal
    if(i + j == tam-1 && sumaDiag[1] + k> cteMagica){
        return false;
    }
    return true;
}

void imprimir(vector<vector<int>>& m){
    for(int i = 0; i < tam; i++){
        for(int j = 0; j < tam; j++){
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


bool esMagico(vector<vector<int>>& m, int N){
    for(int i = 0; i < N; i++){
        int suma_fila = 0;
        int suma_col = 0;
        for(int j = 0; j < N; j++){
            suma_fila += m[i][j];
            suma_col += m[j][i];
        }
        if(suma_col != cteMagica || suma_fila != cteMagica){
            return false;
        }
    }
    int suma_diag = 0;
    int suma_diag_inv = 0;
    for(int i = 0; i < N; i++){
        suma_diag += m[i][i];
        suma_diag_inv += m[i][N-i-1];
    }
    if(suma_diag != cteMagica || suma_diag_inv != cteMagica){
        return false;
    }
    return true;
}


bool sigoBien(vector<vector<int>>& m, int i, int j, int k){

    // si termino una columna
    if(i == tam-1){
        return sumaCol[j] + k == cteMagica;
    }
    // si termino una fila
    if(j == tam-1){
        return sumaFila[i] + k == cteMagica;
    }
    // si termino la diagonal principal
    if(i == j && i == tam-1){
        return sumaDiag[0] + k == cteMagica;
    }
    // si termino la diagonal secundaria
    if(i == tam-1 && i + j == tam-1){
        return sumaDiag[1] + k == cteMagica;
    }

    // si no termino ninguna de las anteriores
    return true;
}


bool noPuedoCol(vector<vector<int>> &m, int i, int j, int k){
    if(cteMagica-sumaCol[j] - k > tam*tam || cteMagica-sumaCol[j]-k < 0){
        return true;
    }else{
        return num[cteMagica-sumaCol[j]-k] == 1;
    }
}

bool noPuedoFila(vector<vector<int>> &m, int i, int j, int k){
    if(cteMagica-sumaFila[i] - k > tam*tam || cteMagica-sumaFila[i]-k < 0){
        return true;
    }else{
        return num[cteMagica-sumaFila[i]-k] == 1;
    }
}


int it = 0;
int contar_cm(vector<vector<int>>& m, int i, int j, vector<vector<int>> &res, int& r){
    if(it == r){
        return 0;
    }
    if(i == tam){
        if(esMagico(m, tam)){
            it++;
            if(it == r){
                res = m;
            }
            return 1;
        }else{
            return 0;
        }
    }else{
        int cont = 0;
        for(int k = 1; k <= (tam)*tam; k++){
            
            if(num[k] == 0 && poda(m, i, j, k) && sigoBien(m, i, j, k)){
                if(i == tam-2){
                    if(noPuedoCol(m, i, j, k)){
                        continue;
                    }
                }
                if(j == tam-2){
                    if(noPuedoFila(m, i, j, k)){
                        continue;
                    }
                }
                
                m[i][j] = k;
                num[k] = 1;
                sumaCol[j] += m[i][j];
                sumaFila[i] += m[i][j];
                if(i == j){
                    sumaDiag[0] += m[i][j];
                }
                if(i + j == tam-1){
                    sumaDiag[1] += k;
                }
                int sig_j = (j == tam-1 ? 0 : j + 1);
                int sig_i = (sig_j == 0 ? i + 1 : i);
                cont+= contar_cm(m, sig_i,sig_j, res, r);
                num[k] = 0;
                sumaCol[j] -= m[i][j];
                sumaFila[i] -= m[i][j];
                if(i == j){
                    sumaDiag[0] -= m[i][j];
                }
                if(i + j == tam-1){
                    sumaDiag[1] -= m[i][j];
                }
                m[i][j] = -1;
            }
        }
        return cont;
    }
}

int main(){
    int N, K;
    cin >> N >> K;
    cteMagica = (N*(N*N+1))/2;
    tam = N;
    vector<vector<int>> m(N, vector<int>(N));
    vector<vector<int>> res(N, vector<int>(N));
    sumaFila = vector<int>(N, 0);
    sumaCol = vector<int>(N, 0);
    sumaDiag = vector<int>(2, 0);
    num = vector<int>((N*N)+1, 0);
    int cont = contar_cm(m, 0, 0, res, K);

    if(cont < K){
        cout << -1 << endl;
    }else{
        imprimir(res);
    }
    
    return 0;
}
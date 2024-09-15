#include <iostream>
#include <fstream>

using namespace std;

int main() {
    const int a_length = 20;
    const int b_length = 30;
    const int c_length = 40;
    double h1 = 1.0;
    double h2 = 1.0;
    double D = 1.0;
    double tau = 0.01;
    double current_concentartion[a_length * b_length * c_length];
    double next_concentartion[a_length * b_length * c_length];
    ifstream fin("input.raw", ios_base::binary);
    fin.read((char*)current_concentartion, sizeof(double) * a_length * b_length * c_length);
    fin.close();
    double h1_squared = h1 * h1;
    double h2_squared = h2 * h2;
    double h2_cubed = h2 * h2 * h2;
    long current_indx = 0;
    for(size_t t = 1; t<=1000; t++){
        for(size_t i = 0; i<a_length; i++){
            for(size_t j = 0; j<b_length; j++){
                for(size_t k = 0; k<b_length; k++){
                    current_indx = i * b_length * c_length + j * c_length + k;
                    if(i==0 || j==0 || k==0 || i==a_length-1 || j==b_length-1 || k==c_length-1){
                        next_concentartion[current_indx]=0;
                    }else{
                        next_concentartion[current_indx]= D * tau * ((current_concentartion[current_indx + b_length * c_length] - 2 * current_concentartion[current_indx] + current_concentartion[current_indx - b_length * c_length])/h1_squared + 
                        (current_concentartion[current_indx + c_length] - 2 * current_concentartion[current_indx] + current_concentartion[current_indx - c_length])/h2_squared + 
                        (current_concentartion[current_indx + 1] - 2 * current_concentartion[current_indx] + current_concentartion[current_indx - 1])/h2_cubed) + 
                        current_concentartion[current_indx];
                    }
                    
                }
            }  
            swap(current_concentartion,next_concentartion);
        }
    }
    ofstream fout("output_b.raw", ios_base::binary);
    fout.write((char*)next_concentartion, sizeof(double) * a_length * b_length * c_length);
    fout.close();

    return 0;
}
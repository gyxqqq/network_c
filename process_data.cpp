#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
int main(){
    vector<vector<float>> input_data;
    vector<vector<float>> output_data;
    string filename = "";
    cout<<"Enter the filename: ";
    cin>>filename;
    ifstream file;
    file.open(filename);
    if(!file.is_open()){
        cout<<"Error opening file"<<endl;
        return 1;
    }
    int j=0;
    while (!file.eof())
    {
        vector<float> temp;
        for (int i=0;i<748;i++){
            float x;
            file>>x;
            temp.push_back(x);
        }
        input_data.push_back(temp);
        vector<float> temp2;
        for (int i=0;i<10;i++){
            float x;
            file>>x;
            temp2.push_back(x);
        }
        output_data.push_back(temp2);
        j++;
        if (j % 100 == 0){
            cout<<"Number of samples read: "<<j<<endl;
        }
    }
    file.close();
    cout<<"Data read successfully"<<endl;
    cout<<"Number of samples: "<<j<<endl;
    ofstream file2;
    file2.open("input_data.bin", ios::binary);
    for (int i=0;i<j;i++){
        for (int k=0;k<748;k++){
            file2.write((char*)&input_data[i][k], sizeof(float));
        }
    }
    file2.close();
    cout<<"Input data written successfully"<<endl;
    ofstream file3;
    file3.open("output_data.bin", ios::binary);
    for (int i=0;i<j;i++){
        for (int k=0;k<10;k++){
            file3.write((char*)&output_data[i][k], sizeof(float));
        }
    }
    file3.close();
    cout<<"Output data written successfully"<<endl;
    return 0;
}
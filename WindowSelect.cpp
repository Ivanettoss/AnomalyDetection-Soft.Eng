#include <iostream>
using namespace std;


int v[2] {0,0}; 
//entrynumber è il numero delle entry che contiamo dal file di input 
array<int,2> windowDimension(entrynumber){

    cout<<"there are curently"<<entrynumber<<"entry detected"<<\n;

    while(v[0]>entrynumber)
    {
    cout<<"Select a valid initial starting point for the window"<<\n;
    cin>>v[0];
    }

    while(v[1]>entrynumber || v[1]<v[0])
    {
    cout<<"Select a valid final point for the window"<<\n;
    cin>>v[1];    
    }

    cout<<"your selected window is :"<<\n<<"starting point="<<v[0]<<\n<<"end point="<<v[1];
    
    return v;
}
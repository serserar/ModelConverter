/*
 * File:   modelSampler.cpp
 * Author: serserar
 *
 * Created on February 21, 2016, 2:02 AM
 */

#include "ModelSamplerApp.h"
#include<iostream>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include <unistd.h>

void generateSamples() {
    ModelSamplerApp modelSamplerApp("../samples", "../samples/3dtest-out", "samples-test.xml", true);
    modelSamplerApp.Run();
}

int main(int argc, char** argv) {
    int opt,a=0,b=0,c=0;
    while ((opt = getopt(argc,argv,"abc:d")) != EOF) {
        switch(opt)
        {
        case 'a':
            a = 1;
            cout <<" a is enabled"<<a <<endl;
            break;
        case 'b':
            b = 1;
            cout <<" b is enabled"<<b <<endl;
            break;
        case 'c':
            c = 1;
            cout << "value of c is"<< optarg <<endl ;
            break;
        case '?':
            fprintf(stderr, "usuage is \n -a : for enabling a \n -b : for enabling b \n -c: <value> ");
        default:
            std::cout<<endl;
        }
    }
    if(c) {
        generateSamples();
    }
    return 0;
}


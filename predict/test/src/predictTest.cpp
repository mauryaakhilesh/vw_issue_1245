/*
 * Copyright © Microsoft Corp 2012-2014, Yahoo! Inc. 2007-2012, and many
 individual contributors.

 All rights reserved.

 Redistribution and use in source and binary forms, with or without

 modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright

 notice, this list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright

 notice, this list of conditions and the following disclaimer in the

 documentation and/or other materials provided with the distribution.

 * Neither the name of the Microsoft Corp nor the

 names of its contributors may be used to endorse or promote products

 derived from this software without specific prior written permission.



 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND

 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED

 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE

 DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY

 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES

 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;

 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND

 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT

 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS

 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
individual contributors.

All rights reserved.

Redistribution and use in source and binary forms, with or without

modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright

      notice, this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright

      notice, this list of conditions and the following disclaimer in the

      documentation and/or other materials provided with the distribution.

    * Neither the name of the Microsoft Corp nor the

      names of its contributors may be used to endorse or promote products

      derived from this software without specific prior written permission.



THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND

ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED

WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE

DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY

DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES

(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;

LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND

ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT

(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS

SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * predictTest.cpp
 *
 *  Created on: Jan 17, 2012
 *      Author: surbhi
 *  Modified on : jan 20 , 2017
 *  	Author : Akhilesh
 *
 */

#include "iostream"
#include <fstream>
#include <string>
#include <sstream>
#include "vw_predict_model.h"
#include <vw_predict_model.h>
#include <unistd.h>
using namespace std;

int main(int argc, char **argv) {
	 cout << "In main class \n";
	
	if ( argc < 2 ){     
	// We print argv[0] assuming it is the program name
       		cout<<"usage: "<< argv[0] <<" <modelPath>\n";
		return 0;
	}
    
        char modelpath[strlen(argv[1]) + 1] ;
	strcpy(modelpath, argv[1]);
	char model_ver_name[32] = "MY_TESTING_VERSION_1";
	//vw_model_test(modelpath,model_ver_name);
        int n;
        cout<<"How many times you want to load model \n";
        cin>>n;
        for(int i=0;i<n;i++){
                int st = load_vw_model_from_file(model_ver_name, modelpath);
                cout<<"load status "<<st<<" now sleep for 3 sec for next itration\n";
                int sec = int(3*1000000); 
                usleep(sec); 
        }
        cout << "In main class end\n";

	return 0;
}
